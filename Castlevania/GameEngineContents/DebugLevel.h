#pragma once
#include <GameEngineCore/GameEngineLevel.h>


class DebugLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	DebugLevel();
	~DebugLevel();

	// delete Function
	DebugLevel(const DebugLevel& _Other) = delete;
	DebugLevel(DebugLevel&& _Other) noexcept = delete;
	DebugLevel& operator=(const DebugLevel& _Other) = delete;
	DebugLevel& operator=(DebugLevel&& _Other) noexcept = delete;


protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


private:
	class Map* DebugRoomPtr;
	class Player* LevelPlayer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

