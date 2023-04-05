#pragma once

enum class eSceneType
{
	Title,
	Map,
	Fight,
	MiniMap,
	Ending,
	Tool,
	End,
};

enum class eLayerType
{
	BG,
	Tile,
	Monster,
	Player,
	Ball,
	Bomb,
	Ground,
	Test,
	Effect,
	UI,
	End
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Rigidbody,
	Audio,
	End,
};