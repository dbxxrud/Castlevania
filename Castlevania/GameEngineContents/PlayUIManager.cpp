#include "PlayUIManager.h"

#include "ContentsEnum.h"
#include <GameEngineCore/GameEngineRenderer.h>

PlayUIManager* PlayUIManager::UI = nullptr;

PlayUIManager::PlayUIManager() 
{
	UI = this;
}

PlayUIManager::~PlayUIManager() 
{
}

void PlayUIManager::Start()
{
	// UI는 여기서 이제
	GameEngineRenderer* Ptr = CreateUIRenderer("HP_Bar.bmp", RenderOrder::Play);
	Ptr->SetRenderPos({ 155, 50 });
	Ptr->SetTexture("HP_Bar.bmp");
	Ptr->SetRenderScaleToTexture();

}

