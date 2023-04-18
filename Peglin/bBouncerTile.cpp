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

		//Transform* tr = GetComponent<Transform>();

		//Vector2 tPos = tr->GetPos();

		tileCol = AddComponent<Collider>();
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
		Vector2 tilePos = tileCol->GetPos();

		Vector2 fLen;
		fLen.x = fabs(orbPos.x - tilePos.x);
		fLen.y = fabs(orbPos.y - tilePos.y);

		Vector2 fSize;
		fSize.x = (orbCol->GetSize().x / 2.0f) + (tileCol->GetSize().x / 2.0f);
		fSize.y = (orbCol->GetSize().y / 2.0f) + (tileCol->GetSize().y / 2.0f);

		if (orb->GetIsShoot())
		{
			Transform* orbTr = orb->GetComponent<Transform>();
			Vector2 pos = orbTr->GetPos();

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