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

		static bool GetIsShoot() { return bShoot; }
		static void AddBombCnt() { bombCnt++; }
		static int GetBombCnt() { return bombCnt; }

	private:
		Animator* mAnimator;
		Rigidbody* mRigidbody;
		Collider* mCollider;

		static bool bShoot;
		static int bombCnt;
		int hitCnt;
		int damage;
		int critDamage;
		int totalDamage;
		
		float mPower;
		class Text* mText;
	};
}

