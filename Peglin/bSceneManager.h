#pragma once
#include "bScene.h"

namespace b
{
	class SceneManager
	{
	public:
		static void Initailize();
		static void Update();
		static void Render(HDC hdc);
		static void Release();

		static void LoadScene(eSceneType type);

	private:
		static std::vector<Scene*> mScenes;
		static Scene* mActiveScene;
	};
}

