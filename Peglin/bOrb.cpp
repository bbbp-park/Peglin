#include "bOrb.h"
#include "bAnimator.h"
#include "bTransform.h"
#include "bInput.h"
#include "bRigidbody.h"
#include "bObject.h"
#include "bCollider.h"
#include "bWall.h"
#include "bPeg.h"

namespace b
{
	Orb::Orb()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, bShoot(false)
		, mForce(Vector2(Vector2::One))
		, mPower(DEFAULT_POWER)
		, hitCnt(0)
		, damage(2)
		, critDamage(4)
		, totalDamage(0)
	{
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
		mCollider->SetShape(eColliderType::Ellipse);
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
			object::Destory(this);

		if (!bShoot && Input::GetKeyDown(eKeyCode::LBUTTON))
		{
			bShoot = true;
			
			Vector2 dir = Input::GetMousePos();
			dir -= pos;
			dir.Normalize();
			//mForce = dir;
			mRigidbody->SetPower(mPower);
			dir *= mRigidbody->GetPower();
			mRigidbody->SetVelocity(dir);
			//mRigidbody->SetForce(mForce);
			mRigidbody->SetGravity(Vector2(0.0f, 400.0f));
		}

		if (Input::GetKey(eKeyCode::RBUTTON))
		{
			Vector2 mouse = Input::GetMousePos();
			int a = 0;
		}

		totalDamage = damage * hitCnt;

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

		wchar_t tDamage[50] = {};
		swprintf_s(tDamage, 50, L"damage : %d", totalDamage);
		TextOut(hdc, 800, 40, tDamage, wcsnlen_s(tDamage, 50));

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
			float power = mRigidbody->GetPower() * 0.9f;
			mRigidbody->SetPower(power);
			
			if (other->GetPoint())
			{
				Peg* peg = dynamic_cast<Peg*>(other->GetOwner());

				if (peg->GetType() == ePegType::Normal
					|| peg->GetType() == ePegType::Crit
					|| peg->GetType() == ePegType::Refresh)
				{
					hitCnt++;
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