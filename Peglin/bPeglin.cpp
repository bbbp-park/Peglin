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

namespace b
{
	Peglin::Peglin()
	{
	}

	Peglin::~Peglin()
	{
	}

	void Peglin::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));
		//Image* mImage = Resources::Load<Image>(L"Peglin", L"..\\Resources\\sprite.bmp\\peglin.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Angel", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Death", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Move", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Ball", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Bomb", Vector2::Zero, 0.15f);


		mAnimator->Play(L"PeglinIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(mAnimator->GetCenterPos());
		collider->SetSize(Vector2(65.0f, 70.0f));

		

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
		case b::Peglin::ePeglinState::Move:
			move();
			break;
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

	void Peglin::move()
	{
		if (Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::W))
		{
			mState = ePeglinState::Idle;
			//mAnimator->Play(L"Idle", true);
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

		if (Input::GetKeyDown(eKeyCode::I))
		{
			mAnimator->Play(L"PeglinIdle", true);
			mState = ePeglinState::Idle;
		}
	}

	void Peglin::shoot_ball()
	{
		/*Transform* tr = GetComponent<Transform>();

		Scene* curScene = SceneManager::GetActiveScene();
		Ball* ball = new Ball();
		ball->GetComponent<Transform>()->SetPos(tr->GetPos());
		curScene->AddGameObject(ball, eLayerType::Ball);*/

		if (Input::GetKeyDown(eKeyCode::I))
		{
			mAnimator->Play(L"PeglinIdle", true);
			mState = ePeglinState::Idle;
		}

		/*mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;*/
	}

	void Peglin::shoot_bomb()
	{
		if (Input::GetKeyDown(eKeyCode::I))
		{
			mAnimator->Play(L"PeglinIdle", true);
			mState = ePeglinState::Idle;
		}
	}

	void Peglin::death()
	{
		if (Input::GetKeyDown(eKeyCode::I))
		{
			mAnimator->Play(L"PeglinIdle", true);
			mState = ePeglinState::Idle;
		}
		mAnimator->Play(L"PeglinAngel", true);
	}

	void Peglin::idle()
	{
		if (Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::W))
		{
			mState = ePeglinState::Move;
			//mAnimator->Play(L"FowardRun", true);
		}

		/*if (Input::GetKeyDown(eKeyCode::M))
		{
			mAnimator->Play(L"PeglinMove", true);
			mState = ePeglinState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::K))
		{
			mAnimator->Play(L"PeglinShoot Ball", false);
			mState = ePeglinState::ShootBall;
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			mAnimator->Play(L"PeglinDeath", false);
			mState = ePeglinState::Death;
		}
		if (Input::GetKeyDown(eKeyCode::B))
		{
			mAnimator->Play(L"PeglinShoot Bomb", true);
			mState = ePeglinState::ShootBomb;
		}*/
	}
}