#pragma once
#include <GameEngineCore/GameEngineCore.h>
// 설명 :
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

	// 행동한고.
	void Update(float _Delta) override;

	// 그려지고.
	void Render(float _Delta) override;

	// 정리된다.
	void Release() override;
};

