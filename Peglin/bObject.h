#pragma once
#include "bGameObject.h"
#include "bScene.h"
#include "bSceneManager.h"
#include "bTransform.h"

namespace b::object
{
	template <typename T>
	static inline T* Instantiate(eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		return gameObj;
	}

	template <typename T>
	static inline T* Instantiate(Vector2 pos, Vector2 scale, eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(gameObj, type);
		gameObj->Initialize();
		gameObj->GameObject::GetComponent<Transform>()->SetPos(pos);
		gameObj->GameObject::GetComponent<Transform>()->SetScale(scale);
		return gameObj;
	}

	static void Destory(GameObject* obj)
	{
		obj->SetState(GameObject::eState::Death);
	}
}