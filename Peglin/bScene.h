#pragma once
#include "bEntity.h"
#include "bLayer.h"

namespace b
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Destroy();
		virtual void Release();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(GameObject* obj, eLayerType layer);
		std::vector<GameObject*>& GetGameObjects(eLayerType layer);

	private:
		std::vector<Layer> mLayers;
	};
}

