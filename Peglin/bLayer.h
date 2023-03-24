#pragma once
#include "bEntity.h"
#include "bGameObject.h"

namespace b
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddaGameObject(GameObject* gameObj);
		std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
