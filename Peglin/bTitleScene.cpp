#include "bTitleScene.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"
#include "bLogo.h"
#include "bAnimation.h"
#include "bObject.h"
#include "bCamera.h"

namespace b
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
		//Transform* tr = GetComponent<Transform>();
		//tr->SetPos(Vector2(400.0f, 340.0f));
		//tr->SetScale(Vector2(7.0f, 7.0f));

		object::Instantiate<Logo>(Vector2(100.0f, 200.0f), Vector2(7.0f, 7.0f), eLayerType::BG);
		
		titleBackground = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");
	}

	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Map);
		}

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		StretchBlt(hdc, -1, -1, 1902, 1082, titleBackground->GetHdc(), 0, 0, titleBackground->GetWidth(), titleBackground->GetHeight(), SRCCOPY);

		Scene::Render(hdc);
	}

	void TitleScene::Release()
	{
		Scene::Release();
	}

	void TitleScene::OnEnter()
	{
	}

	void TitleScene::OnExit()
	{
		Camera::StartFadeIn();
	}
}