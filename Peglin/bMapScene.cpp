#include "bMapScene.h"
#include "bMapPeglin.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bResources.h"
#include "bSpeedUp.h"
#include "bAnimation.h"
#include "bTime.h"
#include "bCamera.h"
#include "bTransform.h"
#include "bObject.h"
#include "bTrees.h"

namespace b
{
	MapScene::MapScene()
		: mMapPeglin(nullptr)
		, treeTop(nullptr)
		, mSpeedUp(nullptr)
	{
	}

	MapScene::~MapScene()
	{
	}

	void MapScene::Initialize()
	{
		Scene::Initialize();

		mMapPeglin = object::Instantiate<MapPeglin>(Vector2(800.0f, 450.0f), Vector2(2.2f, 2.2f), eLayerType::Player);

		object::Instantiate<Trees>(eLayerType::BG);
		//object::Instantiate<SpeedUp>(eLayerType::UI);

		
	}

	void MapScene::Update()
	{
		//Camera::SetTarget(mMapPeglin);

		Transform* tr = mMapPeglin->GetComponent<Transform>();

		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Title);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Fight);
		}

		Scene::Update();
	}

	void MapScene::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(48, 130, 48));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		
		Scene::Render(hdc);
		DeleteObject(oldBrush);
	}

	void MapScene::Release()
	{
		Scene::Release();
	}

	void MapScene::OnEnter()
	{
		Camera::StartFadeIn();
		Camera::SetTarget(mMapPeglin);
	}

	void MapScene::OnExit()
	{
		Camera::Clear();
		Camera::SetTarget(nullptr);
	}
}