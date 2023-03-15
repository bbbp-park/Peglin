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

	private:
		Animator* mAnimator;
		eMapPeglinState mState;
	};

}
