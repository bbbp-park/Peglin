#include "bRigidbody.h"
#include "bTime.h"
#include "bGameObject.h"
#include "bTransform.h"

namespace b
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 400.0f;
		mLimitedVelocity.y = 400.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 400.0f);
		mFriction = 100.0f;
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		// F = M * A
		mAccelation = mForce / mMass;

		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround)
		{
			// 땅 위에 있을 때
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 중력가속도 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		//Vector2 sideVelocity = mVelocity - gravity;

		//if (mLimitedVelocity.y < gravity.Length())
		//{
		//	gravity.Normalize();
		//	gravity *= mLimitedVelocity.y;
		//}

		//if (mLimitedVelocity.x < gravity.Length())
		//{
		//	sideVelocity.Normalize();
		//	sideVelocity *= mLimitedVelocity.x;
		//}

		//// 마찰력 조건 ( 적용된 힘이 없고, 속도가 0이 아님)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// 속도 반대 방향으로 마찰력 적용
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

		//	// 마찰력으로 인한 속도 감소가 현재 속도보다 큰 경우
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		// 속도에 맞게끔 물체를 이동
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector2 pos = tr->GetPos();
		pos += mVelocity * Time::DeltaTime();

		if (pos.y > 900.0f)
			mbGround = true;

		tr->SetPos(pos);
		mForce.Clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
	}

	void Rigidbody::Release()
	{
	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}