#include "bOrb.h"
#include "bAnimator.h"
#include "bTransform.h"
#include "bInput.h"
#include "bRigidbody.h"
#include "bObject.h"
#include "bCollider.h"
#include "bWall.h"
#include "bPeg.h"
#include "bBall.h"
#include "bPeglin.h"
#include "bText.h"
#include "bSceneManager.h"
#include "bFightScene.h"


namespace b
{
	int Orb::bombCnt = 0;
	bool Orb::bShoot = false;

	Orb::Orb()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mPower(DEFAULT_POWER)
		, mInfo()
		, mText(nullptr)
	{
		bombCnt = 0;

		mInfo.damage = 2;
		mInfo.critDamage = 4;
		mInfo.hitCnt = 0;
		mInfo.totalDamage = 0;
		mInfo.isCrit = false;
		mInfo.isRefresh = false;
	}

	Orb::~Orb()
	{
	}

	void Orb::Initialize()
	{
		GameObject::Initialize();
		this->SetName(L"Orb");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Ball\\Rock", Vector2::Zero, 0.1f);

		mAnimator->Play(L"BallRock", true);

		mCollider = AddComponent<Collider>();
		mCollider->SetShape(eColliderShape::Ellipse);
		mCollider->SetSize(Vector2(20.0f, 20.0f));
		mCollider->SetCenter(Vector2(-2.0f, -10.0f));

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2::Zero);
		mRigidbody->SetGround(false);
	}

	void Orb::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		// 오브가 떨어졌을 때
		if (pos.y >= 910.0f)
		{
			object::Destory(this);
			bShoot = false;
			Ball::SetPower(mInfo.totalDamage);
			Peglin::SetState(Peglin::ePeglinState::ShootBomb);
		}

		if (!bShoot && Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			bShoot = true;
			
			Vector2 dir = Input::GetMousePos();
			dir -= pos;
			dir.Normalize();
			mRigidbody->SetPower(mPower);
			dir *= mRigidbody->GetPower();
			mRigidbody->SetVelocity(dir);
			mRigidbody->SetGravity(Vector2(0.0f, 400.0f));

		}

		/*totalDamage = damage * hitCnt;*/

		GameObject::Update();
	}

	void Orb::Render(HDC hdc)
	{
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);

		if (!bShoot)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 mPos = tr->GetPos();
			Vector2 mousePos = Input::GetMousePos();

			MoveToEx(hdc, mPos.x + 10, mPos.y, NULL);
			LineTo(hdc, mousePos.x, mousePos.y);
		}

		(HPEN)SelectObject(hdc, oldPen);
		DeleteObject(pen);

		GameObject::Render(hdc);
	}

	void Orb::Release()
	{
		GameObject::Release();
	}

	void Orb::OnCollisionEnter(Collider* other)
	{
		if (bShoot)
		{
			eColliderType type = other->GetColliderType();

			if (type != eColliderType::null)
			{
				float power = mRigidbody->GetPower() * 0.9f;
				mRigidbody->SetPower(power);

				if (type == eColliderType::peg)
				{
					Peg* peg = dynamic_cast<Peg*>(other->GetOwner());

					if (peg->GetType() == ePegType::Normal
						|| peg->GetType() == ePegType::Red)
					{
						mInfo.hitCnt++;
						//mInfo.totalDamage = mInfo.damage * mInfo.hitCnt;
					}
					else if (peg->GetType() == ePegType::Crit)
					{
						// 치명타 페그 터질 때
						mInfo.isCrit = true;

						Scene* activeScene = SceneManager::GetActiveScene();
						if (activeScene->GetName() == L"FightScene")
						{
							FightScene::SetRedPegs();
						}
						
					}
					else if (peg->GetType() == ePegType::Refresh)
					{
						// 새로고침
						Scene* activeScene = SceneManager::GetActiveScene();
						if (activeScene->GetName() == L"FightScene")
						{
							FightScene::Refresh();
						}
					}

					if (mInfo.isCrit)
						mInfo.totalDamage = mInfo.critDamage * mInfo.hitCnt;
					else
						mInfo.totalDamage = mInfo.damage * mInfo.hitCnt;

					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPos();
					mText = object::Instantiate<Text>(eLayerType::UI);
					wchar_t str[10] = L"";
					int num = swprintf_s(str, 10, L"%d", mInfo.totalDamage);
					mText->SetText(*str);
					mText->SetIsChange(false);
					mText->SetTextHeight(30);
					mText->SetDelete(true);
					mText->SetActive(true);
					Transform* textTr = mText->GetComponent<Transform>();
					pos.x += 10;
					pos.y -= 10;
					textTr->SetPos(pos);
				}
			}
		}
	}

	void Orb::OnCollisionStay(Collider* other)
	{
	}

	void Orb::OnCollisionExit(Collider* other)
	{
	}
}