#include "bGround.h"
#include "bCollider.h"
#include "bTransform.h"
#include "bRigidBody.h"

namespace b
{
	Ground::Ground()
		: mCollider(nullptr)
		, mGameObject(nullptr)
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(1600.0f, 50.0f));

		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();

		if (mGameObject != nullptr)
		{
			Transform* objTr = mGameObject->GetComponent<Transform>();

			RigidBody* rb = mGameObject->GetComponent<RigidBody>();

			rb->SetGround(false);
		}
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();


	}

	void Ground::Release()
	{
		GameObject::Release();
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
	}
}