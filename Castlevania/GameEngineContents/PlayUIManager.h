#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class PlayUIManager : public GameEngineActor
{
public:
	static PlayUIManager* UI; // �÷��̾ UI�� �����ϰ� ���� �� �����ϰ�
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

