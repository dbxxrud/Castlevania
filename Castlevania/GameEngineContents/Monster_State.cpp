#include "Monster.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCore.h>


void Monster::IdleStart()
{
	ChangeAnimationState("Idle");;
}

void Monster::RunStart()
{
	ChangeAnimationState("RunStart");
}

void Monster::JumpStart()
{
	SetGravityVector(float4::UP * 1000.0f);

	ChangeAnimationState("Jump");
}

void Monster::AttackStart()
{
}

