#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Stage1Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Stage1Level();
	~Stage1Level();

	// delete Function
	Stage1Level(const Stage1Level& _Other) = delete;
	Stage1Level(Stage1Level&& _Other) noexcept = delete;
	Stage1Level& operator=(const Stage1Level& _Other) = delete;
	Stage1Level& operator=(Stage1Level&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	class BackGround* BackGroundPtr;
	class Map* DebugRoomPtr;
	class Player* LevelPlayer = nullptr;
};

