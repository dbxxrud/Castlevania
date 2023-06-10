#pragma once
#include <GameEngineCore/GameEngineCore.h>
// ���� :
class CastlevaniaCore : public CoreProcess
{
public:
	// constrcuter destructer
	CastlevaniaCore();
	~CastlevaniaCore();

	// delete Function
	CastlevaniaCore(const CastlevaniaCore& _Other) = delete;
	CastlevaniaCore(CastlevaniaCore&& _Other) noexcept = delete;
	CastlevaniaCore& operator=(const CastlevaniaCore& _Other) = delete;
	CastlevaniaCore& operator=(CastlevaniaCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override;

	// �ൿ�Ѱ�.
	void Update(float _Delta) override;

	// �׷�����.
	void Render(float _Delta) override;

	// �����ȴ�.
	void Release() override;
};

