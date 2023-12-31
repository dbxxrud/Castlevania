#pragma once
#include <GameEngineCore/GameEngineCore.h>

// 설명 :
class ContentCore : public CoreProcess
{
public:
	// constrcuter destructer
	ContentCore();
	~ContentCore();

	// delete Function
	ContentCore(const ContentCore& _Other) = delete;
	ContentCore(ContentCore&& _Other) noexcept = delete;
	ContentCore& operator=(const ContentCore& _Other) = delete;
	ContentCore& operator=(ContentCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override; // CoreProcess 는 GameEngineObject를 상속받으니 정의내릴 수 있다

	// 행동한고.
	void Update() override;

	// 그려지고.
	void Render() override;

	// 정리된다.
	void Release() override;
};