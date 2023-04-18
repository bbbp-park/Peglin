#include "bBouncer.h"
#include "bResources.h"
#include "bImage.h"
#include "bTransform.h"
#include "bOrb.h"
#include "bRigidbody.h"
#include "bCollider.h"
#include "bInput.h"

namespace b
{
	Bouncer::Bouncer()
		: bouncerImage(nullptr)
		, bouncerCol(nullptr)
		, mOrb(nullptr)
	{
	}

	Bouncer::~Bouncer()
	{
	}

	void Bouncer::Initialize()
	{
		bouncerImage = Resources::Load<Image>(L"Bouncer", L"..\\Resources\\sprite\\Background\\bouncer.bmp");

		//Transform* tr = GetComponent<Transform>();

		//Vector2 bPos = tr->GetPos();

		/*Vector2 tPos;
		tPos.x = bPos.x + 15;
		tPos.y = bPos.y + (bouncerImage->GetHeight() * 3);*/

		bouncerCol = AddComponent<Collider>();
		bouncerCol->SetSize(Vector2(bouncerImage->GetWidth() * 3 + 10, bouncerImage->GetHeight() * 3 + 10));


		//tileCol = AddComponent<Collider>();
		//tileCol->SetSize(Vector2(tileImage->GetWidth() * 3, tileImage->GetHeight() * 3));
		bouncerCol->SetShape(eColliderType::Ellipse);
		bouncerCol->SetCenter(Vector2(-2.0f, 0.0f));
		bouncerCol->SetSize(Vector2(bouncerImage->GetWidth() * 3, bouncerImage->GetHeight() * 3));

		
		GameObject::Initialize();
	}

	void Bouncer::Update()
	{
		GameObject::Update();
	}

	void Bouncer::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();

		Vector2 bPos = tr->GetPos();

		TransparentBlt(hdc, bPos.x, bPos.y
			, bouncerImage->GetWidth() * 3, bouncerImage->GetHeight() * 3
			, bouncerImage->GetHdc()
			, 0, 0
			, bouncerImage->GetWidth(), bouncerImage->GetHeight()
			, RGB(255, 0, 255));
	}

	void Bouncer::Release()
	{
		GameObject::Release();
	}

	void Bouncer::OnCollisionEnter(Collider* other)
	{
		Orb* orb = dynamic_cast<Orb*>(other->GetOwner());

		if (orb == nullptr)
			return;

		Rigidbody* rb = orb->GetComponent<Rigidbody>();

		Collider* orbCol = orb->GetComponent<Collider>();
		Vector2 orbPos = orbCol->GetCenterPos();

		Collider* bCol = this->GetComponent<Collider>();
		Vector2 bPos = bCol->GetCenterPos();

		if (orb->GetIsShoot())
		{
			Vector2 dir = orbPos;
			dir -= bPos;
			dir.Normalize();

			Vector2 vel = rb->GetVelocity();

			Vector2 rVec = math::Reflect(vel, dir);
			rVec *= rb->GetPower();
			rb->SetVelocity(rVec);
		}
	}

	void Bouncer::OnCollisionStay(Collider* other)
	{
	}

	void Bouncer::OnCollisionExit(Collider* other)
	{
	}
}