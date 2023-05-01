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
#include "mMapIcon.h"

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

		MapIcon* mIcon = object::Instantiate<MapIcon>(eLayerType::BG);
		mIcon->SetLockPos(Vector2(800, 600));
	}

	void MapScene::Update()
	{
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