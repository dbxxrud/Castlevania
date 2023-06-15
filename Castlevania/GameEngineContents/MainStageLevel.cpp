#include "MainStageLevel.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineContents/PlayUIManager.h>
#include <GameEngineCore/GameEngineActor.h>



// Contents
#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "PlayActor.h"
#include "Map.h"

MainStageLevel::MainStageLevel()
{
}

MainStageLevel::~MainStageLevel()
{
}

void MainStageLevel::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FilePath.MoveChild("ContentsResources\\Texture\\Map\\");
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("Map.bmp"));
		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("MapPixel.bmp"));

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("FadeOut.bmp"));

	}

	BackGroundPtr = CreateActor<Map>();
	BackGroundPtr->Init("Map.Bmp", "MapPixel.bmp");
	
	LevelPlayer = CreateActor<Player>();
	LevelPlayer->SetGroundTexture("MapPixel.bmp");

	Monster* BladeMaster = CreateActor<Monster>();
	BladeMaster->SetGroundTexture("MapPixel.bmp");
	BladeMaster->SetPos({ 8450 , 1500 });

	Item* ItemFire = CreateActor<Item>();
	ItemFire->SetPos({ 9750, 1490 });




	LevelPlayer->OverOn(); // ? 머지

	LevelPlayer->SetPos({ 10400,1500 }); // 레벨1 초반위치

	CreateActor<PlayUIManager>();

}

void MainStageLevel::Update(float _Delta)
{
	if (true == GameEngineInput::IsDown('O'))
	{
		GameEngineCore::ChangeLevel("TitleLevel");
	}
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("Stage2Level");
	}
	if (true == GameEngineInput::IsDown('J'))
	{
		BackGroundPtr->SwitchRender(); 
	}


	//PlayActor Color;

	//if (RGB(0, 0, 255) == Color.GetGroundColor(RGB(0, 0, 255)))
	//{
	//	GameEngineCore::ChangeLevel("Stage2Level");
	//}
	//if (1.0f <= GetLiveTime())
	//{
	//	Monster* NewMonster = CreateActor<Monster>();
	//	ResetLiveTime();
	//}


}

void MainStageLevel::Release()
{
}

void MainStageLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("플레이어를 세팅하지 않았습니다.");
	}
}

void MainStageLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}