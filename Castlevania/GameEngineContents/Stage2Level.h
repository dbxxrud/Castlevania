#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class Stage2Level : public GameEngineLevel
{
public:
	// constrcuter destructer
	Stage2Level();
	~Stage2Level();

	// delete Function
	Stage2Level(const Stage2Level& _Other) = delete;
	Stage2Level(Stage2Level&& _Other) noexcept = delete;
	Stage2Level& operator=(const Stage2Level& _Other) = delete;
	Stage2Level& operator=(Stage2Level&& _Other) noexcept = delete;
protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	class Player* LevelPlayer = nullptr;
};

