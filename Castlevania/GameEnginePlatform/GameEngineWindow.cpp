#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <iostream>

HINSTANCE GameEngineWindow::Instance = nullptr;
GameEngineWindow GameEngineWindow::MainWindow;
bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = false;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
    if (nullptr != BackBuffer)
    { // ������!
        delete BackBuffer;
        BackBuffer = nullptr;
    }

    if (nullptr != WindowBuffer)
    { // ������!
        delete WindowBuffer;
        WindowBuffer = nullptr;
    }
}

void GameEngineWindow::ClearBackBuffer()
{
    Rectangle(BackBuffer->GetImageDC(), 0, 0, BackBuffer->GetScale().iX(), BackBuffer->GetScale().iY());
}

void GameEngineWindow::DoubleBuffering()
{
    // transcopy�� �ʿ�� ����. ���״�� �̹����� ���� �Ȱ��� �׷��� ��� �ǹ̴ϱ�
    WindowBuffer->BitCopy(BackBuffer, Scale.Half(), BackBuffer->GetScale());
}

void GameEngineWindow::CursorOff()
{
    ShowCursor(FALSE);
}


void GameEngineWindow::Open(const std::string& _Title, HINSTANCE _hInstance)
{
    Instance = _hInstance;
    Title = _Title;

    if (nullptr == Instance)
    {
        MsgBoxAssert("HInstance���� �����츦 ������� �����ϴ�.");
        return;
    }

    MyRegisterClass();
    InitInstance();
}


void GameEngineWindow::InitInstance()
{
    // ������ ����� �Լ���
    // const char* == std::string
    hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("������ ������ �����߽��ϴ�.");
        return;
    }

    // :: ������ �ǹ�?..
    // ::GetDC(hWnd)�� ���� ���ӽ����̽��� �ƴ� ���� ���ӽ����̽����� GetDC �Լ��� ȣ���ϴ� ��
    Hdc = ::GetDC(hWnd);

    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc); // �����ϰ� Hdc�� �Ⱦ����°�

    // ������۸��� �ϱ� ���� �̹���
    BackBuffer = new GameEngineWindowTexture();
    // �������� GetScale�� �������� ũ��! �� ũ�⸸ŭ�� �����츦 ������̴�.
    BackBuffer->ResCreate(WindowBuffer->GetScale());

    // CreateDC()

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

}

LRESULT CALLBACK GameEngineWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SETFOCUS:
    {
        IsFocusValue = true;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_KILLFOCUS:
    {
        IsFocusValue = false;
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        IsWindowUpdate = false;
        //PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void GameEngineWindow::MyRegisterClass()
{
    static bool Check = false; // ���� static �� �Լ������� ����!

    if (true == Check)
    {
        return;
    }

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // LRESULT(CALLBACK* WNDPROC)(HWND, unsigned int, unsigned int, unsigned int);
    wcex.lpfnWndProc = GameEngineWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = Instance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "DefaultWindow";
    wcex.hIconSm = nullptr;

    if (false == RegisterClassExA(&wcex))
    {
        MsgBoxAssert("������ Ŭ���� ���Ͽ� �����߽��ϴ�.");
        return;
    }

    Check = true;
}

void GameEngineWindow::MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)())
{
    if (nullptr != _Start)
    {
        _Start(_Inst);
    }

    MSG msg;
    while (IsWindowUpdate)
    {
        // �����쿡 �������� �ִ°� �ƴ϶� �޼����� �ֵ� ����
        // ������ �޼����� ó�� ���� �� ����.
        // <= Ű�� �ø������� �����
        // (�Լ��� ����� ���������� ��ٸ��� �Լ����� ���� �Լ���� �մϴ�)
        // GetMessage�� ���� �Լ��̴�. �������� �޼����� �߻��Ҷ����� ��ٸ���.
        // �񵿱� �޼��� �Լ��� �ִ�. ������ �޼����� ������ ó���ϰ� ������ �׳� �����
        // PeekMessage�� ������ �޼����� ������ 0�� �����մϴ�.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // ������ �޼����� ���� �ð��� ����Ÿ���̶�� �Ѵ�
        // ������ ����Ÿ�ӿ� ���ư��°� �����̴�
        // �����߿� 2���� ������ �ִ�. �����츦 �����̰ų� ũ�⸦ ���̸� ȭ���� �����ϴ� ����
        // �����찡 �߱����� �ε��ؾ��� �̹����� ���� ����� ó���ϴ� �ܰ�
        // FPS Frame Per Second
        // �ʴ� ȭ���� �׷����� Ƚ��
        // �ϵ����͵� ������ �ִ�
        // �̰� �ѹ����� ���� ���� �������̶�� �Ѵ�
        if (nullptr != _Update)
        {
            _Update(); // �ھ������Ʈ
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    return;
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
    // Window���� LP �����Ͷ�� �� Long Pointer 8����Ʈ ������
    Scale = _Scale;

    // �������� ũ�Ⱑ �ٲ�� ������ �̹����� ��������� �����ٰ�!
    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = new GameEngineWindowTexture;
        BackBuffer->ResCreate(_Scale);
    }


    // LPRECT�� RECT ������
    //                200           200
    RECT Rc = { 0, 0, _Scale.iX(), _Scale.iY() };
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    //                          100        100         500          500
    SetWindowPos(hWnd, nullptr, _Pos.iX(), _Pos.iY(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

float4 GameEngineWindow::GetMousePos()
{
    POINT MoniterPoint;
    GetCursorPos(&MoniterPoint);
    ScreenToClient(hWnd, &MoniterPoint);

    return float4{ static_cast<float>(MoniterPoint.x), static_cast<float>(MoniterPoint.y) };
}