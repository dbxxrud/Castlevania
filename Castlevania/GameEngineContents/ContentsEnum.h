#pragma once

enum class UpdateOrder
{
	Player,
	Monster
};

enum class RenderOrder
{
	BackGround,
	Item,
	Play,
	PlayUI
};

enum class CollisionOrder
{
	Camera,
	Map,
	Potal,
	PlayerBody,
	MonsterBody,
};
