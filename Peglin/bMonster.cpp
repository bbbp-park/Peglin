#include "bMonster.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bCollider.h"
#include "bBall.h"
#include "bFightScene.h"
#include "bRigidbody.h"
#include "bTime.h"
#include "bHPbar.h"
#include "bObject.h"
#include "bOrb.h"
#include "bPeglin.h"
#include "bText.h"
#include "bSound.h"
#include "bResources.h"

namespace b
{
	bool isMove = false;

	Monster::Monster()
		: mAnimator(nullptr)
		, mType(eMonsterType::Stump)
		, mRigidbody(nullptr)
		, eventComplete(false)
		, mState(eMonsterState::Idle)
		, hpBar(nullptr)
		, bombCnt(0)
		, hpText(nullptr)
		, mText(nullptr)
	{
		// stump
		mInfo.maxHp = 200;
		mInfo.hp = mInfo.maxHp;
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
		Vector2 pos = tr->GetPos();

		hpBar = object::Instantiate<HpBar>(pos, Vector2(3.7f, 3.7f), eLayerType::UI);
		hpBar->SetHpType(eHpType::Monster);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(5.0f, -20.0f));
		collider->SetSize(Vector2(50.0f, 60.0f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetGround(true);
		mRigidbody->SetMass(1.0f);

		GameObject::Initialize();
	}

	void Monster::Update()
	{
		GameObject::Update();

		hpBar->SetHp(mInfo.hp);
		hpBar->SetMaxHp(mInfo.maxHp);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		/*Transform* hpTr = hpText->GetComponent<Transform>();
		hpTr->SetPos(pos);*/

		Vector2 velocity = mRigidbody->GetVelocity();

		Vector2 peglinPos = Vector2(450.0f, 200.0f);
		distance = pos - peglinPos;
		this;
		if (mInfo.hp <= 0)
		{
			if (mType == eMonsterType::Stump)
			{
				if (mState != eMonsterState::Dead)
				{
					mState = eMonsterState::Dead;
					mInfo.hp = mInfo.maxHp;
					mAnimator->Play(L"StumpDie", false);
				}
				else
				{
					//object::Destory(hpBar);
					this->SetState(eState::Death);
					return;
				}
			}
		}
		else
		{
			if (distance.x <= 60.0f && distance.x >= 45.0f)
			{
				velocity = Vector2::Zero;
				isMove = false;
				mRigidbody->SetVelocity(velocity);
			}


		}

		Transform* hpTr = hpBar->GetComponent<Transform>();
		Vector2 hpPos = pos;
		hpTr->SetPos(hpPos);
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
		eColliderType type = other->GetColliderType();

		if (type == eColliderType::ball)
		{
			// ������ ����
			Ball* ball = dynamic_cast<Ball*>(other->GetOwner());
			int power = ball->GetPower();
			mInfo.hp -= power;

			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			mText = object::Instantiate<Text>(eLayerType::UI);
			wchar_t str[10] = L"";
			int num = swprintf_s(str, 10, L"%d", power);
			mText->SetText(*str);
			mText->SetIsChange(false);
			mText->SetTextHeight(35);
			mText->SetDelete(true);
			mText->SetActive(true);
			Transform* textTr = mText->GetComponent<Transform>();
			pos.x += 40;
			pos.y -= 50;
			textTr->SetPos(pos);
		}
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
		mAnimator->Play(L"StumpDead", false);
		mInfo.hp = mInfo.maxHp;

		eventComplete = true;

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 15;
		pos.y += 8;
		tr->SetPos(pos);
	}

	void Monster::StumpMoveCompleteEvent()
	{
		Vector2 velocity = mRigidbody->GetVelocity();

		velocity = Vector2::Zero;
		isMove = false;
		mRigidbody->SetVelocity(velocity);

		mAnimator->Play(L"StumpIdle", true);
		mState = eMonsterState::Idle;

		eventComplete = true;
	}

	void Monster::StumpAttackCompleteEvent()
	{
		mAnimator->Play(L"StumpIdle", true);
		mState = eMonsterState::Idle;

		eventComplete = true;

		Peglin::CalHp(mInfo.power);
	}

	void Monster::StartEvent()
	{
		if (this->GetState() != eState::Active || mState == eMonsterState::Dead)
		{
			eventComplete = true;
			return;
		}

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 peglinPos = Vector2(450.0f, 200.0f);
		distance = pos - peglinPos;

			if (mType == eMonsterType::Stump)
			{
				if (mState == eMonsterState::Dead)
				{
					eventComplete = true;
					return;
				}

				if (mState == eMonsterState::Idle)
				{
					if (distance.x <= 60.0f && distance.x >= 45.0f)
					{
						// ��۸����� �Ÿ� ��� �� �����̰ų� ����
						mAnimator->Play(L"StumpAttack", false);
						mState = eMonsterState::Attack;
						attack();
						Sound* swish_melee = Resources::Load<Sound>(L"swish_melee", L"..\\Resources\\audio\\swish_melee.wav");
						swish_melee->Play(false);
					}
					else
					{
						mAnimator->Play(L"StumpMove", true);
						mState = eMonsterState::Move;
						move();
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