#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class MainStageLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MainStageLevel();
	~MainStageLevel();

	// delete Function
	MainStageLevel(const MainStageLevel& _Other) = delete;
	MainStageLevel(MainStageLevel&& _Other) noexcept = delete;
	MainStageLevel& operator=(const MainStageLevel& _Other) = delete;
	MainStageLevel& operator=(MainStageLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	class Map* BackGroundPtr;
	class Player* LevelPlayer;
	class GameEngineCollision* CameraCollision;

};

