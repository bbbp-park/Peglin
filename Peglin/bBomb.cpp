#include "bBomb.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"

namespace b
{
	bool bTop = false;

	Bomb::Bomb()
		: mImage(nullptr)
	{
	}

	Bomb::~Bomb()
	{
	}

	void Bomb::Initialize()
	{
		bTop = false;
		GameObject::Initialize();
	}

	void Bomb::Update()
	{
		Transform* tr = GetComponent<Transform>();

		Vector2 pos = tr->GetPos();

		if (pos.x < 900.0f)
			pos.x += 180.0f * Time::DeltaTime();

		if (pos.y < 100.0f)
			bTop = true;

		if (bTop)
			pos.y += 120.0f * Time::DeltaTime();
		else
			pos.y -= 120.0f * Time::DeltaTime();

		tr->SetPos(pos);

		GameObject::Update();
	}

	void Bomb::Render(HDC hdc)
	{
		mImage = Resources::Load<Image>(L"Bomb", L"..\\Resources\\sprite\\Ball\\Bomb\\Hit bomb 2.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Bomb::Release()
	{
		GameObject::Release();
	}

	void Bomb::OnCollisionEnter(Collider* other)
	{
	}

	void Bomb::OnCollisionStay(Collider* other)
	{
	}

	void Bomb::OnCollisionExit(Collider* other)
	{
	}
}