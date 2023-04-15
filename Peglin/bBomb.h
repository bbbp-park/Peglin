#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class Animator;
	class Rigidbody;
	class Bomb : public GameObject
	{
	public:
		Bomb();
		~Bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	public:
		void explosionCompleteEvent();

	private:
		Image* mImage;
		Animator* mAnimator;
		Rigidbody* mRigidbody;
	};
}

