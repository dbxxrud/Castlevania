#include "DebugLevel.h"
#include "Map.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>


#pragma comment(lib, "msimg32.lib")

// Contents
#include "Player.h"

// 타이틀레벨 -> 디버그 레벨로 돌려
DebugLevel::DebugLevel()
{
}

DebugLevel::~DebugLevel() 
{
}

void DebugLevel::Start()
{

	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DebugRoom.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DebugRoomPixel.bmp"));
	}

	DebugRoomPtr = CreateActor<Map>();
	DebugRoomPtr->Init("DebugRoom.Bmp", "DebugRoomPixel.bmp");

	DebugLevelPlayer = CreateActor<Player>();
	DebugLevelPlayer->SetGroundTexture("DebugRoomPixel.bmp");

	DebugLevelPlayer->SetPos({ 1000 , 1500 });

	DebugLevelPlayer->OverOn();
}

void DebugLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("MainStageLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		DebugRoomPtr->SwitchRender();
	}

}
void DebugLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == DebugLevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 않았습니다.");
	}
}

void DebugLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	DebugLevelPlayer->SetPos({ 10400,1500 });

}
