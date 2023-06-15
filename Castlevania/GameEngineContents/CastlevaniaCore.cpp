#include "CastlevaniaCore.h"
#include "TitleLevel.h"
#include "MainStageLevel.h"
#include "DebugLevel.h"
#include <GameEnginePlatform/GameEngineWindow.h>

CastlevaniaCore::CastlevaniaCore() 
{
}

CastlevaniaCore::~CastlevaniaCore() 
{
}

void CastlevaniaCore::Start()
{
	GameEngineWindow::MainWindow.SetPosAndScale({ 0,0 }, { 1280, 800 });

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<DebugLevel>("DebugLevel");

	GameEngineCore::CreateLevel<MainStageLevel>("MainStageLevel");


	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("TitleLevel");
}

void CastlevaniaCore::Update(float _Delta)
{

}

void CastlevaniaCore::Render(float _Delta)
{
}

void CastlevaniaCore::Release()
{
}
