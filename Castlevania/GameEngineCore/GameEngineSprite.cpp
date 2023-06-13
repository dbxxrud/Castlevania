#include "GameEngineSprite.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include "ResourcesManager.h"

GameEngineSprite::GameEngineSprite()
{
}

GameEngineSprite::~GameEngineSprite()
{
}

void GameEngineSprite::CreateSpriteSheet(GameEngineWindowTexture* _Texture, int _XCount, int _YCount)
{
	float4 TexScale = _Texture->GetScale(); // 크기
	// 벡터쓸때무조건리사이즈
	AllSprite.resize(_XCount * _YCount);

	float4 StartPos = { float4::ZERO }; // 1000의 0부터 1000의 1000크기로 자르겠다
	float4 ImageSize = { TexScale.X / _XCount, TexScale.Y / _YCount }; // 이미지하나하나의 크기


	for (size_t y = 0; y < _YCount; y++)
	{
		for (size_t x = 0; x < _XCount; x++)
		{
			size_t Index = (y * _XCount) + x;

			AllSprite[Index].BaseTexture = _Texture;
			AllSprite[Index].RenderPos.X = StartPos.X;
			AllSprite[Index].RenderPos.Y = StartPos.Y;

			AllSprite[Index].RenderScale.X = ImageSize.X;
			AllSprite[Index].RenderScale.Y = ImageSize.Y;

			StartPos.X += ImageSize.X; // 이미지를 격자처럼 짜르는거임
		}
		// 그 다음 줄
		StartPos.X = 0;
		StartPos.Y += ImageSize.Y;
	}
}

void GameEngineSprite::CreateSpriteFolder(const std::string& _Path)
{
	GameEngineDirectory Dir = _Path;

	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".Bmp" });

	AllSprite.resize(Files.size());

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineWindowTexture* Texture = ResourcesManager::GetInst().TextureLoad(Files[i].GetStringPath());
		AllSprite[i].BaseTexture = Texture;
		AllSprite[i].RenderPos = float4::ZERO;
		AllSprite[i].RenderScale = Texture->GetScale();
	}
}

const GameEngineSprite::Sprite& GameEngineSprite::GetSprite(size_t _Index)
{
	static GameEngineSprite::Sprite ReturnValue;

	if (0 > _Index)
	{
		MsgBoxAssert("0보다 작은 스프라이트 인덱스 입니다.");
		return ReturnValue;
	}

	if (AllSprite.size() <= _Index)
	{
		MsgBoxAssert("스프라이트 인덱스 범위를 오버했습니다.");
		return ReturnValue;
	}

	return AllSprite[_Index];
}

