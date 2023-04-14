#pragma once
#include "bGameObject.h"

namespace b
{
	class Ground : public GameObject
	{
	public:
		Ground();
		virtual ~Ground();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetGameObject(class GameObject* gameObj) { mGameObject = gameObj; }

	private:
		class Collider* mCollider;
		class GameObject* mGameObject;
	};
}

