#include "Item.h"
#include <GameEngineCore/GameEngineRenderer.h>
#include "ContentsEnum.h"
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>

std::list<Item*> Item::AllItems;

Item::Item() 
{
	AllItems.push_back(this);
}

Item::~Item() 
{
}

void Item::Start()
{
	if (false == ResourcesManager::GetInst().IsLoadTexture("Test.Bmp"))
	{
		GameEnginePath FilePath;
		FilePath.SetCurrentPath();
		FilePath.MoveParentToExistsChild("ContentsResources");
		FilePath.MoveChild("ContentsResources\\Texture\\Items\\");
		ResourcesManager::GetInst().CreateSpriteSheet(FilePath.PlusFilePath("Item_Fire.bmp"), 5, 1);


		{
			ItemFireRenderer = CreateRenderer(RenderOrder::Item);
			ItemFireRenderer->CreateAnimation("Item_Fire", "Item_Fire.bmp", 0, 4, 0.09f, true);
			ItemFireRenderer->ChangeAnimation("Item_Fire");

			ItemFireRenderer->SetRenderScale({ 880.0f, 800.0f });

		}
	}
	{
		// GameEngineCollision* ItemFireColl = CreateCollision(CollisionOrder::)
	}

}

void Item::Update(float _Delta)
{
}

