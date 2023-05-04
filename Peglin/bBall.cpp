#include "bBall.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"
#include "bObject.h"
#include "bCollider.h"
#include "bRigidbody.h"
#include "bFightScene.h"
#include "bMonster.h"
#include "bSound.h"
#include "bBossScene.h"
#include "bScene.h"
#include "bSceneManager.h"

namespace b
{
	int Ball::power = 0;

	Ball::Ball()
		: mImage(nullptr)
		, mRigidbody(nullptr)
		, shoot(false)
	{
	}

	Ball::~Ball()
	{
	}

	void Ball::Initialize()
	{
		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\Rock\\rock.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(4.0f, 4.0f));

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(5.0f, 5.0f));
		collider->SetSize(Vector2(35.0f, 35.0f));
		collider->SetColliderType(eColliderType::ball);

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetGravity(Vector2::Zero);
		mRigidbody->SetMass(1.0f);

		GameObject::Initialize();
	}

	void Ball::Update()
	{
		GameObject::Update();

		if (shoot)
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x += 100.0f;

			mRigidbody->SetVelocity(velocity);
		}

	}

	void Ball::Render(HDC hdc)
	{
		//mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\Rock\\rock.bmp");
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();

		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

	}

	void Ball::Release()
	{
		GameObject::Release();
	}

	void Ball::OnCollisionEnter(Collider* other)
	{
		//GameObject* obj = other->GetOwner();
		//if (obj->GetState() == eState::Active)

		Sound* ExplodeyHitSound = Resources::Load<Sound>(L"ExplodeyHitSound", L"..\\Resources\\audio\\ExplodeyHitSound.wav");
		ExplodeyHitSound->Play(false);

		Scene* scene = SceneManager::GetActiveScene();
		if (scene->GetName() == L"FightScene")
		{
			FightScene::SetPlayerTurn(false);

		}
		else if (scene->GetName() == L"BossScene")
		{
			BossScene::SetPlayerTurn(false);

		}
		//object::Destory(this);
		mRigidbody->SetVelocity(Vector2::Zero);

		this->SetState(eState::Pause);
		return;

	}

	void Ball::OnCollisionStay(Collider* other)
	{
	}

	void Ball::OnCollisionExit(Collider* other)
	{
	}

	void Ball::Reset(Vector2 pos)
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(pos);
		this->SetState(eState::Active);
		shoot = true;
	}
}