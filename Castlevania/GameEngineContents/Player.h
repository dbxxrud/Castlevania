#pragma once
#include "PlayActor.h"

enum class PlayerState
{
	Idle,
	Run,
	Jump,
	Ducking,
	Fall,
	Attack,
	DuckingAttack,
	Max, // �Ϲ������� ������� �ʴ� ��.
};

enum class PlayerDir
{
	Right,
	Left,
	Max,
};


// ���� : PlayActor�� GameEngineActor�� ��ӹ����鼭 PlayActor�� ��ɵ� ���� �޴´�
class Player : public PlayActor
{
public:
	static Player* MainPlayer;

public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	GameEngineRenderer* MainRenderer = nullptr;

	void StateUpdate(float _Delta);

	void IdleStart();
	void RunStart();
	void JumpStart();
	void DuckingStart();
	void FallingStart();
	void AttackStart();
	void DuckingAttackStart();

	// Ŭ������ ���� �ǰ�.
	void IdleUpdate(float _Delta);
	void RunUpdate(float _Delta);
	void JumpUpdate(float _Delta);
	void DuckingUpdate(float _Delta);
	void FallingUpdate(float _Delta);
	void AttackUpdate(float _Delta);
	void DuckingAttackUpdate(float _Delta);

	void ChanageState(PlayerState State);

	PlayerState State = PlayerState::Max;
	PlayerDir Dir = PlayerDir::Left;
	std::string CurState = "";

	bool IsJump = false;



	int TestValue = 0;

	GameEngineCollision* BodyCollsion = nullptr;

	void DirCheck();

	void ChangeAnimationState(const std::string& _StateName);




private:
	void LevelStart() override;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	////////////////////// DebugValue
	float4 LeftCheck = { -100.0f, -50.0f };
	float4 RightCheck = { 100.0f, -50.0f };
};