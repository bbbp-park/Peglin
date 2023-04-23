#pragma once
#include "bGameObject.h"
#include "bImage.h"

namespace b
{
	class Peglin : public GameObject
	{
	public:
		enum class ePeglinState
		{
			ShootBall,
			ShootBomb,
			Death,
			Idle,
		};

		Peglin();
		~Peglin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		static void CalHp(int damage);
		static void SetState(ePeglinState state) { mState = state; }

	private:
		void shoot_ball();
		void shoot_bomb();
		void death();
		void idle();

		void deathCompleteEvent();
		void shoot_ballCompleteEvent();
		void shoot_bombCompleteEvent();

	private:
		class Animator* mAnimator;
		static ePeglinState mState;
		static int hp;

		class Ground* mGround;

		class Orb* mOrb;
		std::vector<class Bomb*> mBombs;
	};
}

