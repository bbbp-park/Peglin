#include "bPeglin.h"
#include "bTime.h"
#include "bSceneManager.h";
#include "bInput.h";
#include "bResources.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bBall.h"
#include "bCollider.h"
#include "bScene.h"
#include "bObject.h"
#include "bBomb.h"
#include "bGround.h"
#include "bBouncer.h"

namespace b
{
	Peglin::Peglin()
		: mAnimator(nullptr)
		, mState(ePeglinState::Idle)
		, mGround(nullptr)
		, mOrb(nullptr)
	{
	}

	Peglin::~Peglin()
	{
	}

	void Peglin::Initialize()
	{
		mGround = object::Instantiate<Ground>(Vector2(0.0f, 220.0f), eLayerType::Ground);
		
		/*bouncer = object::Instantiate<Bouncer>(Vector2(800.0f, 791.0f), eLayerType::Wall);

		mOrb = object::Instantiate<Orb>(Vector2(900.0f, 350.0f), Vector2(2.0f, 2.0f), eLayerType::Orb);

		bouncer->SetOrb(mOrb);*/

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Angel", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Death", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Ball", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Bomb", Vector2::Zero, 0.15f);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(0.0f, -10.0f));
		collider->SetSize(Vector2(70.0f, 70.0f));

		mAnimator->GetCompleteEvent(L"PeglinDeath") = std::bind(&Peglin::deathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PeglinShoot Ball") = std::bind(&Peglin::shoot_ballCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"PeglinShoot Bomb") = std::bind(&Peglin::shoot_bombCompleteEvent, this);
		
		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;

		GameObject::Initialize();
	}

	void Peglin::Update()
	{
		GameObject::Update();


		switch (mState)
		{
		case b::Peglin::ePeglinState::ShootBall:
			shoot_ball();
			break;
		case b::Peglin::ePeglinState::ShootBomb:
			shoot_bomb();
			break;
		case b::Peglin::ePeglinState::Death:
			death();
			break;
		case b::Peglin::ePeglinState::Idle:
			idle();
			break;
		default:
			break;
		}
	}

	void Peglin::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Peglin::Release()
	{
		GameObject::Release();
	}

	void Peglin::OnCollisionEnter(Collider* other)
	{
		int a = 0;
	}

	void Peglin::OnCollisionStay(Collider* other)
	{
	}

	void Peglin::OnCollisionExit(Collider* other)
	{
	}


	void Peglin::shoot_ball()
	{
		
	}

	void Peglin::shoot_bomb()
	{
		
	}

	void Peglin::death()
	{
		
	}

	void Peglin::idle()
	{
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			mAnimator->Play(L"PeglinShoot Ball", true);
			mState = ePeglinState::ShootBall;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mAnimator->Play(L"PeglinShoot Bomb", true);
			mState = ePeglinState::ShootBomb;
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			mAnimator->Play(L"PeglinDeath", true);
			mState = ePeglinState::Death;
		}

		
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

		//if (Input::GetKey(eKeyCode::A))
		//	pos.x -= 100.0f * Time::DeltaTime();

		//if (Input::GetKey(eKeyCode::D))
		//	pos.x += 100.0f * Time::DeltaTime();

		//if (Input::GetKey(eKeyCode::W))
		//	pos.y -= 100.0f * Time::DeltaTime();

		//if (Input::GetKey(eKeyCode::S))
		//	pos.y += 100.0f * Time::DeltaTime();

		//tr->SetPos(pos);
	}

	void Peglin::deathCompleteEvent()
	{
		mAnimator->Play(L"PeglinAngel", true);
		mState = ePeglinState::Death;
	}

	void Peglin::shoot_ballCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		//pos.x += 40.0f;

		object::Instantiate<Ball>(pos, Vector2(3.0f, 3.0f), eLayerType::Ball);

		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;
	}

	void Peglin::shoot_bombCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 40.0f;

		Bomb* mBomb = object::Instantiate<Bomb>(pos, Vector2(3.0f, 3.0f), eLayerType::Bomb);

		mGround->SetGameObject(mBomb);

		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;
	}
}