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

		Transform* tr = GetOwner()->GetComponent<Transform>();

		Vector2 pos = tr->GetPos();
		pos += mVelocity * Time::DeltaTime();
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