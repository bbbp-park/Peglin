#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class Logo : public GameObject
	{
	public:
		Logo();
		~Logo();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}

