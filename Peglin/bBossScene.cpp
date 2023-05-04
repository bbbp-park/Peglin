#include "bBossScene.h"
#include "bObject.h"
#include "bWall.h"
#include "bPeglin.h"
#include "bOrb.h"
#include "bPeg.h"
#include "bImage.h"
#include "bResources.h"
#include "bCamera.h"
#include "bSound.h"
#include "bMonster.h"
#include "bCollisionManager.h"
#include "bTime.h"

namespace b
{
	bool BossScene::mTurn = true;
	std::vector<Peg*> BossScene::mPegs = {};
	std::vector<Monster*> BossScene::mMonsters = {};

	BossScene::BossScene()
		: mPeglin(nullptr)
		, forest2_bg(nullptr)
		, forest2_tile(nullptr)
		, tileSet0(nullptr)
		, tileSet1(nullptr)
		, tileSet2(nullptr)
		, plunger(nullptr)
		, backScreen(nullptr)
		, mBouncers({})
		, mBouncerTiles({})
		, mOrb(nullptr)
		, CritIdx({})
		, RefreshIdx({})
		, i(0)
		, cnt(1)
	{
	}

	BossScene::~BossScene()
	{
	}

	void BossScene::Initialize()
	{
		Scene::Initialize();

		mPeglin = object::Instantiate<Peglin>(Vector2(410.0f, 170.0f), Vector2(3.0f, 3.0f), eLayerType::Player);

		mOrb = object::Instantiate<Orb>(Vector2(888.0f, 320.0f), Vector2(2.0f, 2.0f), eLayerType::Orb);

		object::Instantiate<Wall>(Vector2(469.0f, 250.0f), eLayerType::Wall);
		object::Instantiate<Wall>(Vector2(1273.0f, 250.0f), eLayerType::Wall);

		// monster setting
		mMonsters.push_back(object::Instantiate<Monster>(Vector2(1275.0f, 150.0f), Vector2(3.0f, 3.0f), eLayerType::Monster));
		mMonsters[0]->SetMonsterType(eMonsterType::Mole);
		mMonsters.push_back(object::Instantiate<Monster>(Vector2(775.0f, 7.0f), Vector2(3.0f, 3.0f), eLayerType::Monster));
		mMonsters[1]->SetMonsterType(eMonsterType::Tree);

		// peg setting
		mPegs.push_back(object::Instantiate<Peg>(Vector2(836.0f, 276.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(860.0f, 276.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(884.0f, 276.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(908.0f, 276.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(931.0f, 276.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(812.0f, 298.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(954.0f, 298.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(788.0f, 322.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(978.0f, 322.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(693.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(719.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(742.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(766.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(788.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(978.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1002.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1025.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1050.0f, 346.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1073.0f, 346.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 370.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(787.0f, 370.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 370.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 370.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(646.0f, 394.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(787.0f, 394.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 394.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1120.0f, 394.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(646.0f, 416.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(812.0f, 416.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(954.0f, 416.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1120.0f, 416.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(646.0f, 441.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(836.0f, 441.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(860.0f, 441.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(884.0f, 441.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(908.0f, 441.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(931.0f, 441.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1120.0f, 441.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(646.0f, 465.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(836.0f, 465.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(931.0f, 465.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1120.0f, 465.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 487.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(812.0f, 487.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(954.0f, 487.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 487.0f), eLayerType::Peg));
		
		mPegs.push_back(object::Instantiate<Peg>(Vector2(693.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(719.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(742.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(766.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(788.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(978.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1002.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1025.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1050.0f, 511.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1073.0f, 511.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(551.0f, 575.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(693.0f, 575.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1073.0f, 575.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1215.0f, 575.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(527.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(717.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1049.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1239.0f, 598.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 622.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 646.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 670.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 694.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 718.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 742.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 766.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 790.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(574.0f, 814.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 622.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 646.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 670.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 694.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 718.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 742.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 766.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 790.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(669.0f, 814.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 622.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 646.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 670.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 694.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 718.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 742.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 766.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 790.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1095.0f, 814.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 598.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 622.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 646.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 670.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 694.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 718.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 742.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 766.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 790.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1192.0f, 814.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(884.0f, 593.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(860.0f, 618.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(908.0f, 618.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(836.0f, 641.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(931.0f, 641.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(908.0f, 663.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(860.0f, 663.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(884.0f, 687.0f), eLayerType::Peg));
		
		mPegs.push_back(object::Instantiate<Peg>(Vector2(812.0f, 540.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(954.0f, 540.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(800.0f, 572.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(966.0f, 572.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(788.0f, 604.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(978.0f, 604.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(776.0f, 636.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(990.0f, 636.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(764.0f, 668.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1002.0f, 668.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(752.0f, 700.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1014.0f, 700.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(740.0f, 732.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1026.0f, 732.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(728.0f, 764.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1038.0f, 764.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(716.0f, 796.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1050.0f, 796.0f), eLayerType::Peg));

		// bomb 622 1142d
		mPegs.push_back(object::Instantiate<Peg>(Vector2(884.0f, 630.0f), eLayerType::Peg));
		mPegs[130]->SetPegType(ePegType::Bomb);
		mPegs.push_back(object::Instantiate<Peg>(Vector2(622.0f, 771.0f), eLayerType::Peg));
		mPegs[131]->SetPegType(ePegType::Bomb);
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1142.0f, 771.0f), eLayerType::Peg));
		mPegs[132]->SetPegType(ePegType::Bomb);

		// bouncer setting
		Vector2 bDiff = Vector2(15.0f, 55.0f);
		mBouncerTiles.push_back(object::Instantiate<BouncerTile>(Vector2(595.0f + bDiff.x, 805.0f + bDiff.y), eLayerType::Wall));
		mBouncers.push_back(object::Instantiate<Bouncer>(Vector2
		(595.0f, 805.0f), eLayerType::Wall));

		mBouncerTiles.push_back(object::Instantiate<BouncerTile>(Vector2(762.0f + bDiff.x, 805.0f + bDiff.y), eLayerType::Wall));
		mBouncers.push_back(object::Instantiate<Bouncer>(Vector2
		(762.0f, 805.0f), eLayerType::Wall));

		mBouncerTiles.push_back(object::Instantiate<BouncerTile>(Vector2(950.0f + bDiff.x, 805.0f + bDiff.y), eLayerType::Wall));
		mBouncers.push_back(object::Instantiate<Bouncer>(Vector2
		(950.0f, 805.0f), eLayerType::Wall));

		mBouncerTiles.push_back(object::Instantiate<BouncerTile>(Vector2(1117.0f + bDiff.x, 805.0f + bDiff.y), eLayerType::Wall));
		mBouncers.push_back(object::Instantiate<Bouncer>(Vector2
		(1117.0f, 805.0f), eLayerType::Wall));

		forest2_bg = Resources::Load<Image>(L"forest_2_background", L"..\\Resources\\sprite\\Background\\forest_2_background.bmp");
		forest2_tile = Resources::Load<Image>(L"forest_2_tile", L"..\\Resources\\sprite\\Background\\forest_2_tile.bmp");

		tileSet0 = Resources::Load<Image>(L"tileSet0", L"..\\Resources\\sprite\\Background\\Tile\\tileset_24.bmp");
		plunger = Resources::Load<Image>(L"plunger", L"..\\Resources\\sprite\\Background\\Tile\\plunger.bmp");
		backScreen = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");
	}

	void BossScene::Update()
	{
		if (isClear)
		{
			mTime += Time::DeltaTime();
			if (mTime >= 2.0f)
			{
				SceneManager::LoadScene(eSceneType::Ending);
				//return;
			}
		}

		if (mTurn && cnt == 1)
		{
			CreateOrb();
			cnt--;

			SetNormalPegs();

			for (int idx : CritIdx)
			{
				if (mPegs[idx]->GetType() != ePegType::SmallRect)
					mPegs[idx]->SetPegType(ePegType::Normal);
			}
			for (int idx : RefreshIdx)
			{
				if (mPegs[idx]->GetType() != ePegType::SmallRect)
					mPegs[idx]->SetPegType(ePegType::Normal);
			}

			SetCritPegs();
			SetRefreshPegs();

			if (mOrb != nullptr && mOrb->GetIsCrit())
			{
				SetRedPegs();
			}
		}

		if (!mTurn && cnt == 0)
		{
			if (mMonsters[i]->GetEventComplete())
				i++;

			if (i < mMonsters.size())
				mMonsters[i]->StartEvent();

			if (mMonsters[mMonsters.size() - 1]->GetEventComplete())
			{
				cnt++;
				mTurn = true;
				i = 0;

				for (auto mon : mMonsters)
				{
					mon->SetEventComplete(false);
				}
			}
		}

		if (isClear == false)
		{
			for (auto mon : mMonsters)
			{
				if (mon->GetState() != GameObject::eState::Active || mon->GetMonsterState() == eMonsterState::Dead)
					isClear = true;
				else
				{
					isClear = false;
					break;
				}
			}
		}



		Scene::Update();
	}

	void BossScene::Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(35, 31, 20));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
		StretchBlt(hdc, -178, -90
			, forest2_bg->GetWidth() * 3
			, forest2_bg->GetHeight() * 3
			, forest2_bg->GetHdc(), 0, 0
			, forest2_bg->GetWidth(), forest2_bg->GetHeight(), SRCCOPY);

		int pX = 0;
		int pY = 0;

		int bX = 373 + tileSet0->GetWidth() * 3 * 3;
		int bY = 220 + (forest2_tile->GetHeight() * 3);

		StretchBlt(hdc, bX, bY
			, 1273 - bX
			, backScreen->GetHeight() * 3
			, backScreen->GetHdc(), 0, 0
			, backScreen->GetWidth(), backScreen->GetHeight(), SRCCOPY);

		for (size_t i = 0; i < 35; i++)
		{
			int x = forest2_tile->GetWidth() * 3 * i;
			StretchBlt(hdc, x, 220
				, forest2_tile->GetWidth() * 3
				, forest2_tile->GetHeight() * 3
				, forest2_tile->GetHdc(), 0, 0
				, forest2_tile->GetWidth(), forest2_tile->GetHeight(), SRCCOPY);
		}

		for (size_t i = 0; i < 2; i++)
		{
			int x = 370 + tileSet0->GetWidth() * 3;
			int y = 220 + (forest2_tile->GetHeight() * 3);
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
			int y = 220 + (forest2_tile->GetHeight() * 3);
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

		DeleteObject(oldBrush);
		Scene::Render(hdc);
	}

	void BossScene::Release()
	{
		Scene::Release();
	}

	void BossScene::OnEnter()
	{
		Camera::StartFadeIn();

		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Peg, true);

		Sound* world1_fight = Resources::Load<Sound>(L"world1_fight", L"..\\Resources\\audio\\world1_fight.wav");
		world1_fight->Play(true);
	}

	void BossScene::OnExit()
	{
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Monster, false);
		CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Wall, false);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Wall, false);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Peg, false);

		Sound* world1_fight = Resources::Load<Sound>(L"world1_fight", L"..\\Resources\\audio\\world1_fight.wav");
		world1_fight->Stop(true);
	}

	void BossScene::SetRedPegs()
	{
		for (auto peg : mPegs)
		{
			if (peg->GetType() == ePegType::Normal)
			{
				peg->SetPegType(ePegType::Red);
			}
		}
	}

	void BossScene::SetNormalPegs()
	{
		for (auto peg : mPegs)
		{
			if (peg->GetType() == ePegType::Red)
			{
				peg->SetPegType(ePegType::Normal);
			}
		}
	}

	void BossScene::Refresh(bool isCrit)
	{
		for (auto peg : mPegs)
		{
			if (peg->GetType() == ePegType::SmallRect)
			{
				if (isCrit)
					peg->SetPegType(ePegType::Red);
				else
					peg->SetPegType(ePegType::Normal);

				Collider* pCol = peg->GetComponent<Collider>();
				pCol->SetColliderType(eColliderType::peg);
			}
		}
	}

	void BossScene::CreateOrb()
	{
		mOrb->Reset();
	}

	void BossScene::SetCritPegs()
	{
		CritIdx = {};
		CritIdx = math::Random(3, 129);

		for (int idx : CritIdx)
		{
			mPegs[idx]->SetPegType(ePegType::Crit);
			Collider* pCol = mPegs[idx]->GetComponent<Collider>();
			pCol->SetColliderType(eColliderType::peg);
		}
	}

	void BossScene::SetRefreshPegs()
	{
		RefreshIdx = {};
		RefreshIdx = math::Random(3, 129);

		for (int idx : RefreshIdx)
		{
			mPegs[idx]->SetPegType(ePegType::Refresh);
			Collider* pCol = mPegs[idx]->GetComponent<Collider>();
			pCol->SetColliderType(eColliderType::peg);
		}
	}
}