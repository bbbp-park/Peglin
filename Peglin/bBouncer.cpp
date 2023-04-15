#include "bBouncer.h"
#include "bResources.h"
#include "bImage.h"
#include "bTransform.h"
#include "bOrb.h"
#include "bRigidbody.h"
#include "bCollider.h"

namespace b
{
	Bouncer::Bouncer()
		: bouncerImage(nullptr)
		, tileImage(nullptr)
		, bouncerCol(nullptr)
		, tileCol(nullptr)
		, mOrb(nullptr)
	{
	}

	Bouncer::~Bouncer()
	{
	}

	void Bouncer::Initialize()
	{
		bouncerImage = Resources::Load<Image>(L"Bouncer", L"..\\Resources\\sprite\\Background\\bouncer.bmp");
		tileImage = Resources::Load<Image>(L"BouncerTile", L"..\\Resources\\sprite\\Background\\tileset_33.bmp");

		Transform* tr = GetComponent<Transform>();

		Vector2 bPos;
		bPos.x = tr->GetPos().x;
		bPos.y = tr->GetPos().y;

		Vector2 tPos;
		tPos.x = bPos.x + 15;
		tPos.y = bPos.y + (bouncerImage->GetHeight() * 3);

		bouncerCol = AddComponent<Collider>();
		bouncerCol->SetSize(Vector2(bouncerImage->GetWidth() * 3 + 10, bouncerImage->GetHeight() * 3 + 10));


		/*tileCol = AddComponent<Collider>();
		tileCol->SetSize(Vector2(tileImage->GetWidth() * 3, tileImage->GetHeight() * 3));*/
		//bouncerCol->SetShape()

		
		GameObject::Initialize();
	}

	void Bouncer::Update()
	{
		GameObject::Update();

		Transform* orbTr = mOrb->GetComponent<Transform>();
		
	}

	void Bouncer::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();

		Vector2 bPos;
		bPos.x = tr->GetPos().x;
		bPos.y = tr->GetPos().y;

		Vector2 tPos;
		tPos.x = bPos.x + 15;
		tPos.y = bPos.y + (bouncerImage->GetHeight() * 3);

		TransparentBlt(hdc, bPos.x, bPos.y
			, bouncerImage->GetWidth() * 3, bouncerImage->GetHeight() * 3
			, bouncerImage->GetHdc()
			, 0, 0
			, bouncerImage->GetWidth(), bouncerImage->GetHeight()
			, RGB(255, 0, 255));

		TransparentBlt(hdc, tPos.x, tPos.y
			, tileImage->GetWidth() * 3, tileImage->GetHeight() * 3
			, tileImage->GetHdc()
			, 0, 0
			, tileImage->GetWidth(), tileImage->GetHeight()
			, RGB(255, 0, 255));
		
	}

	void Bouncer::Release()
	{
		GameObject::Release();
	}

	void Bouncer::OnCollisionEnter(Collider* other)
	{
	}

	void Bouncer::OnCollisionStay(Collider* other)
	{
	}

	void Bouncer::OnCollisionExit(Collider* other)
	{
	}
}