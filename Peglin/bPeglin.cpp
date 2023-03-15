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
		tr->SetScale(Vector2(3.0f, 3.0f));
		tr->SetPos(Vector2(430.0f, 150.0f));
		tr->SetName(L"peglin's transform");
		//Image* mImage = Resources::Load<Image>(L"Peglin", L"..\\Resources\\sprite.bmp\\peglin.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Angel", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Death", Vector2::Zero, 0.15f);
		/*mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Move", Vector2::Zero, 0.15f);*/
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Ball", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Shoot Bomb", Vector2::Zero, 0.15f);

		/*Collider* collider = AddComponent<Collider>();
		collider->SetCenter(mAnimator->GetCenterPos());
		collider->SetSize(Vector2(65.0f, 70.0f));*/
		
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
		
	}
}