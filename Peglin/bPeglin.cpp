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
#include "bOrb.h"
#include "bFightScene.h"

namespace b
{
	int Peglin::hp = 100;
	Peglin::ePeglinState Peglin::mState = Peglin::ePeglinState::Idle;

	float time = 0.0f;

	Peglin::Peglin()
		: mAnimator(nullptr)
		, mGround(nullptr)
		, mOrb(nullptr)
		, mBombs({})
		, delay(false)
	{
	}

	Peglin::~Peglin()
	{
	}

	void Peglin::Initialize()
	{
		mGround = object::Instantiate<Ground>(Vector2(0.0f, 220.0f), eLayerType::Wall);
		mGround->SetName(L"Ground");

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

		if (hp <= 0 && mState == ePeglinState::Idle)
		{
			mAnimator->Play(L"PeglinDeath", true);
			mState = ePeglinState::Death;
		}

		if (!delay)
		{
			switch (mState)
			{
			case b::Peglin::ePeglinState::ShootBall:
				time += Time::DeltaTime();
				if (time >= 0.8f)
					shoot_ball();
				break;
			case b::Peglin::ePeglinState::ShootBomb:
				time += Time::DeltaTime();
				if (time >= 0.8f)
					shoot_bomb();
				if (time >= 3.0f)
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

	}

	void Peglin::OnCollisionStay(Collider* other)
	{
	}

	void Peglin::OnCollisionExit(Collider* other)
	{
	}

	void Peglin::CalHp(int damage)
	{
		hp -= damage;
	}


	void Peglin::shoot_ball()
	{
		delay = true;

		if (delay)
			mAnimator->Play(L"PeglinShoot Ball", true);
	}

	void Peglin::shoot_bomb()
	{
		int bCnt = Orb::GetBombCnt();
		delay = true;

		if (delay)
		{
			if (bCnt > 0)
				mAnimator->Play(L"PeglinShoot Bomb", true);
			else
			{
				mState = ePeglinState::ShootBall;
				delay = false;
			}
		}
	}

	void Peglin::death()
	{
		//mAnimator->Play(L"PeglinDeath", true);
	}

	void Peglin::idle()
	{
		

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			//mAnimator->Play(L"PeglinShoot Ball", false);
			mState = ePeglinState::ShootBall;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			mAnimator->Play(L"PeglinShoot Bomb", true);
			mState = ePeglinState::ShootBomb;
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			hp = 0;
		}

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

		object::Instantiate<Ball>(pos, Vector2(3.0f, 3.0f), eLayerType::Ball);

		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;
		delay = false;
		time = 0.0f;

		/*FightScene::GetPlayerTurn(true);*/
	}

	void Peglin::shoot_bombCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 40.0f;

		int bCnt = Orb::GetBombCnt();

		//mBombs.resize(bCnt);
		if (mState == ePeglinState::ShootBomb)
		{
			for (int i = 0; i < bCnt; i++)
			{
				pos.x += i * 10.0f;
				mBombs.push_back(object::Instantiate<Bomb>(pos, Vector2(3.0f, 3.0f), eLayerType::Bomb));
				//mBombs[i]->SetName(L"Bomb");

				mGround->SetGameObject(mBombs[i]);
			}
		}

		mState = ePeglinState::ShootBall;
		delay = false;
		time = 0.0f;
	}
}