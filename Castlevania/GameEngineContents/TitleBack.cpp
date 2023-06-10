#include "TitleBack.h"
#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#pragma comment(lib, "msimg32.lib")

TitleBack::TitleBack() 
{
}

TitleBack::~TitleBack() 
{
}

void TitleBack::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("BackGround1.bmp"))
	{

		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");

		GameEnginePath FolderPath = FilePath;

		FolderPath.MoveChild("ContentsResources\\Texture\\");
		ResourcesManager::GetInst().CreateSpriteFolder("FolderTitle", FolderPath.PlusFilePath("FolderTitle"));

		GameEngineRenderer* TitleRender = CreateRenderer(RenderOrder::BackGround);
		TitleRender->CreateAnimation("Title_Anim", "FolderTitle", 0, 8, 0.3f, true);
		TitleRender->ChangeAnimation("Title_Anim");
		SetPos({ 640.0f,400.0f});
	}
}