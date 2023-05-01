#include "bMapPeglin.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bResources.h"
#include "bInput.h"
#include "bTime.h"
#include "bRigidbody.h"
#include "bSceneManager.h"

namespace b
{
	MapPeglin::MapPeglin()
		: mAnimator(nullptr)
		, mState(eMapPeglinState::Idle)
		, mRigidbody(nullptr)
		, target(Vector2::Zero)
		, dir(Vector2::Zero)
		, mTime(0.0f)
	{
	}

	MapPeglin::~MapPeglin()
	{
	}

	void MapPeglin::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Move", Vector2::Zero, 0.15f);

		mAnimator->Play(L"PeglinIdle", true);

		mState = eMapPeglinState::Idle;

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2::Zero);
		mRigidbody->SetGround(false);

		GameObject::Initialize();
	}

	void MapPeglin::Update()
	{
		GameObject::Update();

		switch (mState)
		{
		case b::MapPeglin::eMapPeglinState::Move:
			move();
			break;
		case b::MapPeglin::eMapPeglinState::Idle:
			idle();
			break;
		case b::MapPeglin::eMapPeglinState::Pass:
			pass();
			break;
		default:
			break;
		}

	}

	void MapPeglin::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// 820 625
	}

	void MapPeglin::Release()
	{
		GameObject::Release();
	}

	void MapPeglin::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 vel = mRigidbody->GetVelocity();
		vel -= dir * 5;

		mRigidbody->SetVelocity(vel);

		if (pos.x >= 795 && pos.x <= 815
			&& pos.y >= 580 && pos.y <= 595)
		{
			mAnimator->Play(L"PeglinIdle", true);
			mState = eMapPeglinState::Idle;
			vel = Vector2::Zero;
			mRigidbody->SetVelocity(Vector2::Zero);
			mState = eMapPeglinState::Pass;
		}
	}

	void MapPeglin::idle()
	{
		if (Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			Vector2 mousePos = Input::GetMousePos();

			if (mousePos.x >= 785 && mousePos.x <= 860
				&& mousePos.y >= 580 && mousePos.y <= 660)
			{
				mAnimator->Play(L"PeglinMove", true);
				Transform* tr = GetComponent<Transform>();
				Vector2 pos = tr->GetPos();
				target = Vector2(805.0f, 590.0f);
				dir = pos - target;
				dir.Normalize();
				mRigidbody->SetVelocity(dir * 100);
				mState = eMapPeglinState::Move;
				mTime = 0.0f;
			}
		}
	}

	void MapPeglin::pass()
	{
		mTime += Time::DeltaTime();

		if (mTime >= 1.5f)
		{
			SceneManager::LoadScene(eSceneType::Fight);
		}
	}
}