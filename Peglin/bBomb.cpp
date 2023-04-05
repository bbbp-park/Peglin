#include "bBomb.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"
#include "bRigidBody.h"
#include "bCollider.h"

namespace b
{
	bool bTop = false;

	Bomb::Bomb()
		: mImage(nullptr)
		, mRigidbody(nullptr)
	{
	}

	Bomb::~Bomb()
	{
	}

	void Bomb::Initialize()
	{
		bTop = false;

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(5.0f, 5.0f));
		collider->SetSize(Vector2(35.0f, 35.0f));

		mRigidbody = AddComponent<RigidBody>();
		mRigidbody->SetMass(1.0f);

		GameObject::Initialize();
	}

	void Bomb::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		Vector2 pos = tr->GetPos();


		Vector2 velocity = mRigidbody->GetVelocity();
		
		if (pos.x < 850.0f)
			velocity.x += 10.0f;
		else
			velocity.x = 0.0f;
		
		mRigidbody->SetVelocity(velocity);
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
		mRigidbody->SetGround(true);
	}

	void Bomb::OnCollisionStay(Collider* other)
	{
	}

	void Bomb::OnCollisionExit(Collider* other)
	{
	}
}