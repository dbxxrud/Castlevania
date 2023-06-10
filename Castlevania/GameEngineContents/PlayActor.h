#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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
		// ���� ������� �����ϱ�
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

	// �� ��ġ���� ���� ��Ҵ��� �ȴ�Ҵ���
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);

	float GravityPower = 8.0f; // �������� �ӷ��� �ٸ��ٸ�~

protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsGravity = true;

	//float GravityPower = 8.0f; // �������� �ӷ��� �ٸ��ٸ�~

	float JumpPower = 10.0f;

	// �� ó�� ��� �߷��� ���� �׷��ٰ� ������� ������ ������
	float4 GravityVector = float4::ZERO;

};