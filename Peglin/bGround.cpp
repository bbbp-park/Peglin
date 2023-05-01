#include "bGround.h"
#include "bCollider.h"
#include "bTransform.h"
#include "bRigidbody.h"
#include "bBomb.h"
#include "bOrb.h"

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
		mCollider->SetSize(Vector2(1600.0f, 45.0f));

		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::Release()
	{
		GameObject::Release();
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		//if (other->GetName() == L"Bomb")
		//{
		//	Bomb* obj = dynamic_cast<Bomb*>(other->GetOwner());

		//	if (obj == nullptr)
		//		return;

		//	Rigidbody* rb = obj->GetComponent<Rigidbody>();
		//	rb->SetGround(true);

		//	Collider* bombCol = obj->GetComponent<Collider>();
		//	Vector2 bombPos = bombCol->GetPos();

		//	Collider* groundCol = this->GetComponent<Collider>();
		//	Vector2 groundPos = groundCol->GetPos();

		//	float fLen = fabs(bombPos.y - groundPos.y);
		//	float fSize = (bombCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);


		//	if (fLen < fSize)
		//	{
		//		Transform* objTr = obj->GetComponent<Transform>();
		//		Transform* groundTr = this->GetComponent<Transform>();

		//		Vector2 objPos = objTr->GetPos();
		//		Vector2 groundPos = groundTr->GetPos();

		//		if (obj->GetName() == L"Bomb")
		//		{
		//			objPos -= (fSize - fLen) - 1.0f;
		//			objTr->SetPos(objPos);
		//		}
		//	}
		//}

		Orb* orb = dynamic_cast<Orb*>(other->GetOwner());

		if (orb == nullptr)
			return;

		Rigidbody* rb = orb->GetComponent<Rigidbody>();
		//rb->SetGround(true);

		Collider* orbCol = orb->GetComponent<Collider>();
		Vector2 orbPos = orbCol->GetCenterPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetCenterPos();
		groundPos.x = 0.0f;

		if (orb->GetIsShoot())
		{
			Vector2 dir = orbPos;
			dir -= groundPos;
			dir.Normalize();

			Vector2 vel = rb->GetVelocity();

			vel.y *= -1.0f;
			rb->SetVelocity(vel);
		}

	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
	}
}