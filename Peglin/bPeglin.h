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

		static void SetState(ePeglinState state) { mState = state; }

		static void CalHp(int damage) { hp -= damage; }

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

		class HPbar* hpBar;
		static int hp;
		int maxHp;

		class Ground* mGround;

		class Orb* mOrb;
		std::vector<class Bomb*> mBombs;

		bool delay;
	};
}

