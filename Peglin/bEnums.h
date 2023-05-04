#pragma once

enum class eSceneType
{
	Title,
	Map,
	Fight,
	Boss,
	Ending,
	Tool,
	End,
};

enum class eLayerType
{
	BG,
	//Tile,
	Monster,
	Blob,
	Player,
	Bomb,
	Wall,
	Orb,
	Peg,
	UI,
	Effect,
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
	wall,
	bomb,
	null,
};

enum class ePegType
{
	Normal,
	Bomb,
	ActiveBomb,
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
	Mole,
};

enum class eMonsterType
{
	Stump,
	Tree,
	Mole,
	SmallPlant,
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