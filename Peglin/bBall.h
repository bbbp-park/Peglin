#pragma once
#include "bGameObject.h"

namespace b
{
	class Ball : public GameObject
	{
	public:
		Ball();
		~Ball();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		static void SetPower(int p) { power = p; }
		static int GetPower() { return power; }

		void Reset(Vector2 pos);

	private:
		class Image* mImage;
		class Rigidbody* mRigidbody;

		static int power;
		bool shoot;
	};

}
