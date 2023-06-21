#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class PlayActor : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayActor();
	~PlayActor();

	// delete Function
	PlayActor(const PlayActor& _Other) = delete;
	PlayActor(PlayActor&& _Other) noexcept = delete;
	PlayActor& operator=(const PlayActor& _Other) = delete;
	PlayActor& operator=(PlayActor&& _Other) noexcept = delete;

	void Gravity(float _Delta);

	void CameraFocus();

	void GravityReset()
	{
		// 땅에 닿았으면 리셋하기
		GravityVector = float4::ZERO;
	}


	void GravityOff()
	{
		IsGravity = false;
	}

	void SetGroundTexture(const std::string& _GroundTextureName);

	float4 ActorCameraPos();

	void SetGravityVector(float4 _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	float4 GetGravityVector()
	{

		return GravityVector;

	}

	// 내 위치에서 땅에 닿았는지 안닿았는지
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	float GravityPower = 2000.0f; // 떨어지는 속력이 다르다면~

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsGravity = true;

	float JumpPower = 20.0f;

	// 맨 처음 모든 중력은 제로 그러다가 끌어당기면 걔한테 끌려감
	float4 GravityVector = float4::ZERO;

};

