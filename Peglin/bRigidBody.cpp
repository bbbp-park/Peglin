#include "bRigidBody.h"
#include "bTime.h"
#include "bGameObject.h"
#include "bTransform.h"

namespace b
{
	RigidBody::RigidBody()
		: Component(eComponentType::Rigidbody)
		, mMass(0.0f)
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
	{
		mLimitedVelocity.x = 200.0f;
		mLimitedVelocity.y = 1000.0f;
		mbGround = false;
		mGravity = Vector2(0.0f, 800.0f);
		mFriction = 100.0f;
	}

	RigidBody::~RigidBody()
	{
	}

	void RigidBody::Initialize()
	{
	}

	void RigidBody::Update()
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

		Vector2 sideVelocity = mVelocity - gravity;

		if (mLimitedVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocity.x;
		}

		// ������ ���� ( ����� ���� ����, �ӵ��� 0�� �ƴ�)
		if (!(mVelocity == Vector2::Zero))
		{
			// �ӵ� �ݴ� �������� ������ ����
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���Ұ� ���� �ӵ����� ū ���
			if (mVelocity.Length() < friction.Length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}

		// �ӵ��� �°Բ� ��ü�� �̵�
		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector2 pos = tr->GetPos();
		pos += mVelocity * Time::DeltaTime();

		if (pos.y > 900.0f)
			mbGround = true;

		tr->SetPos(pos);
		mForce.Clear();
	}

	void RigidBody::Render(HDC hdc)
	{
	}

	void RigidBody::Release()
	{
	}

	void RigidBody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}