#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class Rigidbody;
	class Orb : public GameObject
	{
	public:
		Orb();
		~Orb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;

		Vector2 mForce;
		bool bShoot;
	};
}

