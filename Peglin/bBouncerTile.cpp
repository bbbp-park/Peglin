#include "bBouncerTile.h"
#include "bResources.h"
#include "bTransform.h"
#include "bImage.h"
#include "bCollider.h"
#include "bOrb.h"
#include "bRigidbody.h"

namespace b
{
	BouncerTile::BouncerTile()
		: tileImage(nullptr)
		, tileCol(nullptr)
	{
	}

	BouncerTile::~BouncerTile()
	{
	}

	void BouncerTile::Initialize()
	{
		tileImage = Resources::Load<Image>(L"BouncerTile", L"..\\Resources\\sprite\\Background\\tileset_33.bmp");

		tileCol = AddComponent<Collider>();
		tileCol->SetColliderType(eColliderType::wall);
		tileCol->SetSize(Vector2(tileImage->GetWidth() * 3, tileImage->GetHeight() * 3));

		GameObject::Initialize();
	}

	void BouncerTile::Update()
	{
		GameObject::Update();
	}

	void BouncerTile::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();

		Vector2 tPos = tr->GetPos();

		TransparentBlt(hdc, tPos.x, tPos.y
			, tileImage->GetWidth() * 3, tileImage->GetHeight() * 3
			, tileImage->GetHdc()
			, 0, 0
			, tileImage->GetWidth(), tileImage->GetHeight()
			, RGB(255, 0, 255));
	}

	void BouncerTile::Release()
	{
		GameObject::Release();
	}

	void BouncerTile::OnCollisionEnter(Collider* other)
	{
		Orb* orb = dynamic_cast<Orb*>(other->GetOwner());

		if (orb == nullptr)
			return;

		Rigidbody* rb = orb->GetComponent<Rigidbody>();

		Collider* orbCol = orb->GetComponent<Collider>();
		Vector2 orbPos = orbCol->GetPos();

		Collider* tileCol = this->GetComponent<Collider>();
		Vector2 tilePos = tileCol->GetCenterPos();

		if (orb->GetIsShoot())
		{
			Vector2 dir = orbPos;
			dir -= tilePos;
			dir.Normalize();

			Vector2 vel = rb->GetVelocity();
			vel.x *= -1.0f;
			rb->SetVelocity(vel);
		}
	}

	void BouncerTile::OnCollisionStay(Collider* other)
	{
	}

	void BouncerTile::OnCollisionExit(Collider* other)
	{
	}
}