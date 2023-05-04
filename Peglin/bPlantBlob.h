#pragma once
#include "bGameObject.h"


namespace b
{
	class PlantBlob : public GameObject
	{
	public:
		PlantBlob();
		~PlantBlob();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		static void SetPower(int p) { power = p; }
		static int GetPower() { return power; }


	private:
		class Animator* mAnimator;
		static int power;
	};
}

