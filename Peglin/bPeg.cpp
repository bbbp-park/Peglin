#include "bPeg.h"
#include "bResources.h"
#include "bTransform.h"
#include "bImage.h"
#include "bRigidbody.h"
#include "bCollider.h"
#include "bOrb.h"
#include "bAnimator.h"
#include "bObject.h"
#include "bExplosion.h"

namespace b
{
	Peg::Peg()
		:mImages({})
		, mType(ePegType::Normal)
		, collider(nullptr)
		, mAnimator(nullptr)
		, durability(0)
	{
	}

	Peg::~Peg()
	{
	}

	void Peg::Initialize()
	{
		GameObject::Initialize();

		mImages.resize((UINT)ePegType::End);

		mImages[(UINT)ePegType::Normal] = Resources::Load<Image>(L"NormalPeg", L"..\\Resources\\sprite\\Peg\\Normal Peg.bmp");
		mImages[(UINT)ePegType::Bomb] = Resources::Load<Image>(L"BombPeg1", L"..\\Resources\\sprite\\Peg\\Bomb Peg1.bmp");
		mImages[(UINT)ePegType::Crit] = Resources::Load<Image>(L"CritPeg", L"..\\Resources\\sprite\\Peg\\Crit Peg.bmp");
		mImages[(UINT)ePegType::Red] = Resources::Load<Image>(L"RedPeg", L"..\\Resources\\sprite\\Peg\\Red Peg.bmp");
		mImages[(UINT)ePegType::Refresh] = Resources::Load<Image>(L"RefreshPeg", L"..\\Resources\\sprite\\Peg\\Refresh Peg.bmp");
		mImages[(UINT)ePegType::SmallRect] = Resources::Load<Image>(L"SmallRectPeg", L"..\\Resources\\sprite\\Peg\\small_rect_peg.bmp");
		mImages[(UINT)ePegType::Null] = Resources::Load<Image>(L"NullPeg", L"..\\Resources\\sprite\\Peg\\Null Peg.bmp");

		//mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Ball\\Bomb\\Hit bomb", Vector2::Zero, 0.1f);

		collider = AddComponent<Collider>();
		collider->SetShape(eColliderType::Ellipse);
		collider->SetCenter(Vector2(0.0f, 0.0f));
		collider->SetSize(Vector2(mImages[(UINT)mType]->GetWidth() * 3, mImages[(UINT)mType]->GetHeight() * 3));
		collider->SetPoint(true);
	}

	void Peg::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (this->GetType() == ePegType::Bomb)
		{
			collider->SetCenter(Vector2(0.0f, 6.0f));
		}

		if (durability == 1)
		{
			mImages[(UINT)ePegType::Bomb] = Resources::Load<Image>(L"BombPeg0", L"..\\Resources\\sprite\\Peg\\Bomb Peg0.bmp");
		}
	}

	void Peg::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y
			, mImages[(UINT)mType]->GetWidth() * 3
			, mImages[(UINT)mType]->GetHeight() * 3
			, mImages[(UINT)mType]->GetHdc()
			, 0, 0
			, mImages[(UINT)mType]->GetWidth()
			, mImages[(UINT)mType]->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Peg::Release()
	{
		GameObject::Release();
	}

	void Peg::OnCollisionEnter(Collider* other)
	{
		Orb* orb = dynamic_cast<Orb*>(other->GetOwner());

		if (orb == nullptr)
			return;

		Rigidbody* rb = orb->GetComponent<Rigidbody>();

		Collider* orbCol = orb->GetComponent<Collider>();
		Vector2 orbPos = orbCol->GetCenterPos();

		Collider* bCol = this->GetComponent<Collider>();
		Vector2 bPos = bCol->GetCenterPos();

		if (orb->GetIsShoot())
		{
			if (this->GetType() != ePegType::SmallRect 
				&& this->GetType() != ePegType::Null)
			{
				Vector2 dir = orbPos;
				dir -= bPos;
				dir.Normalize();

				Vector2 vel = rb->GetVelocity();

				if (this->GetType() == ePegType::Bomb)
					durability++;
				
				if (this->GetType() == ePegType::Bomb)
				{
					// ÆøÅº Æä±× Æø¹ß
					if (durability >= 2)
					{
						deleteBomb();
						rb->SetPower(DEFAULT_POWER + 300.0f);
					}
				}
				else if (this->GetType() != ePegType::SmallRect)
				{
					deletePeg();
				}

				Vector2 rVec = math::Reflect(vel, dir);
				rVec *= rb->GetPower();
				rb->SetVelocity(rVec);
			}
		}
	}

	void Peg::OnCollisionStay(Collider* other)
	{
	}

	void Peg::OnCollisionExit(Collider* other)
	{
	}

	void Peg::deletePeg()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		if (this->GetType() == ePegType::Red)
		{
			// »¡°£ »öÀ¸·Î Ç¥Çö Ä¿Á³´Ù°¡ »ç¶óÁü
			this->SetType(ePegType::SmallRect);
		}
		else
		{
			// ³ª¸ÓÁö
			if (this->GetType() != ePegType::Null)
				this->SetType(ePegType::SmallRect);
		}
	}

	void Peg::deleteBomb()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = collider->GetCenterPos();
		pos.x += 60.0f;
		pos.y += 155.0f;
		object::Instantiate<Explosion>(pos, Vector2(0.4f, 0.4f), eLayerType::Effect);

		Orb::AddBombCnt();
		this->SetType(ePegType::Null);
	}
}