#include <iostream>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/CastlevaniaCore.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 어떤 코어프로세스를 상속받는 클래스를 넣어줘야함
	GameEngineCore::EngineStart<CastlevaniaCore>("MyWindow", hInstance);
	return 0;
}