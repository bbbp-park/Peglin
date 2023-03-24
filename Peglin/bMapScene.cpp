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

		object::Instantiate<MapPeglin>(Vector2(800.0f, 240.0f), Vector2(2.2f, 2.2f), eLayerType::Player);
		/*mMapPeglin = new MapPeglin();
		AddGameObject(mMapPeglin, eLayerType::Player);*/

		treeTop = Resources::Load<Image>(L"treeTop", L"..\\Resources\\sprite\\Background\\treetop_.bmp");
		
		object::Instantiate<SpeedUp>(eLayerType::UI);
		/*mSpeedUp = new SpeedUp();
		AddGameObject(mSpeedUp, eLayerType::UI);*/

		//Camera::SetTarget(mMapPeglin);

	}

	void MapScene::Update()
	{
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

		
		TransparentBlt(hdc, -990, -600
			, treeTop->GetWidth() * 2.4
			, treeTop->GetHeight() * 2.4
			, treeTop->GetHdc(), 0, 0
			, treeTop->GetWidth()
			, treeTop->GetHeight()
			, RGB(255, 0, 255));
		
		Scene::Render(hdc);
		DeleteObject(oldBrush);
	}

	void MapScene::Release()
	{
		Scene::Release();
	}

	void MapScene::OnEnter()
	{

	}

	void MapScene::OnExit()
	{
	}
}