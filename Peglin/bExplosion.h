#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class Explosion : public GameObject
	{
	public:
		Explosion();
		~Explosion();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		static bool GetEnd() { return mEnd; }

	private:
		void explosionCompleteEvent();

	private:
		Animator* mAnimator;
		static bool mEnd;
	};
}

