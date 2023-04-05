#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class Bomb : public GameObject
	{
	public:
		Bomb();
		~Bomb();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Image* mImage;
		class RigidBody* mRigidbody;
	};
}

