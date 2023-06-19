#pragma once
#include "PlayActor.h"

enum class Monsters
{
	M_BladeMaster,
	

};

enum class MonsterDir
{
	Right,
	Left,
	Max,
};

// ���� :
class Monster : public PlayActor
{
private:
	static std::list<Monster*> AllMonster;

public:
	static void AllMonsterDeath(); // ��� ���� �� �׿�

public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

	GameEngineRenderer* BladeMasterRenderer = nullptr;
	//GameEngineRenderer* BladeMasterRenderer2 = nullptr;


	//GameEngineRenderer* ArmorLordRenderer = nullptr;

	void IdleStart();
	void RunStart();
	void JumpStart();
	void AttackStart();

	void ChangeAnimationState(const std::string& _StateName);

	MonsterDir Dir = MonsterDir::Right;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;

};