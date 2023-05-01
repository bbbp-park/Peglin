#include "bBall.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"
#include "bObject.h"
#include "bCollider.h"
#include "bRigidbody.h"
#include "bFightScene.h"
#include "bMonster.h"

namespace b
{
	int Ball::power = 0;

	Ball::Ball()
		: mImage(nullptr)
		, mRigidbody(nullptr)
	{
	}

	Ball::~Ball()
	{
	}

	void Ball::Initialize()
	{
		//mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\rock.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(5.0f, 5.0f));
		collider->SetSize(Vector2(35.0f, 35.0f));
		collider->SetColliderType(eColliderType::ball);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetGravity(Vector2::Zero);
		mRigidbody->SetMass(1.0f);

		GameObject::Initialize();
	}

	void Ball::Update()
	{
		GameObject::Update();


		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.x += 100.0f;

		mRigidbody->SetVelocity(velocity);
		
	}

	void Ball::Render(HDC hdc)
	{
		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\Rock\\rock.bmp");

		Transform* tr = GetComponent<Transform>();
		
		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Ball::Release()
	{
		GameObject::Release();
	}

	void Ball::OnCollisionEnter(Collider* other)
	{
		object::Destory(this);
		FightScene::SetPlayerTurn(false);
	}

	void Ball::OnCollisionStay(Collider* other)
	{
	}

	void Ball::OnCollisionExit(Collider* other)
	{
	}
}