#pragma once
#include "GameEngineObject.h"

// 설명 :
class GameEngineActor;
class GameEngineActorSubObject : public GameEngineObject
{
	friend class GameEngineLevel;
	friend class GameEngineActor;

public:
	// constrcuter destructer
	GameEngineActorSubObject();
	~GameEngineActorSubObject();

	// delete Function
	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;


	bool IsDeath() override; // 콜리전과 렌더러의 공통기능

	GameEngineActor* GetActor()
	{
		return Master;
	}

protected:

private:
	GameEngineActor* Master = nullptr;
};