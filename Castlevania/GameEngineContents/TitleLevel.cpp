#include "TitleLevel.h"
#include "TitleBack.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	CreateActor<TitleBack>();
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown('P'))
	{
		GameEngineCore::ChangeLevel("DebugLevel");
	}
}