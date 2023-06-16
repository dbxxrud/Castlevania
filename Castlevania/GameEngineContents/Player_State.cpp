#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

void Player::IdleStart()
{
	ChangeAnimationState("Idle");;
}

void Player::RunStart()
{
	ChangeAnimationState("RunStart");
}

void Player::JumpStart()
{
	SetGravityVector(float4::UP * 1000.0f);

	ChangeAnimationState("Jump");
}

void Player::DuckingStart()
{
	ChangeAnimationState("Ducking");
}

void Player::FallingStart()
{
	ChangeAnimationState("Falling");
}

void Player::AttackStart()
{
	ChangeAnimationState("Attack");
	//ChangeAnimationState("DuckingAttack");
}

void Player::DuckingAttackStart()
{
	ChangeAnimationState("DuckingAttack");

}
void Player::BatModeStart()
{
	ChangeAnimationState("BatModeStart");
	BatStart = true;
}


void Player::IdleUpdate(float _Delta)
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
	if (true == GameEngineInput::IsDown('A')
		|| true == GameEngineInput::IsDown('W')
		|| true == GameEngineInput::IsDown('S')
		|| true == GameEngineInput::IsDown('D'))
	{
		DirCheck();
		ChanageState(PlayerState::Run);
		return;
	}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		IsJump = true;
		ChanageState(PlayerState::Jump);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LBUTTON))
	{
		ChanageState(PlayerState::Attack);
		return;
	}

	if (true == GameEngineInput::IsPress('C'))
	{
		ChanageState(PlayerState::Ducking);
		return;
	}

	// 일단은 키 누르면 변신하는걸로하자
	if (true == GameEngineInput::IsPress('B'))
	{
		ChanageState(PlayerState::Bat);
		return;
	}
}

void Player::RunUpdate(float _Delta)
{
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));
		if (RGB(255, 255, 255) == Color) // 흰색바탕이면 중력적용
		{
			Gravity(_Delta);
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

	if (true == MainRenderer->IsAnimationEnd())
	{
		ChangeAnimationState("Run");

	}


	DirCheck();

	float4 CheckPos = float4::ZERO;
	float MoveSpeed = 500.0f;

	float4 MovePos = float4::ZERO;

	if (true == GameEngineInput::IsPress('A') && Dir == PlayerDir::Left)
	{
		// 약간위로 올리고
		CheckPos = { -30.0f, -50.0f };
		MovePos = { -MoveSpeed * _Delta, 0.0f };
	}
	else if (true == GameEngineInput::IsPress('D') && Dir == PlayerDir::Right)
	{
		CheckPos = { 30.0f, -50.0f };

		MovePos = { MoveSpeed * _Delta, 0.0f };
	}
	//if (true == GameEngineInput::IsPress('S'))
	//{
	//	MovePos = { 0.0f, MoveSpeed * _Delta };
	//}

	if (true == GameEngineInput::IsDown(VK_SPACE))
	{
		IsJump = true;
		ChanageState(PlayerState::Jump);
		return;
	}


	if (MovePos == float4::ZERO)
	{
		DirCheck();
		ChanageState(PlayerState::Idle);
		return;
	}

	{
		// 흰색이면 움직여라 못가게 막는코드
		unsigned int Color = GetGroundColor(RGB(255, 255, 255), CheckPos);

		if (Color == RGB(255, 255, 255))
		{
			AddPos(MovePos);
			GetLevel()->GetMainCamera()->AddPos(MovePos);
		}
	}

	if (true == GameEngineInput::IsPress(VK_LBUTTON))
	{
		ChanageState(PlayerState::Attack);
		return;
	}


}

void Player::JumpUpdate(float _Delta)
{
	float4 MovePos = float4::ZERO;
	if (true == GameEngineInput::IsPress('A'))
	{
		MovePos += float4::LEFT * _Delta * 300.0f;
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		MovePos += float4::RIGHT * _Delta * 300.0f;
	}

	AddPos(MovePos);

	// 더블점프 -> 안되는중
	if (IsJump == true && GameEngineInput::IsDown(VK_SPACE))
	{
		SetGravityVector(float4::UP * 1000.0f);

		ChangeAnimationState("Double_Jump");

		IsJump = false;
	}


	Gravity(_Delta);



	// 점프하고 내 아래 픽셀이 허공이라면 fall 상태로..
	{
		unsigned int Color = GetGroundColor(RGB(255, 255, 255));

		if (Color != RGB(255, 255, 255))
		{
			 // 땅에 땋으면
			ChanageState(PlayerState::Idle);
			return;
		}
		
	}

}

void Player::DuckingUpdate(float _Delta)
{
	if (true == GameEngineInput::IsUp('C'))
	{
		ChanageState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::IsPress(VK_LBUTTON))
	{
		ChanageState(PlayerState::DuckingAttack);
		return;
	}

}

void Player::FallingUpdate(float _Delta)
{

}

void Player::AttackUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd())
	{
		ChanageState(PlayerState::Idle);
		return;
	}
}

void Player::DuckingAttackUpdate(float _Delta)
{
	if (true == GameEngineInput::IsUp('C'))
	{
		ChanageState(PlayerState::Idle);
		return;
	}
}

void Player::BatModeUpdate(float _Delta)
{
	if (true == MainRenderer->IsAnimationEnd() && true == BatStart)
	{
		ChangeAnimationState("BatModeMove");
		MainRenderer->SetRenderScale({ 600.0f, 600.0f });
		float4 Pos = MainPlayer->GetPos();
		MainPlayer->SetPos({ Pos.X, Pos.Y - 50.0f });
		BatStart = false;
		return;
	}
	if (true == GameEngineInput::IsDown('B'))
	{
		ChanageState(PlayerState::Idle);

		MainRenderer->SetRenderScale({ 900.0f, 900.0f });
		return;
	}

}
