#include "bWall.h"
#include "bCollider.h"

namespace b
{
	Wall::Wall()
		: mGameObject(nullptr)
		, mCollider(nullptr)
	{
	}

	Wall::~Wall()
	{
	}

	void Wall::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(50.0f, 680.0f));
		
		GameObject::Initialize();
	}

	void Wall::Update()
	{
		GameObject::Update();
	}

	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Wall::Release()
	{
		GameObject::Release();
	}

	void Wall::OnCollisionEnter(Collider* other)
	{
	}

	void Wall::OnCollisionStay(Collider* other)
	{
	}

	void Wall::OnCollisionExit(Collider* other)
	{
	}
}