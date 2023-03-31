#include "bSceneManager.h"
#include "bMapScene.h"
#include "bTitleScene.h"
#include "bFightScene.h"
#include "bEndingScene.h"
#include "bToolScene.h"
#include "bCollisionManager.h"
#include "bCamera.h"

namespace b
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initailize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Map] = new MapScene();
		mScenes[(UINT)eSceneType::Fight] = new FightScene();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();
		mScenes[(UINT)eSceneType::Tool] = new ToolScene();

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}

		mActiveScene = mScenes[(UINT)eSceneType::Tool];
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(48, 130, 48));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		mActiveScene->Render(hdc);

		DeleteObject(oldBrush);
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}

	void SceneManager::Release()
	{
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::LoadScene(eSceneType type)
	{
		Camera::Clear();

		// ÇöÀç ¾À
		mActiveScene->OnExit();

		CollisionManager::Clear();
		// ´ÙÀ½ ¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}
}