#pragma once
#include "PlayActor.h"

enum class Monsters
{
	M_BladeMaster,
	

};

// 설명 :
class Monster : public PlayActor
{
private:
	static std::list<Monster*> AllMonster;

public:
	static void AllMonsterDeath(); // 모든 몬스터 다 죽여

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