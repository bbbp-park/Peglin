#include "bFightScene.h"
#include "bResources.h"
#include "bInput.h"
#include "bSceneManager.h"
#include "bPeglin.h"
#include "bMonster.h"
#include "bHPbar.h"
#include "bCollisionManager.h"
#include "bObject.h"
#include "bCamera.h"
#include "bSpeedUp.h"
#include "bBag.h"
#include "bGround.h"

namespace b
{
	FightScene::FightScene()
		: mPeglin(nullptr)
		, mHPbar(nullptr)
		, forest1_bg(nullptr)
		, forest1_tile(nullptr)
		, tileSet0(nullptr)
		, tileSet1(nullptr)
		, tileSet2(nullptr)
		, plunger(nullptr)
		, backScreen(nullptr)
	{
	}

	FightScene::~FightScene()
	{
	}

	void FightScene::Initialize()
	{

		Scene::Initialize();

		//mPeglin = new Peglin();
		//AddGameObject(mPeglin, eLayerType::Player);

		//mGround = object::Instantiate<Ground>(Vector2(0.0f, 220.0f), eLayerType::Ground);

		object::Instantiate<Peglin>(Vector2(410.0f, 170.0f), Vector2(3.0f, 3.0f), eLayerType::Player);

		object::Instantiate<Monster>(Vector2(1000.0f, 200.0f), Vector2(3.0f, 3.0f), eLayerType::Monster);

		object::Instantiate<HPbar>(eLayerType::UI);
		object::Instantiate<Bag>(Vector2(140.0f, 0.0f), Vector2(2.4f, 2.4f), eLayerType::UI);
		object::Instantiate<SpeedUp>(eLayerType::UI);

		forest1_bg = Resources::Load<Image>(L"forest1_bg", L"..\\Resources\\sprite\\Background\\forest_1_background.bmp");
		forest1_tile = Resources::Load<Image>(L"forest1_tile", L"..\\Resources\\sprite\\Background\\forest_1_tile.bmp");

		tileSet0 = Resources::Load<Image>(L"tileSet0", L"..\\Resources\\sprite\\Background\\Tile\\tileset_24.bmp");
		plunger = Resources::Load<Image>(L"plunger", L"..\\Resources\\sprite\\Background\\Tile\\plunger.bmp");
		backScreen = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");
	}

	void FightScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::O) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Map);
		}

		if (Input::GetKeyState(eKeyCode::P) == eKeyState::Down)
		{
			SceneManager::LoadScene(eSceneType::Ending);
		}

		Scene::Update();
	}

	void FightScene::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(35, 31, 20));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

		StretchBlt(hdc, -178, -90
			, forest1_bg->GetWidth() * 3
			, forest1_bg->GetHeight() * 3
			, forest1_bg->GetHdc(), 0, 0
			, forest1_bg->GetWidth(), forest1_bg->GetHeight(), SRCCOPY);

		int pX = 0;
		int pY = 0;

		int bX = 373 + tileSet0->GetWidth() * 3 * 3;
		int bY = 220 + (forest1_tile->GetHeight() * 3);

		StretchBlt(hdc, bX, bY
			, 1273 - bX
			, backScreen->GetHeight() * 3
			, backScreen->GetHdc(), 0, 0
			, backScreen->GetWidth(), backScreen->GetHeight(), SRCCOPY);

		for (size_t i = 0; i < 35; i++)
		{
			int x = forest1_tile->GetWidth() * 3 * i;
			StretchBlt(hdc, x, 220
				, forest1_tile->GetWidth() * 3
				, forest1_tile->GetHeight() * 3
				, forest1_tile->GetHdc(), 0, 0
				, forest1_tile->GetWidth(), forest1_tile->GetHeight(), SRCCOPY);
		}

		for (size_t i = 0; i < 2; i++)
		{
			int x = 370 + tileSet0->GetWidth() * 3;
			int y = 220 + (forest1_tile->GetHeight() * 3);
			y += tileSet0->GetHeight() * 3 * i;

			pX = x;
			pY = y + tileSet0->GetHeight() * 3;

			TransparentBlt(hdc, x, y
				, tileSet0->GetWidth() * 3 + 8
				, tileSet0->GetHeight() * 3
				, tileSet0->GetHdc(), 0, 0
				, tileSet0->GetWidth()
				, tileSet0->GetHeight()
				, RGB(255, 0, 255));
		}

		for (size_t i = 0; i < 14; i++)
		{
			int x1 = 373; 
			int x2 = x1 + tileSet0->GetWidth() * 3 * 2;
			int x3 = 1273;
			int y = 220 + (forest1_tile->GetHeight() * 3);
			y += tileSet0->GetHeight() * 3 * i;

			TransparentBlt(hdc, x1, y
				, tileSet0->GetWidth() * 3
				, tileSet0->GetHeight() * 3
				, tileSet0->GetHdc(), 0, 0
				, tileSet0->GetWidth()
				, tileSet0->GetHeight()
				, RGB(255, 0, 255));

			TransparentBlt(hdc, x2, y
				, tileSet0->GetWidth() * 3
				, tileSet0->GetHeight() * 3
				, tileSet0->GetHdc(), 0, 0
				, tileSet0->GetWidth()
				, tileSet0->GetHeight()
				, RGB(255, 0, 255));

			TransparentBlt(hdc, x3, y
				, tileSet0->GetWidth() * 3
				, tileSet0->GetHeight() * 3
				, tileSet0->GetHdc(), 0, 0
				, tileSet0->GetWidth()
				, tileSet0->GetHeight()
				, RGB(255, 0, 255));
		}

		StretchBlt(hdc, pX, pY
			, plunger->GetWidth() * 3
			, plunger->GetHeight() * 3
			, plunger->GetHdc(), 0, 0
			, plunger->GetWidth(), plunger->GetHeight(), SRCCOPY);


		Scene::Render(hdc);

		DeleteObject(oldBrush);
	}

	void FightScene::Release()
	{
		Scene::Release();
	}

	void FightScene::OnEnter()
	{
		Camera::StartFadeIn();
		
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Ball, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Ground, true);
	}

	void FightScene::OnExit()
	{
	}
}