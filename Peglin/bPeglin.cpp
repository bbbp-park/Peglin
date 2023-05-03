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
#include "bHPbar.h"
#include "bText.h"
#include "bSound.h"

namespace b
{
	Peglin::ePeglinState Peglin::mState = Peglin::ePeglinState::Idle;
	int Peglin::hp = 0;

	Peglin::Peglin()
		: mAnimator(nullptr)
		, mGround(nullptr)
		, mOrb(nullptr)
		, mBombs({})
		, hpBar(nullptr)
		, maxHp(100)
		, delay(false)
		, hpText(nullptr)
	{
	}

	Peglin::~Peglin()
	{
	}

	void Peglin::Initialize()
	{
		mGround = object::Instantiate<Ground>(Vector2(0.0f, 220.0f), eLayerType::Wall);
		mGround->SetName(L"Ground");

		hp = maxHp;
		hpBar = object::Instantiate<HpBar>(Vector2(126.0f, 290.0f), Vector2(3.7f, 3.7f), eLayerType::UI);
		hpBar->SetHpType(eHpType::Player);

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

		hpBar->SetHp(hp);
		hpBar->SetMaxHp(maxHp);

		if (Input::GetKeyDown(eKeyCode::Q))
			hp -= 10;

		if (hp <= 0 && mState == ePeglinState::Idle)
		{
			hp = 0;
			mAnimator->Play(L"PeglinDeath", true);
			mState = ePeglinState::Death;
		}

		if (!delay)
		{
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
	}

	void Peglin::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Vector2 pos = Input::GetMousePos();
		wchar_t x[50] = {};
		swprintf_s(x, 50, L"%f", pos.x);
		TextOut(hdc, 800, 0, x, wcsnlen_s(x, 50));
		wchar_t y[50] = {};
		swprintf_s(y, 50, L"%f", pos.y);
		TextOut(hdc, 800, 40, y, wcsnlen_s(y, 50));
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
		Sound* player_hit = Resources::Load<Sound>(L"player_hit", L"..\\Resources\\audio\\player_hit.wav");
		player_hit->Play(false);
	}

	void Peglin::shoot_ball()
	{
		delay = true;

		if (delay)
			mAnimator->Play(L"PeglinShoot Ball", false);

	}

	void Peglin::shoot_bomb()
	{
		int bCnt = Orb::GetBombCnt();
		delay = true;

		if (delay)
		{
			if (bCnt > 0)
			{
				mAnimator->Play(L"PeglinShoot Bomb", false);
			}

			else
			{
				mState = ePeglinState::ShootBall;
				delay = false;
			}
		}
	}

	void Peglin::death()
	{
	}

	void Peglin::idle()
	{
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

		object::Instantiate<Ball>(pos, Vector2(3.0f, 3.0f), eLayerType::Orb);

		mAnimator->Play(L"PeglinIdle", true);
		mState = ePeglinState::Idle;
		delay = false;
	}

	void Peglin::shoot_bombCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 40.0f;

		int bCnt = Orb::GetBombCnt();

		if (mState == ePeglinState::ShootBomb)
		{
			for (int i = 0; i < bCnt; i++)
			{
				pos.x += i * 10.0f;
				mBombs.push_back(object::Instantiate<Bomb>(pos, Vector2(3.0f, 3.0f), eLayerType::Bomb));

				mGround->SetGameObject(mBombs[i]);
			}
		}

		delay = false;
	}
}