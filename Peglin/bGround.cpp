#include "bGround.h"
#include "bCollider.h"
#include "bTransform.h"
#include "bRigidbody.h"
#include "bBomb.h"

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
		mCollider->SetSize(Vector2(1600.0f, 40.0f));

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
		Bomb* bomb = dynamic_cast<Bomb*>(other->GetOwner());

		if (bomb == nullptr)
			return;

		Rigidbody* rb = bomb->GetComponent<Rigidbody>();
		rb->SetGround(true);

		Collider* bombCol = bomb->GetComponent<Collider>();
		Vector2 bombPos = bombCol->GetPos();

		Collider* groundCol = this->GetComponent<Collider>();
		Vector2 groundPos = groundCol->GetPos();

		float fLen = fabs(bombPos.y - groundPos.y);
		float fSize = (bombCol->GetSize().y / 2.0f) + (groundCol->GetSize().y / 2.0f);

		if (fLen < fSize)
		{
			Transform* bombTr = bomb->GetComponent<Transform>();
			Transform* groundTr = this->GetComponent<Transform>();

			Vector2 bombPos = bombTr->GetPos();
			Vector2 groundPos = groundTr->GetPos();

			bombPos -= (fSize - fLen) - 1.0f;
			bombTr->SetPos(bombPos);
		}
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}

	void Ground::OnCollisionExit(Collider* other)
	{
	}
}