#pragma once
#include "PlayActor.h"

enum class Monsters
{
	M_BladeMaster,
	

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


protected:

private:
	void Start() override;

	void Update(float _Delta) override;

};