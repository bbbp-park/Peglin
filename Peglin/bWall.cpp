#include "bWall.h"
#include "bCollider.h"
#include "bOrb.h"
#include "bTransform.h"
#include "bRigidbody.h"

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
		mCollider->SetColliderType(Collider::eColliderType::wall);
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
		Orb* orb = dynamic_cast<Orb*>(other->GetOwner());

		if (orb == nullptr)
			return;

		Rigidbody* rb = orb->GetComponent<Rigidbody>();

		Collider* orbCol = orb->GetComponent<Collider>();
		Vector2 orbPos = orbCol->GetCenterPos();

		Collider* wallCol = this->GetComponent<Collider>();
		Vector2 wallPos = wallCol->GetCenterPos();
		wallPos.y = 0.0f;
		
		if (orb->GetIsShoot())
		{
			Vector2 dir = orbPos;
			dir -= wallPos;
			dir.Normalize();

			Vector2 vel = rb->GetVelocity();
			vel.x *= -1.0f;
			//Vector2 rVec = math::Reflect(vel, dir);
			//rVec *= rb->GetPower();
			//rVec *= -1.0f;
			rb->SetVelocity(vel);
		}
	}

	void Wall::OnCollisionStay(Collider* other)
	{
	}

	void Wall::OnCollisionExit(Collider* other)
	{
	}
}