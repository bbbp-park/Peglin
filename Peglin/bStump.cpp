#include "bStump.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bCollider.h"
#include "bBall.h"
#include "bFightScene.h"

namespace b
{
	bool delay = false;

	Stump::Stump()
		: mAnimator(nullptr)
		, mInfo()
		, mState(eStumpState::Idle)
	{
	}

	Stump::~Stump()
	{
	}

	void Stump::Initialize()
	{
		/*Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(800.0f, 240.0f));
		tr->SetScale(Vector2(3.0f, 3.0f));*/

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Attack", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Move", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Die", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Dead", Vector2::Zero, 0.15f);

		mAnimator->Play(L"StumpIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, -20.0f));
		collider->SetSize(Vector2(60.0f, 60.0f));

		mInfo.hp = 200;
		mInfo.power = 2;

		GameObject::Initialize();
	}

	void Stump::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case b::Stump::eStumpState::Attack:
			attack();
			break;
		case b::Stump::eStumpState::Death:
			death();
			break;
		case b::Stump::eStumpState::Idle:
			idle();
			break;
		case b::Stump::eStumpState::Move:
			move();
			break;
		default:
			break;
		}
	}

	void Stump::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Stump::Release()
	{
		GameObject::Release();
	}

	void Stump::OnCollisionEnter(Collider* other)
	{
		
	}

	void Stump::OnCollisionStay(Collider* other)
	{
	}

	void Stump::OnCollisionExit(Collider* other)
	{
	}

	void Stump::attack()
	{
	}

	void Stump::death()
	{
	}

	void Stump::idle()
	{
	}

	void Stump::move()
	{
	}
}