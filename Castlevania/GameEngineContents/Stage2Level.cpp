#include "Stage2Level.h"
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "Monster.h"



// Contents
#include "Player.h"
#include "BackGround.h"
#include "Map.h"


Stage2Level::Stage2Level() 
{
}

Stage2Level::~Stage2Level() 
{
}

void Stage2Level::Start()
{
}

void Stage2Level::Update(float _Delta)
{
}

void Stage2Level::Release()
{
}

void Stage2Level::LevelStart(GameEngineLevel* _PrevLevel)
{
	/*if (nullptr == LevelPlayer)
	{
		MsgBoxAssert("�÷��̾ ���������� �ʾҽ��ϴ�.");
	}*/

	// LevelPlayer->SetGroundTexture("��¼��");

}

void Stage2Level::LevelEnd(GameEngineLevel* _NextLevel)
{
}
