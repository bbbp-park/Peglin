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
#include "bBossScene.h"
#include "bPlantBlob.h"

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
		, mInfo()
		, mCollider(nullptr)
		, pattern(0)
	{

	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		// stump
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Attack", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Move", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Die", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Stump\\Dead", Vector2::Zero, 0.15f);

		mAnimator->GetCompleteEvent(L"StumpDie") = std::bind(&Monster::StumpDeathCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"StumpMove") = std::bind(&Monster::StumpMoveCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"StumpAttack") = std::bind(&Monster::StumpAttackCompleteEvent, this);

		// Tree
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Tree", Vector2::Zero, 0.1f);

		// Mole
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Boss\\Mole\\Attack", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Boss\\Mole\\Dive", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Boss\\Mole\\Emerge", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Boss\\Mole\\Idle", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Boss\\Mole\\Hit", Vector2::Zero, 0.15f);

		mAnimator->GetCompleteEvent(L"MoleDive") = std::bind(&Monster::MoleDiveCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"MoleEmerge") = std::bind(&Monster::MoleEmergeCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"MoleAttack") = std::bind(&Monster::MoleAttackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"MoleHit") = std::bind(&Monster::MoleHitCompleteEvent, this);

		// SmallPlant
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\SmallPlant\\Attack", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\SmallPlant\\Idle", Vector2::Zero, 0.15f); 
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\SmallPlant\\Summon", Vector2::Zero, 0.15f);
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\SmallPlant\\Die", Vector2::Zero, 0.15f);
		

		mAnimator->GetCompleteEvent(L"SmallPlantAttack") = std::bind(&Monster::SmallPlantAttackCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"SmallPlantDie") = std::bind(&Monster::SmallPlantDieCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"SmallPlantSummon") = std::bind(&Monster::SmallPlantSummonCompleteEvent, this);
		mAnimator->GetCompleteEvent(L"SmallPlantIdle") = std::bind(&Monster::SmallPlantIdleCompleteEvent, this);
		

		mAnimator->Play(L"StumpIdle", true);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		hpBar = object::Instantiate<HpBar>(pos, Vector2(3.7f, 3.7f), eLayerType::UI);
		hpBar->SetHpType(eHpType::Monster);

		mCollider = AddComponent<Collider>();

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
			mInfo.hp = 0;

			if (mType == eMonsterType::Stump)
			{
				if (mState != eMonsterState::Dead)
				{
					mState = eMonsterState::Dead;
					mRigidbody->SetVelocity(Vector2::Zero);
					mInfo.hp = mInfo.maxHp;
					mAnimator->Play(L"StumpDie", false);
				}
				else
				{

					hpBar->SetState(eState::Pause);
					//object::Destory(this);
					this->SetState(eState::Pause);
					return;
				}
			}
			else if (mType == eMonsterType::Tree)
			{
				hpBar->SetState(eState::Pause);
				//object::Destory(this);
				this->SetState(eState::Pause);
				return;
			}
			else if (mType == eMonsterType::SmallPlant)
			{
				mAnimator->Play(L"SmallPlantDie", false);
			}
			else if (mType == eMonsterType::Mole)
			{
				Sound* Animals_Monster_Death = Resources::Load<Sound>(L"world1_fight", L"..\\Resources\\audio\\Animals_Monster_Death.wav");
				Animals_Monster_Death->Play(false);
				SceneManager::LoadScene(eSceneType::Ending);
			}
		}
		else
		{
			if (mType == eMonsterType::Stump)
			{
				if (distance.x <= 60.0f && distance.x >= 45.0f)
				{
					velocity = Vector2::Zero;
					isMove = false;
					mRigidbody->SetVelocity(velocity);
				}
			}


		}

		Transform* hpTr = hpBar->GetComponent<Transform>();
		Vector2 hpPos = Vector2::Zero;
		if (mType == eMonsterType::Stump)
			hpPos = pos;
		else if (mType == eMonsterType::Tree)
		{
			hpPos.x = pos.x + 60.0f;
			hpPos.y = 160.0f;
		}
		else if (mType == eMonsterType::Mole)
		{
			hpPos = Vector2(1330.0f, 290.0f);
		}
		else if (mType == eMonsterType::SmallPlant)
		{
			hpPos = pos;
		}
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

		if (type == eColliderType::ball && this->GetState() == eState::Active) 
		{
			// 데미지 적용
			Ball* ball = dynamic_cast<Ball*>(other->GetOwner());
			int power = ball->GetPower();
			
			if (mType == eMonsterType::Mole)
				mAnimator->Play(L"MoleHit", false);

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
			mCollider->SetCenter(Vector2(5.0f, -20.0f));
			mCollider->SetSize(Vector2(50.0f, 60.0f));

			mAnimator->Play(L"StumpIdle", true);
			// stump
			mInfo.maxHp = 200;
			mInfo.hp = mInfo.maxHp;
			mInfo.power = 2;
		}
		else if (mType == eMonsterType::Tree)
		{
			mCollider->SetCenter(Vector2(60.0f, 80.0f));
			mCollider->SetSize(Vector2(50.0f, 140.0f));

			mAnimator->Play(L"MonsterTree", true);
			mInfo.maxHp = 999;
			mInfo.hp = mInfo.maxHp;
			mInfo.power = 0;
		}
		else if (mType == eMonsterType::Mole)
		{
			mCollider->SetCenter(Vector2(10.0f, 0.0f));
			mCollider->SetSize(Vector2(100.0f, 80.0f));

			mAnimator->Play(L"MoleIdle", true);
			mInfo.maxHp = 602;
			mInfo.hp = mInfo.maxHp;
			mInfo.power = 10;
			mInfo.turn = 0;
			hpBar->SetHpType(eHpType::Mole);
		}
		else if (mType == eMonsterType::SmallPlant)
		{
			mCollider->SetCenter(Vector2(0.0f, -10.0f));
			mCollider->SetSize(Vector2(50.0f, 60.0f));

			mAnimator->Play(L"SmallPlantSummon", false);
			mInfo.maxHp = 60;
			mInfo.hp = mInfo.maxHp;
			mInfo.power = 3;
			mInfo.turn = 0;
		}
	}

	void Monster::StumpDeathCompleteEvent()
	{
		mAnimator->Play(L"StumpDead", false);
		mInfo.hp = mInfo.maxHp;

		eventComplete = true;

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 30.0f;
		pos.y += 10.0f;
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

	void Monster::MoleDiveCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		Vector2 spPos = pos;
		spPos += 25;
		//BossScene::AddMonster(spPos, eMonsterType::SmallPlant);

		if (pattern == 2)
		{
			pos.x = 1275.0f - (50.0f * mInfo.turn);
		}
		else if (pattern == 1)
		{
			pos.x = 510.0f;
		}
		tr->SetPos(pos);


		mAnimator->Play(L"MoleEmerge", true);
	}

	void Monster::MoleEmergeCompleteEvent()
	{
		mAnimator->Play(L"MoleIdle", true);
		mState = eMonsterState::Idle;
		mInfo.turn++;
		eventComplete = true;
	}

	void Monster::MoleAttackCompleteEvent()
	{
		mAnimator->Play(L"MoleDive", false);
		mState = eMonsterState::Move;

		//eventComplete = true;

	}

	void Monster::MoleHitCompleteEvent()
	{
		mAnimator->Play(L"MoleIdle", true);
		mState = eMonsterState::Idle;
	}

	void Monster::SmallPlantAttackCompleteEvent()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		PlantBlob* blob = object::Instantiate<PlantBlob>(pos, eLayerType::Blob);
		mAnimator->Play(L"SmallPlantIdle", true);
		mState = eMonsterState::Idle;
		eventComplete = true;
	}

	void Monster::SmallPlantDieCompleteEvent()
	{
		object::Destory(this);
		hpBar->SetState(eState::Pause);
	}

	void Monster::SmallPlantIdleCompleteEvent()
	{
		//if (mInfo.turn % 2 == 0)
		//{
		//	eventComplete = true;
		//	mInfo.turn++;
		//	mState = eMonsterState::Idle;
		//}
	}

	void Monster::SmallPlantSummonCompleteEvent()
	{
		mAnimator->Play(L"SmallPlantIdle", true);
	}

	void Monster::StartEvent()
	{
		if (eventComplete)
		{
			eventComplete = false;
			return;
		}

		/*if (this->GetState() != eState::Active || mState == eMonsterState::Dead)
		{
			eventComplete = true;
			return;
		}*/

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
					// 페글린과의 거리 계산 후 움직이거나 공격
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
		else if (mType == eMonsterType::Tree)
		{
			eventComplete = true;
			return;
		}
		else if (mType == eMonsterType::Mole)
		{
			if (mState == eMonsterState::Idle)
			{
				std::vector<Monster*> mons = BossScene::GetMonsters();
				pattern = mInfo.turn % 3;
				if (pattern == 0)
				{
					// pass
					mInfo.turn++;
					eventComplete = true;
					return;
				}
				else if (pattern == 1)
				{
					// dive, summon plant, move to peglin
					// if plant's pos is nearby peglin >> don't dive
					bool exist = false;

					for (Monster* mon : mons)
					{
						if (mon->GetMonsterType() != eMonsterType::SmallPlant)
							continue;

						Transform* tr = mon->GetComponent<Transform>();
						Vector2 pos = tr->GetPos();

						if (pos.x >= 500.0f && pos.x <= 600.0f)
						{
							exist = true;
							break;
						}
					}

					if (exist)
						eventComplete = true;
					else
					{
						mAnimator->Play(L"MoleDive", false);
						mState = eMonsterState::Move;
						//move();
					}
				}
				else if (pattern == 2)
				{
					// if face to peglin >> attack
					mAnimator->Play(L"MoleAttack", false);

					Peglin::CalHp(mInfo.power);
					mState = eMonsterState::Attack;
				}
			}
		}
		else if (mType == eMonsterType::SmallPlant)
		{
			if (mState == eMonsterState::Idle)
			{
				if (mInfo.turn % 2 == 1)
				{
					// 두 턴마다 공격
					mAnimator->Play(L"SmallPlantAttack", false);
					mState = eMonsterState::Attack;
				}
				else
				{
					//eventComplete = true;
					//mAnimator->Play(L"SmallPlantIdle", true);
					//mState = eMonsterState::Move;
					mInfo.turn++;
					eventComplete = true;
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

		if (mType == eMonsterType::Stump)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			mRigidbody->SetGround(true);
			velocity.x = -130.0f;
			velocity.y = 0.0f;
			mRigidbody->SetVelocity(velocity);
		}
		else if (mType == eMonsterType::Mole)
		{

		}
	}

}