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
    { // 릭제거!
        delete BackBuffer;
        BackBuffer = nullptr;
    }

    if (nullptr != WindowBuffer)
    { // 릭제거!
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
    // transcopy할 필요는 없다. 말그대로 이미지를 나랑 똑같이 그려라 라는 의미니까
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
        MsgBoxAssert("HInstance없이 윈도우를 만들수는 없습니다.");
        return;
    }

    MyRegisterClass();
    InitInstance();
}


void GameEngineWindow::InitInstance()
{
    // 윈도우 만드는 함수인
    // const char* == std::string
    hWnd = CreateWindowA("DefaultWindow", Title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, Instance, nullptr);

    if (!hWnd)
    {
        MsgBoxAssert("윈도우 생성에 실패했습니다.");
        return;
    }

    // :: 전역을 의미?..
    // ::GetDC(hWnd)는 현재 네임스페이스가 아닌 전역 네임스페이스에서 GetDC 함수를 호출하는 것
    Hdc = ::GetDC(hWnd);

    WindowBuffer = new GameEngineWindowTexture();
    WindowBuffer->ResCreate(Hdc); // 순수하게 Hdc로 안쓸려는것

    // 더블버퍼링을 하기 위한 이미지
    BackBuffer = new GameEngineWindowTexture();
    // 윈도우의 GetScale은 윈도우의 크기! 그 크기만큼의 윈도우를 만들것이다.
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
    static bool Check = false; // 지역 static 이 함수에서만 쓰는!

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
        MsgBoxAssert("윈도우 클래스 동록에 실패했습니다.");
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
        // 윈도우에 무슨일이 있는게 아니라 메세지가 있든 없든
        // 윈도우 메세지를 처리 안할 수 없다.
        // <= 키가 늘릴때까지 멈춘다
        // (함수가 제대로 끝날때까지 기다리는 함수들을 동기 함수라고 합니다)
        // GetMessage는 동기 함수이다. 윈도우의 메세지가 발생할때까지 기다린다.
        // 비동기 메세지 함수가 있다. 윈도우 메세지가 있으면 처리하고 없으면 그냥 실행돼
        // PeekMessage는 윈도우 메세지가 없으면 0을 리턴합니다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        // 윈도우 메세지가 없는 시간은 데드타임이라고 한다
        // 게임은 데드타임에 돌아가는게 보통이다
        // 게임중에 2가지 종류가 있다. 윈도우를 움직이거나 크기를 줄이면 화면이 정지하는 게임
        // 윈도우가 뜨기전에 로딩해야할 이미지나 사운드 등등을 처리하는 단계
        // FPS Frame Per Second
        // 초당 화면이 그려지는 횟수
        // 하드웨어와도 연결이 있다
        // 이게 한바퀴가 도는 것을 프레임이라고 한다
        if (nullptr != _Update)
        {
            _Update(); // 코어업데이트
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
    // Window에서 LP 포인터라는 뜻 Long Pointer 8바이트 포인터
    Scale = _Scale;

    // 윈도우의 크기가 바뀌면 기존의 이미지가 쓸모없어짐 지웠다가!
    if (nullptr != BackBuffer)
    {
        delete BackBuffer;
        BackBuffer = new GameEngineWindowTexture;
        BackBuffer->ResCreate(_Scale);
    }


    // LPRECT는 RECT 포인터
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