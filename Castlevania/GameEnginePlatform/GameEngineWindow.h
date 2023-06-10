#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineWindowTexture.h"

// 설명 :
class GameEngineWindow
{
public:
	static GameEngineWindow MainWindow;

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

	void Open(const std::string& _Title, HINSTANCE _hInstance);

	static void MessageLoop(HINSTANCE _Inst, void(*_Start)(HINSTANCE), void(*_Update)(), void(*_End)());

	HDC GetHDC()
	{
		return Hdc;
	}
	
	float4 GetScale()
	{
		return Scale;
	}

	GameEngineWindowTexture* GetWindowBuffer()
	{
		return WindowBuffer;
	}

	GameEngineWindowTexture* GetBackBuffer()
	{
		return BackBuffer;
	}

	float4 GetMousePos(); // 핸들의 윈도우를 기반으로 마우스포스 넘겨줌

	void SetPosAndScale(const float4& _Pos, const float4& _Scale);

	static void WindowLoopOff()
	{
		IsWindowUpdate = false;
	}
	void ClearBackBuffer();
	void DoubleBuffering();

	void CursorOff();

	static bool IsFocus()
	{
		return IsFocusValue;
	}

	float GetDoubleBufferingCopyScaleRatio() const
	{
		return CopyRatio;
	}

	void SetDoubleBufferingCopyScaleRatio(float _Ratio)
	{
		CopyRatio = _Ratio;
	}

	void AddDoubleBufferingCopyScaleRatio(float _Ratio)
	{
		CopyRatio += _Ratio;
	}

protected:

private:
	static bool IsFocusValue;
	static bool IsWindowUpdate;
	static HINSTANCE Instance;
	std::string Title = "";
	HWND hWnd = nullptr;
	float CopyRatio = 1.0f;


	float4 Scale;
 
	// DC관리
	GameEngineWindowTexture* BackBuffer = nullptr;

	GameEngineWindowTexture* WindowBuffer = nullptr;


	// 2차원 배열 형식의 색깔들의 집합이 존재하고
	// 거기에 그림을 그리거나 수정할수 있는 권한을 HDC
	HDC Hdc = nullptr; // 특정 윈도우에 그림을 그릴 수 있는 권한 -> 어떤 색깔이 있는 2차원 배열에 그림을 그릴 수 있는 권한

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitInstance();
	void MyRegisterClass();
};