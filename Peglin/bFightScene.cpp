#include "bFightScene.h"
#include "bResources.h"

namespace b
{
	FightScene::FightScene()
	{
	}

	FightScene::~FightScene()
	{
	}

	void FightScene::Initialize()
	{
		forest1_bg = Resources::Load<Image>(L"forest1_bg", L"..\\Resources\\sprite.bmp\\background\\forest_1_background.bmp");
		forest1_tile = Resources::Load<Image>(L"forest1_tile", L"..\\Resources\\sprite.bmp\\background\\forest_1_tile.bmp");
	}

	void FightScene::Update()
	{
	}

	void FightScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		StretchBlt(hdc, -1, -1
			, forest1_bg->GetWidth() * 2.5
			, forest1_bg->GetHeight() * 2.5
			, forest1_bg->GetHdc(), 0, 0
			, forest1_bg->GetWidth(), forest1_bg->GetHeight(), SRCCOPY);

		StretchBlt(hdc, -1, 300 - forest1_tile->GetHeight(), forest1_tile->GetWidth(), forest1_tile->GetHeight(), forest1_tile->GetHdc(), 0, 0, forest1_tile->GetWidth(), forest1_tile->GetHeight(), SRCCOPY);
	}

	void FightScene::Release()
	{
		Scene::Release();
	}

	void FightScene::OnEnter()
	{
	}

	void FightScene::OnExit()
	{
	}
}