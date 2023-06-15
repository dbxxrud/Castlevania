#pragma once

// Ό³Έν :
class MonsterState
{
public:
	// constrcuter destructer
	MonsterState();
	~MonsterState();

	// delete Function
	MonsterState(const MonsterState& _Other) = delete;
	MonsterState(MonsterState&& _Other) noexcept = delete;
	MonsterState& operator=(const MonsterState& _Other) = delete;
	MonsterState& operator=(MonsterState&& _Other) noexcept = delete;

protected:

private:

};

