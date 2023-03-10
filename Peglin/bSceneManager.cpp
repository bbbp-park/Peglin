#include "bSceneManager.h"
#include "bPlayScene.h"
#include "bTitleScene.h"
#include "bFightScene.h"
#include "bEndingScene.h"

namespace b
{
	std::vector<Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;

	void SceneManager::Initailize()
	{
		mScenes.resize((UINT)eSceneType::End);

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Fight] = new FightScene();
		mScenes[(UINT)eSceneType::Ending] = new EndingScene();

		mActiveScene = mScenes[(UINT)eSceneType::Title];

		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			scene->Initialize();
		}
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
		// ÇöÀç ¾À
		mActiveScene->OnExit();

		// ´ÙÀ½ ¾À
		mActiveScene = mScenes[(UINT)type];
		mActiveScene->OnEnter();
	}
}