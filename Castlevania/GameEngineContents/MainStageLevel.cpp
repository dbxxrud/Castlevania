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
#include "DebugLevel.h"
#include "Map.h"
#include "FadeObject.h"
#include "ContentsEnum.h"



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


	Item* ItemFire = CreateActor<Item>();
	ItemFire->SetPos({ 9750, 1490 });

	// 몬스터 생성
	Monster* BladeMaster = CreateActor<Monster>(UpdateOrder::Monster);
	BladeMaster->SetPos({ 8300 , 1450 });

	BladeMaster->SetGroundTexture("MapPixel.bmp");

	CreateActor<PlayUIManager>();

	{
		FadeObject* FObject = CreateActor<FadeObject>();
	}
}

void MainStageLevel::Update(float _Delta)
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
	//	Monster* NewMonster = CreateActor<Monster>(UpdateOrder::Monster);

	//	NewMonster->SetPos({ 10400,1500 });

	//	ResetLiveTime();
	//}


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
	LevelPlayer = Player::MainPlayer;

	LevelPlayer->SetGroundTexture("MapPixel.bmp");


}

void MainStageLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
}