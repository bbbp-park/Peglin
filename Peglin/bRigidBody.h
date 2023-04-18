#pragma once
#include "bComponent.h"

namespace b
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetMass(float mass) { mMass = mass; }
		void AddForce(Vector2 force);
		void SetGround(bool ground) { mbGround = ground; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetForce(Vector2 force) { mForce = force; }
		void SetGravity(Vector2 gravity) { mGravity = gravity; }
		void SetPower(float power) { mPower = power; }

		Vector2 GetVelocity() { return mVelocity; }
		Vector2 GetForce() { return mForce; }
		float GetPower() { return mPower; }

	private:
		float mMass;
		Vector2 mForce;
		Vector2 mAccelation;
		Vector2 mVelocity;
		Vector2 mLimitedVelocity;

		Vector2 mGravity;
		float mPower;
		float mFriction;
		bool mbGround;
	};
}

