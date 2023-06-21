#include "Monster.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

// 몬스터도 플레이엑터 받아라

std::list<Monster*> Monster::AllMonster;

Monster::Monster()
{
	AllMonster.push_back(this); // 모든 몬스터를 다 들고 있는
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
	if (false == ResourcesManager::GetInst().IsLoadTexture("M_BladeMaster.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Monster\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("M_BladeMaster.bmp"), 5, 9);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("M_ArmorLord.bmp"), 5, 10);


	}
	{
		BladeMasterRenderer = CreateRenderer(RenderOrder::Play);
		//BladeMasterRenderer2 = CreateRenderer(RenderOrder::Play);

		BladeMasterRenderer->CreateAnimation("Right_Idle", "M_BladeMaster.bmp", 0, 2, 0.5f, true);
		BladeMasterRenderer->CreateAnimation("Right_Run", "M_BladeMaster.bmp", 3, 4, 0.5f, true);
		BladeMasterRenderer->ChangeAnimation("Right_Idle");

		BladeMasterRenderer->SetRenderScale({ 450.0f, 450.0f });
		//BladeMasterRenderer2->SetRenderScale({ 450.0f, 450.0f });
		//BladeMasterRenderer2->ChangeAnimation("Right_Idle");
	}
	ChanageState(MonsterState::Idle);


	GameEngineCollision* BodyCollsion = CreateCollision(CollisionOrder::MonsterBody);
	BodyCollsion->SetCollisionScale({ 100, 300 });
	BodyCollsion->SetCollisionType(CollisionType::Rect);
}

void Monster::Update(float _Delta)
{
	//Player::MainPlayer = nullptr;

	//float4 Dir = Player::MainPlayer->GetPos() - GetPos();

	//Dir.Normalize();

	//// Dir <= 거리가 일정하지 않다는 게 문제에요.

	//// Dir *= 0.1f;

	//AddPos(Dir * _Delta * 100.0f);

	StateUpdate(_Delta);


}

void Monster::ChangeAnimationState(const std::string& _StateName)
{

	std::string AnimationName;

	switch (Dir)
	{
	case MonsterDir::Right:
		AnimationName = "Right_";
		break;
	case MonsterDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	BladeMasterRenderer->ChangeAnimation(AnimationName);
}

void Monster::StateUpdate(float _Delta)
{
	switch (State)
	{
	case MonsterState::Idle:
		return IdleUpdate(_Delta);
	default:
		break;
	}
}




void Monster::ChanageState(MonsterState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case MonsterState::Idle:
			IdleStart();
			break;
		case MonsterState::Run:
			RunStart();
			break;
		case MonsterState::Jump:
			JumpStart();
			break;
			break;
		case MonsterState::Attack:
			AttackStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}