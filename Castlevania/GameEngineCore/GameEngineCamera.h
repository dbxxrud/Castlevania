#pragma once
#include "GameEngineRenderer.h"
#include <map>
#include <list>

// 설명 :
class GameEngineRenderer;
class GameEngineCamera
{
	friend class GameEngineRenderer;
	friend class GameEngineActor;
	friend class GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineCamera();
	~GameEngineCamera();

	// delete Function
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _Value)
	{
		Pos = _Value;
	}

	void AddPos(const float4& _Value)
	{
		Pos += _Value;
	}


protected:

private:
	float4 Pos = float4::ZERO;
	std::map<int, std::list<GameEngineRenderer*>> Renderers;
	// 렌더러의 역할은 화면에 이미지 띄우기! 그걸 카메라가 가졌음! 그래서 이미지를 띄어주는건 카메라와 렌더러가 하는것

	// 아무나 막쓰면 안된다! 정석적으로 CreateRenderer를 통해서 만들어졌을때만 들어가야 하기 때문에
	void PushRenderer(GameEngineRenderer* _Renderer, int _Order);
	void Release();

	void OverRelease();
	void Render(float _Delta);
};

