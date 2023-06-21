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

void Monster::IdleUpdate(float _Delta)
{
	{ // 함수화 해도될듯
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);// 흰바탕이면 중력적용
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP); // 흰바탕이 될때까지 올려라
				AddPos(float4::UP);
			}

			GravityReset();
		}
	}
}

