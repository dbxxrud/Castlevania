#include "Stage1Level.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineContents/PlayUIManager.h>
#include "Monster.h"



// Contents
#include "Player.h"
#include "BackGround.h"
#include "Map.h"

Stage1Level::Stage1Level() 
{
}

Stage1Level::~Stage1Level() 
{
}

void Stage1Level::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("TestMapPixel.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("DebugRoomPixel.bmp"));
	}

	BackGroundPtr = CreateActor<BackGround>();
	BackGroundPtr->Init("TestMap.Bmp", "TestMapPixel.bmp");

	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("TestMapPixel.bmp");
	LevelPlayer->SetPos({ 4000, 500 });

	CreateActor<PlayUIManager>();

}

void Stage1Level::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender();
	}

	//if (1.0f <= GetLiveTime())
	//{
	//	Monster* NewMonster = CreateActor<Monster>();
	//	ResetLiveTime();
	//}

	// GameEngineCore::ChangeLevel("TitleLevel");
}

void Stage1Level::Release()
{
}

void Stage1Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 않았습니다.");
	}
}

void Stage1Level::LevelEnd(GameEngineLevel* _NextLevel)
{
}