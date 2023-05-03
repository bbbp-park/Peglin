#include "bBomb.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"
#include "bRigidbody.h"
#include "bCollider.h"
#include "bAnimator.h"
#include "bObject.h"
#include "bExplosion.h"
#include "bMonster.h"
#include "bFightScene.h"
#include "bPeglin.h"
#include "bText.h"
#include "bSound.h"

namespace b
{
	Bomb::Bomb()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mText(nullptr)
	{
	}

	Bomb::~Bomb()
	{
	}

	void Bomb::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Ball\\Bomb\\Hit bomb", Vector2::Zero, 0.1f);

		mAnimator->Play(L"BombHit bomb", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-10.0f, -10.0f));
		collider->SetSize(Vector2(30.0f, 30.0f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);

		Vector2 velocity = mRigidbody->GetVelocity();

		velocity.x = 250.0f;
		velocity.y = -250.0f;

		mRigidbody->SetVelocity(velocity);
		mRigidbody->SetGround(false);

		GameObject::Initialize();
	}

	void Bomb::Update()
	{
		GameObject::Update();

	}

	void Bomb::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bomb::Release()
	{
		GameObject::Release();
	}

	void Bomb::OnCollisionEnter(Collider* other)
	{
		Vector2 velocity = mRigidbody->GetVelocity();

		velocity.x = 0.0f;
		mRigidbody->SetVelocity(velocity);

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos.x += 60.0f;
		pos.y += 120.0f;
		Sound* BombHitSoundDistort = Resources::Load<Sound>(L"BombHitSoundDistort", L"..\\Resources\\audio\\BombHitSoundDistort.wav");
		BombHitSoundDistort->Play(false);
		object::Instantiate<Explosion>(pos, Vector2(0.8f, 0.8f), eLayerType::Effect);

		std::vector<Monster*> mons = FightScene::GetMonsters();

		for (auto mon : mons)
		{
			int hp = mon->GetHp();
			hp -= 50;
			mon->SetHp(hp);

			Transform* tr = mon->GetComponent<Transform>();
			Vector2 pos = tr->GetPos();
			mText = object::Instantiate<Text>(eLayerType::UI);
			wchar_t str[10] = L"50";
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

		Peglin::SetPeglinState(Peglin::ePeglinState::ShootBall);
		object::Destory(this);
	}

	void Bomb::OnCollisionStay(Collider* other)
	{
	}

	void Bomb::OnCollisionExit(Collider* other)
	{
	}
}