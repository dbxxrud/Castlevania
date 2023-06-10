#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <string>

// Ό³Έν :
class Map : public GameEngineActor
{
public:
	// constrcuter destructer
	Map();
	~Map();

	// delete Function
	Map(const Map& _Other) = delete;
	Map(Map&& _Other) noexcept = delete;
	Map& operator=(const Map& _Other) = delete;
	Map& operator=(Map&& _Other) noexcept = delete;

	void Init(const std::string& _FileName, const std::string& _DebugFileName);

	void SwitchRender();

protected:

private:
	bool SwitchRenderValue = true;
	std::string FileName;
	class GameEngineRenderer* Renderer;
	class GameEngineRenderer* DebugRenderer;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

