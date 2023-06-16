#include "Player.h"
#pragma region Headers

#include "ContentsEnum.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
// #include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

#include "PlayUIManager.h"
#include <GameEnginePlatform/GameEngineInput.h>
#pragma endregion

Player* Player::MainPlayer = nullptr; // �÷��̾ �˼��ֵ���

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	if(false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp")) // �̷��� �ε尡 �ѹ���
	{
		// ������ �ڵ����� ���� �������� ��ġ�� �ȴ�.
		// �� ��ü�� ��δ�
		// ������ġ  C:\47th\WinAPI_Castlevania\Castlevania\CastlevaniaApp
		// ������ġ C:\47th\WinAPI_Castlevania\Castlevania\ContentsResources\Texture\Player
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HP_Bar.bmp"));


		// ���̵�
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Idle.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Idle.bmp"), 5, 2);

		// �̵�
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Move.bmp"), 5, 7);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Move.bmp"), 5, 7);

		// ����
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Turning.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Turning.bmp"), 5, 2);

		// ����
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Jump.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Jump.bmp"), 5, 2);
		
		// ��������
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_DoubleJump.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_DoubleJump.bmp"), 5, 1);

		// �ɱ�
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Ducking.bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Ducking.bmp"), 5, 4);


		// ����
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Falling.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Falling.bmp"), 5, 3);

		// �ҵ����
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Attack.bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Attack.bmp"), 5, 4);

		// �ʱ����
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_DuckingAttack.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_DuckingAttack.bmp"), 5, 3);

		// ������
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Bat.bmp"), 5, 6);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Bat.bmp"), 5, 6);

		// ������ ������
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_BatMove.bmp"), 6, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_BatMove.bmp"), 6, 1);

	}

	{
		MainRenderer = CreateRenderer(RenderOrder::Play);
		
		MainRenderer->CreateAnimation("Left_Idle", "Player_Left_Idle.bmp", 0, 6, 0.1f, true);
		MainRenderer->CreateAnimation("Right_Idle", "Player_Right_Idle.bmp", 0, 6, 0.1f, true);

		MainRenderer->CreateAnimation("Left_RunStart", "Player_Left_Move.bmp", 0, 14, 0.05f, true);
		MainRenderer->CreateAnimation("Right_RunStart", "Player_Right_Move.bmp", 0, 14, 0.05f, true);

		MainRenderer->CreateAnimation("Left_Run", "Player_Left_Move.bmp", 15, 30, 0.05f, true);
		MainRenderer->CreateAnimation("Right_Run", "Player_Right_Move.bmp", 15, 30, 0.05f, true);

		MainRenderer->CreateAnimation("Left_Turning", "Player_Left_Turning.bmp", 0, 9, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Turning", "Player_Right_Turning.bmp", 0, 9, 0.05f, false);

		MainRenderer->CreateAnimation("Left_Jump", "Player_Left_Jump.bmp", 0, 5, 0.15f, true);
		MainRenderer->CreateAnimation("Right_Jump", "Player_Right_Jump.bmp", 0, 5, 0.2f, true);

		MainRenderer->CreateAnimation("Left_Move_Jump", "Player_Left_Jump.bmp", 6, 9, 0.15f, true);
		MainRenderer->CreateAnimation("Right_Move_Jump", "Player_Right_Jump.bmp", 6, 9, 0.15f, true);

		MainRenderer->CreateAnimation("Left_Double_Jump", "Player_Left_DoubleJump.bmp", 0, 4, 0.15f, true);
		MainRenderer->CreateAnimation("Right_Double_Jump", "Player_Right_DoubleJump.bmp", 0, 4, 0.15f, true);


		MainRenderer->CreateAnimation("Right_Ducking", "Player_Right_Ducking.bmp", 0, 13, 0.05f, false);
		MainRenderer->CreateAnimation("Left_Ducking", "Player_Left_Ducking.bmp", 0, 13, 0.05f, false);



		MainRenderer->CreateAnimation("Left_Falling", "Player_Left_Falling.bmp", 0, 13, 0.1f, false);
		MainRenderer->CreateAnimation("Right_Falling", "Player_Right_Falling.bmp", 0, 13, 0.1f, false);


		MainRenderer->CreateAnimation("Left_Attack", "Player_Left_Attack.bmp", 0, 13, 0.05f, false);
		MainRenderer->CreateAnimation("Right_Attack", "Player_Right_Attack.bmp", 0, 13, 0.05f, false);

		MainRenderer->CreateAnimation("Left_DuckingAttack", "Player_Left_DuckingAttack.bmp", 0, 13, 0.05f, false);
		MainRenderer->CreateAnimation("Right_DuckingAttack", "Player_Right_DuckingAttack.bmp", 0, 13, 0.05f, false);

		MainRenderer->CreateAnimation("Left_BatModeStart", "Player_Left_Bat.bmp", 0, 29,0.1f, true);
		MainRenderer->CreateAnimation("Right_BatModeStart", "Player_Right_Bat.bmp", 0, 29, 0.1f,true);
		
		MainRenderer->CreateAnimation("Left_BatModeMove", "Player_Left_BatMove.bmp", 0, 5, 0.1f, true);
		MainRenderer->CreateAnimation("Right_BatModeMove", "Player_Right_BatMove.bmp", 0, 5, 0.1f, true);



		MainRenderer->ChangeAnimation("Left_Idle");
		MainRenderer->SetRenderScale({ 900.0f, 900.0f });
	
	}

	{
		// �浹ü ����
		BodyCollsion = CreateCollision(CollisionOrder::PlayerBody);
		BodyCollsion->SetCollisionScale({ 100, 300 });
		BodyCollsion->SetCollisionType(CollisionType::Rect);
	}


	ChanageState(PlayerState::Idle);
	Dir = PlayerDir::Right;

}

void Player::Update(float _Delta)
{
	std::vector<GameEngineCollision*> _Col;
	if (true == BodyCollsion->Collision(CollisionOrder::Potal, _Col
		, CollisionType::Rect // ���� �簢������ ����
		, CollisionType::Rect // ��뵵 �簢������ ����
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
		}
		// ���� ���Ͷ� �浹�Ѱž�.
	}

	/*GameEngineRenderer* Ptr = CreateRenderer("Fade", 6000);
		Ptr->SetRenderScale({ 1280, 720 });*/

	//if (true == GameEngineInput::IsPress('L'))
	//{
	//	// GameEngineSound::SoundLoad("C:\\AAAA\\AAAA\\A\\AAA.Mp3");
	//	// GameEngineSound::SoundPlay("AAA.Mp3");
	//	// GameEngineSound::PlayBgm("AAA.Mp3");
	//	// GameEngineSound::StopBgm("AAA.Mp3");

	//	GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(1.0f * _Delta);

	//	// Monster::AllMonsterDeath();
	//}

	if (true == GameEngineInput::IsPress('Y'))
	{
		GameEngineWindow::MainWindow.AddDoubleBufferingCopyScaleRatio(-1.0f * _Delta);
		GameEngineLevel::CollisionDebugRenderSwitch();
	}
	StateUpdate(_Delta);

	CameraFocus(); // ī�޶� �߾����� �� �÷��̾�� 0,0�� �ִ°���
}

void Player::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PlayerState::Idle:
		return IdleUpdate(_Delta);
	case PlayerState::Run:
		return RunUpdate(_Delta);
	case PlayerState::Jump:
		return JumpUpdate(_Delta);
	case PlayerState::Ducking:
		return DuckingUpdate(_Delta);
	case PlayerState::Fall:
		return FallingUpdate(_Delta);
	case PlayerState::Attack:
		return AttackUpdate(_Delta);
	case PlayerState::DuckingAttack:
		return DuckingAttackUpdate(_Delta);
	case PlayerState::Bat:
		return BatModeUpdate(_Delta);
	default:
		break;
	}

}

void Player::ChanageState(PlayerState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Run:
			RunStart();
			break;
		case PlayerState::Jump:
			JumpStart();
			break;
		case PlayerState::Ducking:
			DuckingStart();
			break;
		case PlayerState::Fall:
			FallingStart();
			break;
		case PlayerState::Attack:
			AttackStart();
			break;
		case PlayerState::DuckingAttack:
			DuckingAttackStart();
			break;
		case PlayerState::Bat:
			BatModeStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void Player::DirCheck()
{
	if (true == GameEngineInput::IsFree('A') && true == GameEngineInput::IsFree('D'))
	{
		return;
	}

	// A�� ���Ȱų� D�� �����̶�� Left�� ������ȯ �ε� �������־ Left�� �ٶ󺸴� ������ ����.
	if (true == GameEngineInput::IsDown('A') || true == GameEngineInput::IsFree('D'))
	{
		Dir = PlayerDir::Left;
		/*ChangeAnimationState("Player_Left_Turning.bmp");
		if (MainRenderer->IsAnimationEnd())
		{
			ChangeAnimationState(CurState);
		}*/
		ChangeAnimationState(CurState);

		return;
	}

	// D�� ���Ȱų� A�� �����̸� Right�� ���� ��ȯ.
	if (true == GameEngineInput::IsDown('D') || true == GameEngineInput::IsFree('A'))
	{
		Dir = PlayerDir::Right;
		ChangeAnimationState(CurState);


		return;
	}
}

void Player::ChangeAnimationState(const std::string& _StateName)
{
	
	std::string AnimationName;

	switch (Dir)
	{
	case PlayerDir::Right:
		AnimationName = "Right_";
		break;
	case PlayerDir::Left:
		AnimationName = "Left_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}


void Player::LevelStart()
{
	// ���÷��̾���� �������� ������ �� �����ϱ� ������ �ٲ����� �� ������ �÷��̾��°� �˱�����
	// this �־��ִ°���
	MainPlayer = this; // MainPlayer�� �ڱ��ڽ�����
}

void Player::Render(float _Delta)
{
	// ȭ�� ������� ����
	//std::string Text = "";

	//Text += std::to_string(TestValue);

	//HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//TextOutA(dc, 2, 3, Text.c_str(), Text.size());

	// ���� �߽ɺ���
	HDC DoubleDC = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetMainCamera()->GetPos();

	Rectangle(DoubleDC, 
		ActorPos.iX() - 5,
		ActorPos.iY() - 5,
		ActorPos.iX() + 5,
		ActorPos.iY() + 5
		);

	/*std::string Text = "";
	Text += "�÷��̾� �׽�Ʈ �� : ";
	Text += std::to_string(1.0f / _Delta);
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	TextOutA(dc, 2, 3, Text.c_str(), static_cast<int>(Text.size()));*/

	//CollisionData Data;

	//Data.Pos = ActorCameraPos();
	//Data.Scale = { 5,5 };
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//Data.Pos = ActorCameraPos() + LeftCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	//Data.Pos = ActorCameraPos() + RightCheck;
	//Rectangle(dc, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());

	std::string MouseText = "MousePosition : \n";
	MouseText += GameEngineWindow::MainWindow.GetMousePos().ToString();
	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	TextOutA(dc, 2, 3, MouseText.c_str(), MouseText.size());

}
