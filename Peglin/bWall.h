#pragma once
#include "bGameObject.h"

namespace b
{
	class Wall : public GameObject
	{
	public:
		Wall();
		~Wall();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetOrb(class Orb* orb) { mOrb = orb; }

	private:
		class Collider* mCollider;
		class GameObject* mGameObject;
		class Orb* mOrb;
	};
}

