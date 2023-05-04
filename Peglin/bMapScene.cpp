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
#include "bSound.h"

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

		MapIcon* stage1 = object::Instantiate<MapIcon>(eLayerType::BG);
		stage1->SetLockPos(Vector2(800, 600));
		stage1->SetIconType(eIconType::Skull);
		MapIcon* bossStage = object::Instantiate<MapIcon>(eLayerType::BG);
		bossStage->SetLockPos(Vector2(750, 800));
		bossStage->SetIconType(eIconType::Mole);
	}

	void MapScene::Update()
	{
		Scene::Update();
	}

	void MapScene::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(48, 130, 48));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		DeleteObject(oldBrush);

		Scene::Render(hdc);
	}

	void MapScene::Release()
	{
		Scene::Release();
	}

	void MapScene::OnEnter()
	{
		Camera::StartFadeIn();
		Camera::SetTarget(mMapPeglin);

		Sound* forestmap = Resources::Load<Sound>(L"forestmap", L"..\\Resources\\audio\\forestmap.wav");
		forestmap->Play(true);
	}

	void MapScene::OnExit()
	{
		Camera::Clear();
		Camera::SetTarget(nullptr);
		Sound* forestmap = Resources::Load<Sound>(L"forestmap", L"..\\Resources\\audio\\forestmap.wav");
		forestmap->Stop(true);
	}
}