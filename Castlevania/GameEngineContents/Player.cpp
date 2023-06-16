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

Player* Player::MainPlayer = nullptr; // 플레이어를 알수있도록

Player::Player()
{
}

Player::~Player()
{
}

void Player::Start()
{
	if(false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp")) // 이래야 로드가 한번만
	{
		// 무조건 자동으로 현재 실행중인 위치가 된다.
		// 이 객체는 경로다
		// 시작위치  C:\47th\WinAPI_Castlevania\Castlevania\CastlevaniaApp
		// 도착위치 C:\47th\WinAPI_Castlevania\Castlevania\ContentsResources\Texture\Player
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Player\\");

		ResourcesManager::GetInst().TextureLoad(FilePath.PlusFilePath("HP_Bar.bmp"));


		// 아이들
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Idle.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Idle.bmp"), 5, 2);

		// 이동
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Move.bmp"), 5, 7);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Move.bmp"), 5, 7);

		// 돌기
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Turning.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Turning.bmp"), 5, 2);

		// 점프
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Jump.bmp"), 5, 2);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Jump.bmp"), 5, 2);
		
		// 더블점프
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_DoubleJump.bmp"), 5, 1);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_DoubleJump.bmp"), 5, 1);

		// 앉기
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Ducking.bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Ducking.bmp"), 5, 4);


		// 낙하
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Falling.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Falling.bmp"), 5, 3);

		// 소드공격
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Attack.bmp"), 5, 4);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Attack.bmp"), 5, 4);

		// 않기공격
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_DuckingAttack.bmp"), 5, 3);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_DuckingAttack.bmp"), 5, 3);

		// 박쥐모드
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Left_Bat.bmp"), 5, 6);
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Player_Right_Bat.bmp"), 5, 6);

		// 박쥐모드 움직임
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
		// 충돌체 생성
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
		, CollisionType::Rect // 나를 사각형으로 봐줘
		, CollisionType::Rect // 상대도 사각형으로 봐줘
	))
	{
		for (size_t i = 0; i < _Col.size(); i++)
		{
			GameEngineCollision* Collison = _Col[i];

			GameEngineActor* Actor = Collison->GetActor();

			Actor->Death();
		}
		// 나는 몬스터랑 충돌한거야.
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

	CameraFocus(); // 카메라 중앙으로 옴 플레이어는 0,0에 있는거임
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

	// A가 눌렸거나 D가 프리이라면 Left로 방향전환 인데 가만히있어도 Left를 바라보는 현상이 생김.
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

	// D가 눌렸거나 A가 프리이면 Right로 방향 전환.
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
	// 각플레이어들은 레벨마다 존재할 수 있으니까 레벨이 바꼈을때 그 레벨의 플레이어라는걸 알기위해
	// this 넣어주는거임
	MainPlayer = this; // MainPlayer를 자기자신으로
}

void Player::Render(float _Delta)
{
	// 화면 글자출력 예제
	//std::string Text = "";

	//Text += std::to_string(TestValue);

	//HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	//TextOutA(dc, 2, 3, Text.c_str(), Text.size());

	// 엑터 중심보기
	HDC DoubleDC = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();
	float4 ActorPos = GetPos() - GetLevel()->GetMainCamera()->GetPos();

	Rectangle(DoubleDC, 
		ActorPos.iX() - 5,
		ActorPos.iY() - 5,
		ActorPos.iX() + 5,
		ActorPos.iY() + 5
		);

	/*std::string Text = "";
	Text += "플레이어 테스트 값 : ";
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
