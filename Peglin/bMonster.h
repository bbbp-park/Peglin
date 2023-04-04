#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class Monster : public GameObject
	{
	public:
		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Animator* mAnimator;
	};
}

