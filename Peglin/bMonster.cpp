#include "bMonster.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bCollider.h"
#include "bBall.h"
#include "bFightScene.h"
#include "bRigidbody.h"
#include "bTime.h"

namespace b
{
	bool isMove = false;

	Monster::Monster()
		: mAnimator(nullptr)
		, mType(eMonsterType::Stump)
		, mRigidbody(nullptr)
		, idx(0)
		, mTime(0.0f)
		, eventComplete(false)
		, stumpState(eStumpState::Idle)
	{
		// stump
		mInfo.hp = 200;
		mInfo.power = 2;
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Idle", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Attack", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Move", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Die", Vector2::Zero, 0.1f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Dead", Vector2::Zero, 0.1f);

		mAnimator->Play(L"StumpIdle", true);

		mAnimator->GetCompleteEvent(L"StumpDie") = std::bind(&Monster::StumpDeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"StumpMove") = std::bind(&Monster::StumpMoveCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"StumpAttack") = std::bind(&Monster::StumpAttackCompleteEvent, this);

		Transform* tr = GetComponent<Transform>();

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(5.0f, -20.0f));
		collider->SetSize(Vector2(50.0f, 60.0f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetGround(true);
		mRigidbody->SetMass(1.0f);
		//mInfo.hp = 200;
		//mInfo.power = 2;

		GameObject::Initialize();
	}

	void Monster::Update()
	{
		GameObject::Update();

		Vector2 velocity = mRigidbody->GetVelocity();

		if (mType == eMonsterType::Stump)
		{
			if (mInfo.hp <= 0)
			{
				mAnimator->Play(L"StumpDie", false);
			}
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 peglinPos = Vector2(450.0f, 200.0f);
		distance = pos - peglinPos;

		if (distance.x <= 50.0f)
		{
			velocity = Vector2::Zero;
			isMove = false;
			mRigidbody->SetVelocity(velocity);
		}

		//bool flag = FightScene::GetPlayerTurn();
		//Vector2 peglinPos = Vector2(450.0f, 200.0f);
		//distance = pos - peglinPos;

		//if (!flag)
		//	mTime += Time::DeltaTime();

		//if (!flag && mTime >= idx * 4.0f)
		//{
		//	mAnimator->Play(L"StumpMove", false);
		//	move();
		//}
		//if (isMove)
		//{
		//	velocity.x -= 10.0f;
		//	//velocity.y = 0.0f;
		//	mRigidbody->SetVelocity(velocity);
		//}
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Monster::Release()
	{
		GameObject::Release();
	}

	void Monster::OnCollisionEnter(Collider* other)
	{

	}

	void Monster::OnCollisionStay(Collider* other)
	{
	}

	void Monster::OnCollisionExit(Collider* other)
	{
	}

	void Monster::SetMonsterType(eMonsterType type)
	{
		mType = type;

		if (mType == eMonsterType::Stump)
		{
			mAnimator->Play(L"StumpIdle", true);
		}
	}

	void Monster::StumpDeathCompleteEvent()
	{
		mAnimator->Play(L"StumpDead", true);
	}

	void Monster::StumpMoveCompleteEvent()
	{
		Vector2 velocity = mRigidbody->GetVelocity();

		velocity = Vector2::Zero;
		isMove = false;
		mRigidbody->SetVelocity(velocity);

		mAnimator->Play(L"StumpIdle", true);
		stumpState = eStumpState::Idle;

		eventComplete = true;
	}

	void Monster::StumpAttackCompleteEvent()
	{
		mAnimator->Play(L"StumpIdle", true);
		stumpState = eStumpState::Idle;

		eventComplete = true;
	}

	void Monster::StartEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 peglinPos = Vector2(450.0f, 200.0f);
		distance = pos - peglinPos;
		//Sleep(idx * 2000);

		if (mType == eMonsterType::Stump)
		{
			if (stumpState == eStumpState::Idle)
			{
				if (distance.x > 55.0f)
				{
					// 페글린과의 거리 계산 후 움직이거나 공격
					mAnimator->Play(L"StumpMove", true);
					stumpState = eStumpState::Move;
					move();
				}
				else
				{
					mAnimator->Play(L"StumpAttack", false);
					stumpState = eStumpState::Attack;
					attack();
				}
			}
		}
	}

	void Monster::attack()
	{

	}

	void Monster::death()
	{

	}

	void Monster::idle()
	{
		//mAnimator->Play(L"StumpIdle", true);
	}

	void Monster::move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		Vector2 velocity = mRigidbody->GetVelocity();
		mRigidbody->SetGround(true);
		velocity.x = -130.0f;
		velocity.y = 0.0f;
		mRigidbody->SetVelocity(velocity);
	}

}