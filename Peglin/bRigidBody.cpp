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
			// �� ���� ���� ��
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::DeltaTime();
		}

		// �߷°��ӵ� �ִ� �ӵ� ����
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

		//// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// �ӵ� �ݴ� �������� ������ ����
		//	Vector2 friction = -mVelocity;
		//	friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

		//	// ���������� ���� �ӵ� ���Ұ� ���� �ӵ����� ū ���
		//	if (mVelocity.Length() < friction.Length())
		//	{
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		mVelocity += friction;
		//	}
		//}

		// �ӵ��� �°Բ� ��ü�� �̵�
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