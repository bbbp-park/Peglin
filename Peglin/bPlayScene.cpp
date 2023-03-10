#include "bPlayScene.h"
#include "bPeglin.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"

namespace b
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		mPeglin = new Peglin();
		AddGameObject(mPeglin, eLayerType::Player);
		

		treeTop = Resources::Load<Image>(L"treeTop", L"..\\Resources\\sprite\\Background\\treetop_.bmp");

		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		if (Input::GetKeyState(eKeyCode::M) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Fight);
		}

		Scene::Update();
	}

	void PlayScene::Render(HDC hdc)
	{
		//HBRUSH brush = CreateSolidBrush(RGB(48, 130, 48));
		//HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		TransparentBlt(hdc, 0, 0, 1600, 700, treeTop->GetHdc(), 0, 0, treeTop->GetWidth(), treeTop->GetHeight(), RGB(255, 0, 255));
		
		Scene::Render(hdc);
		
		//DeleteObject(oldBrush);
	}

	void PlayScene::Release()
	{
		Scene::Release();
	}

	void PlayScene::OnEnter()
	{

	}

	void PlayScene::OnExit()
	{
	}
}