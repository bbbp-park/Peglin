#pragma once
#include "bGameObject.h"
#include "bImage.h"

namespace b
{
	class Animator;
	class Peglin : public GameObject
	{
	public:
		Peglin();
		~Peglin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Animator* mAnimator;
	};
}

