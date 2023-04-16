#include "bBouncerTile.h"
#include "bResources.h"
#include "bTransform.h"
#include "bImage.h"
#include "bCollider.h"
#include "bOrb.h"

namespace b
{
	BouncerTile::BouncerTile()
		: mOrb(nullptr)
		, tileImage(nullptr)
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

		Transform* orbTr = mOrb->GetComponent<Transform>();
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
		int a = 0;
	}

	void BouncerTile::OnCollisionStay(Collider* other)
	{
	}

	void BouncerTile::OnCollisionExit(Collider* other)
	{
	}
}