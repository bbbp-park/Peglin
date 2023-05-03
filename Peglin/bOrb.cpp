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

namespace b
{
	int Orb::bombCnt = 0;
	bool Orb::bShoot = false;

	Orb::Orb()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mPower(DEFAULT_POWER)
		, hitCnt(0)
		, damage(2)
		, critDamage(4)
		, totalDamage(0)
		, mText(nullptr)
	{
		bombCnt = 0;
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
			Ball::SetPower(totalDamage);
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
					hitCnt++;
					totalDamage = damage * hitCnt;

					Transform* tr = GetComponent<Transform>();
					Vector2 pos = tr->GetPos();
					mText = object::Instantiate<Text>(eLayerType::UI);
					wchar_t str[10] = L"";
					int num = swprintf_s(str, 10, L"%d", totalDamage);
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