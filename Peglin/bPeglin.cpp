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

namespace b
{
	Peglin::Peglin()
		: mAnimator(nullptr)
	{
	}

	Peglin::~Peglin()
	{
	}

	void Peglin::Initialize()
	{
		/*Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.0f, 3.0f));
		tr->SetPos(Vector2(430.0f, 240.0f));
		tr->SetName(L"peglin's transform");*/

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Angel", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Death", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Ball", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Bomb", Vector2::Zero, 0.15f);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-40.0f, -80.0f));
		collider->SetSize(Vector2(80.0f, 80.0f));

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

		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPos();

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





		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (Input::GetKey(eKeyCode::A))
			pos.x -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::D))
			pos.x += 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::W))
			pos.y -= 100.0f * Time::DeltaTime();

		if (Input::GetKey(eKeyCode::S))
			pos.y += 100.0f * Time::DeltaTime();

		tr->SetPos(pos);
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
		pos.x += 40.0f;
		pos.y -= 40.0f;

		Scene* curScene = SceneManager::GetActiveScene();

		/*Ball* ball = new Ball();
		
		ball->GetComponent<Transform>()->SetPos(pos);
		ball->GetComponent<Transform>()->SetScale(Vector2(4.0f, 4.0f));
		curScene->AddGameObject(ball, eLayerType::Ball);*/
		object::Instantiate<Ball>(pos, eLayerType::Ball);


		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;
	}

	void Peglin::shoot_bombCompleteEvent()
	{
		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;
	}
}