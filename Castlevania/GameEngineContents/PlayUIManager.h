#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class PlayUIManager : public GameEngineActor
{
public:
	static PlayUIManager* UI; // 플레이어가 UI에 간섭하고 싶을 수 있으니가
public:
	// constrcuter destructer
	PlayUIManager();
	~PlayUIManager();

	// delete Function
	PlayUIManager(const PlayUIManager& _Other) = delete;
	PlayUIManager(PlayUIManager&& _Other) noexcept = delete;
	PlayUIManager& operator=(const PlayUIManager& _Other) = delete;
	PlayUIManager& operator=(PlayUIManager&& _Other) noexcept = delete;

protected:
	void Start() override;


private:

};

