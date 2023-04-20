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
	Wall,
	Orb,
	Peg,
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

enum class eColliderType
{
	Ellipse,
	Rectangle,
};

enum class ePegType
{
	Normal,
	Bomb,
	Crit,
	Red,
	Refresh,
	SmallRect,
	Null,
	End,
};