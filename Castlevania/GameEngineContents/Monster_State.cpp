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
	{ // �Լ�ȭ �ص��ɵ�
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color)
		{
			Gravity(_Delta);// ������̸� �߷�����
		}
		else
		{
			unsigned int CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP);

			while (CheckColor != RGB(255, 255, 255))
			{
				CheckColor = GetGroundColor(RGB(255, 255, 255), float4::UP); // ������� �ɶ����� �÷���
				AddPos(float4::UP);
			}

			GravityReset();
		}
	}
}

