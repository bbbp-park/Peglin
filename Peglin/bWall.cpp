#include "bWall.h"
#include "bCollider.h"
#include "bOrb.h"
#include "bTransform.h"

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
		Orb* orb = dynamic_cast<Orb*>(other->GetOwner());

		if (orb == nullptr)
			return;

		Rigidbody* rb = orb->GetComponent<Rigidbody>();

		Collider* orbCol = orb->GetComponent<Collider>();
		Vector2 orbPos = orbCol->GetPos();

		Collider* wallCol = this->GetComponent<Collider>();
		Vector2 wallPos = wallCol->GetPos();
		if (this->GetName() == L"LeftWall")
			wallPos.x += wallCol->GetSize().x;

		Vector2 fLen;
		fLen.x = fabs(orbPos.x - wallPos.x);
		fLen.y = fabs(orbPos.y - wallPos.y);

		Vector2 fSize;
		fSize.x = (orbCol->GetSize().x / 2.0f) + (wallCol->GetSize().x / 2.0f);
		fSize.y = (orbCol->GetSize().y / 2.0f) + (wallCol->GetSize().y / 2.0f);

		
		if (fLen.x < fSize.x && orb->GetIsShoot())
		{
			Transform* orbTr = orb->GetComponent<Transform>();
			Vector2 pos = orbTr->GetPos();

			if (this->GetName() == L"LeftWall")
			{
				pos += (fSize.x - fLen.x) + 1.0f;
				orbTr->SetPos(pos);
			}

			if (this->GetName() == L"RightWall")
			{
				pos -= (fSize.x - fLen.x) - 1.0f;
				orbTr->SetPos(pos);
			}

			

		}

		/*if (fLen.y < fSize.y)
		{
			Transform* orbTr = orb->GetComponent<Transform>();
			Vector2 orbPos = orbTr->GetPos();

			if (orbPos.y < (220.0f + 45.0f))
			{
				orbPos -= (fSize.y - fLen.y) + 1.0f;
			}
			orbTr->SetPos(orbPos);
		}*/

	}

	void Wall::OnCollisionStay(Collider* other)
	{
	}

	void Wall::OnCollisionExit(Collider* other)
	{
	}
}