#pragma once
#include "bGameObject.h"
#include "bImage.h"

namespace b
{
	Animator;
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
		ePeglinState mState;

		class Ground* mGround;
		class Wall* leftWall;
		class Wall* rightWall;

		class Orb* mOrb;
	};
}

