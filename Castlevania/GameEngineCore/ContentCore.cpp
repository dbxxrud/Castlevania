#include "ContentCore.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include ""


ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	// GameEngineCore::CreateLevel<EndingLevel>("EndingLevel");

	// 이 레벨이 화면에 보여라.
	GameEngineCore::ChangeLevel("PlayLevel");
}

// 행동한고.
void ContentCore::Update()
{
}

// 그려지고.
void ContentCore::Render()
{
}

// 정리된다.
void ContentCore::Release()
{
}