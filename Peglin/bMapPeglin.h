#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class MapPeglin : public GameObject
	{
	public:
		enum class eMapPeglinState
		{
			Move,
			Idle,
			Pass,
		};

		MapPeglin();
		~MapPeglin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		void move();
		void idle();
		void pass();

	private:
		Animator* mAnimator;
		eMapPeglinState mState;

		class Rigidbody* mRigidbody;
		Vector2 target;
		Vector2 dir;
		float mTime;
	};

}
