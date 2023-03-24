#include "bMapPeglin.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bResources.h"
#include "bInput.h"
#include "bTime.h"

namespace b
{
	MapPeglin::MapPeglin()
	{
	}

	MapPeglin::~MapPeglin()
	{
	}

	void MapPeglin::Initialize()
	{
		/*Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.2f, 2.2f));
		tr->SetPos(Vector2(820.0f, 240.0f));;*/

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Move", Vector2::Zero, 0.15f);

		mAnimator->Play(L"PeglinIdle", true);

		mState = eMapPeglinState::Idle;

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
		default:
			break;
		}
	}

	void MapPeglin::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void MapPeglin::Release()
	{
		GameObject::Release();
	}

	void MapPeglin::move()
	{
		if (Input::GetKeyUp(eKeyCode::W)
			|| Input::GetKeyUp(eKeyCode::D)
			|| Input::GetKeyUp(eKeyCode::S)
			|| Input::GetKeyUp(eKeyCode::A))
		{
			mState = eMapPeglinState::Idle;
			mAnimator->Play(L"PeglinIdle", true);
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

	void MapPeglin::idle()
	{
		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::S)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			mState = eMapPeglinState::Move;
			mAnimator->Play(L"PeglinMove", true);
		}
	}
}