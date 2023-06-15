#pragma once
#include "PlayActor.h"

// Ό³Έν :
class Item : public PlayActor
{
private:
	static std::list<Item*> AllItems;

public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	GameEngineRenderer* ItemFireRenderer = nullptr;

protected:

private:
	void Start() override;

	void Update(float _Delta) override;


};

