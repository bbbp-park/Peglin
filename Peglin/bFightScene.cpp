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
#include "bOrb.h"
#include "bBouncer.h"
#include "bBouncerTile.h"
#include "bWall.h"
#include "bPeg.h"
#include "bGameObject.h"
#include "bTime.h"

namespace b
{
	bool FightScene::mTurn = true;
	int FightScene::cnt = 0;
	std::vector<Monster*> FightScene::mMonsters = {};

	int i = 0;

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
		, mBouncers({})
		, mBouncerTiles({})
		, mPegs({})
		, isClear(false)
		, mTime(0.0f)
	{
	}

	FightScene::~FightScene()
	{
	}

	void FightScene::Initialize()
	{
		Scene::Initialize();

		mPeglin = object::Instantiate<Peglin>(Vector2(410.0f, 170.0f), Vector2(3.0f, 3.0f), eLayerType::Player);

		object::Instantiate<Orb>(Vector2(900.0f, 320.0f), Vector2(2.0f, 2.0f), eLayerType::Orb);

		mMonsters.push_back(object::Instantiate<Monster>(Vector2(890.0f, 180.0f), Vector2(3.0f, 3.0f), eLayerType::Monster));
		mMonsters[0]->SetMonsterType(eMonsterType::Stump);
		mMonsters.push_back(object::Instantiate<Monster>(Vector2(1300.0f, 180.0f), Vector2(3.0f, 3.0f), eLayerType::Monster));
		mMonsters[1]->SetMonsterType(eMonsterType::Stump);

		//object::Instantiate<Bag>(Vector2(140.0f, 0.0f), Vector2(2.4f, 2.4f), eLayerType::UI);
		//object::Instantiate<SpeedUp>(eLayerType::UI);

		object::Instantiate<Wall>(Vector2(469.0f, 250.0f), eLayerType::Wall);
		object::Instantiate<Wall>(Vector2(1273.0f, 250.0f), eLayerType::Wall);


		// peg setting
		mPegs.push_back(object::Instantiate<Peg>(Vector2(528.0f, 506.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(528.0f, 667.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(551.0f, 461.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(551.0f, 714.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(551.0f, 764.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(551.0f, 810.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(576.0f, 366.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(576.0f, 416.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(576.0f, 592.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(576.0f, 638.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(598.0f, 687.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(598.0f, 734.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(598.0f, 781.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(611.0f, 444.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(634.0f, 486.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(634.0f, 532.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(634.0f, 580.0f), eLayerType::Peg));
		

		mPegs.push_back(object::Instantiate<Peg>(Vector2(671.0f, 379.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(671.0f, 427.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(671.0f, 711.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(671.0f, 757.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(671.0f, 804.0f), eLayerType::Peg)); 

		mPegs.push_back(object::Instantiate<Peg>(Vector2(695.0f, 586.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(695.0f, 664.0f), eLayerType::Peg));

		

		mPegs.push_back(object::Instantiate<Peg>(Vector2(730.0f, 627.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(753.0f, 390.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(753.0f, 438.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(753.0f, 733.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(753.0f, 783.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(790.0f, 487.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(790.0f, 533.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(790.0f, 580.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(790.0f, 638.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(790.0f, 699.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(811.0f, 757.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(822.0f, 787.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(836.0f, 426.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(848.0f, 628.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(848.0f, 722.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(860.0f, 676.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(872.0f, 474.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(883.0f, 580.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(896.0f, 522.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(910.0f, 676.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(918.0f, 462.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(918.0f, 628.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(918.0f, 722.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(944.0f, 787.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(954.0f, 757.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(953.0f, 426.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 486.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 532.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 580.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 638.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(977.0f, 698.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1014.0f, 390.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1014.0f, 438.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1014.0f, 736.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1014.0f, 784.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1036.0f, 630.0f), eLayerType::Peg));

		

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1072.0f, 586.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1072.0f, 662.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1096.0f, 380.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1096.0f, 426.0f), eLayerType::Peg)); 
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1096.0f, 711.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1096.0f, 758.0f), eLayerType::Peg)); 
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1096.0f, 804.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1132.0f, 486.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1132.0f, 534.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1132.0f, 580.0f), eLayerType::Peg));
		

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1154.0f, 444.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1166.0f, 688.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1166.0f, 734.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1166.0f, 782.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1190.0f, 370.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1190.0f, 416.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1190.0f, 592.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1190.0f, 640.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1214.0f, 464.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1214.0f, 712.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1214.0f, 760.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1214.0f, 806.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(1238.0f, 510.0f), eLayerType::Peg));
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1238.0f, 662.0f), eLayerType::Peg));

		mPegs.push_back(object::Instantiate<Peg>(Vector2(634.0f, 634.0f), eLayerType::Peg)); // bomb 17
		mPegs[84]->SetType(ePegType::Bomb);
		mPegs.push_back(object::Instantiate<Peg>(Vector2(719.0f, 514.0f), eLayerType::Peg)); // bomb 25
		mPegs[85]->SetType(ePegType::Bomb);
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1050.0f, 516.0f), eLayerType::Peg)); // bomb 62
		mPegs[86]->SetType(ePegType::Bomb);
		mPegs.push_back(object::Instantiate<Peg>(Vector2(1132.0f, 632.0f), eLayerType::Peg)); // bomb 73
		mPegs[87]->SetType(ePegType::Bomb);

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

		forest1_bg = Resources::Load<Image>(L"forest1_bg", L"..\\Resources\\sprite\\Background\\forest_1_background.bmp");
		forest1_tile = Resources::Load<Image>(L"forest1_tile", L"..\\Resources\\sprite\\Background\\forest_1_tile.bmp");

		tileSet0 = Resources::Load<Image>(L"tileSet0", L"..\\Resources\\sprite\\Background\\Tile\\tileset_24.bmp");
		plunger = Resources::Load<Image>(L"plunger", L"..\\Resources\\sprite\\Background\\Tile\\plunger.bmp");
		backScreen = Resources::Load<Image>(L"titleBackground", L"..\\Resources\\sprite\\Background\\TitleSceneBackground.bmp");
	}

	void FightScene::Update()
	{
		Scene::Update();

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
		
		CollisionManager::SetLayer(eLayerType::Ball, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Peg, true);
	}

	void FightScene::OnExit()
	{
		Camera::StartFadeOut();

		CollisionManager::SetLayer(eLayerType::Ball, eLayerType::Monster, false);
		CollisionManager::SetLayer(eLayerType::Bomb, eLayerType::Wall, false);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Wall, false);
		CollisionManager::SetLayer(eLayerType::Orb, eLayerType::Peg, false);
	}

	void FightScene::CreateOrb()
	{
		Orb* orb = object::Instantiate<Orb>(Vector2(900.0f, 320.0f), Vector2(2.0f, 2.0f), eLayerType::Orb);
	}
}