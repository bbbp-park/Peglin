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

enum class eColliderShape
{
	Ellipse,
	Rectangle,
};

enum class eColliderType
{
	ball,
	peg,
	bouncer,
	wall,
	bomb,
	null,
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

enum class eHpType
{
	Player,
	Monster,
};

enum class eMonsterType
{
	Stump
};

enum class eMonsterState
{
	Idle,
	Move,
	Attack,
	Dead,
	None,
};

enum class eIconType
{
	Skull,
	Mole,
};