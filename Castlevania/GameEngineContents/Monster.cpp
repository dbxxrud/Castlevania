#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

// ���͵� �÷��̿��� �޾ƶ�

std::list<Monster*> Monster::AllMonster;

Monster::Monster()
{
	AllMonster.push_back(this); // ��� ���͸� �� ��� �ִ�
}

Monster::~Monster()
{
}

void Monster::AllMonsterDeath()
{
	for (Monster* Monster : AllMonster)
	{
		Monster->Death();
	}

	AllMonster.clear();
}

void Monster::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("M_BladeMaster.bmp"), 5, 9);


		{
			BladeMasterRenderer = CreateRenderer(RenderOrder::Play);
			BladeMasterRenderer->CreateAnimation("Right_Idle", "M_BladeMaster.bmp", 0, 2, 0.5f, true);
			BladeMasterRenderer->CreateAnimation("Right_Run", "M_BladeMaster.bmp", 3, 4, 0.5f, true);
			BladeMasterRenderer->ChangeAnimation("Right_Idle");

			BladeMasterRenderer->SetRenderScale({ 450.0f, 450.0f });

		}
	}

}

void Monster::Update(float _Delta)
{
	// Player::MainPlayer = nullptr;

	//float4 Dir = Player::MainPlayer->GetPos() - GetPos();

	//Dir.Normalize();

	//// Dir <= �Ÿ��� �������� �ʴٴ� �� ��������.

	//// Dir *= 0.1f;

	//AddPos(Dir * _Delta * 100.0f);
}