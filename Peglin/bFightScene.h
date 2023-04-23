#pragma once
#include "bScene.h"
#include "bImage.h"

namespace b
{
	class HPbar;
	class Peglin;
	class FightScene : public Scene
	{
	public:
		FightScene();
		~FightScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		static void CreateOrb();
		static void IsMonsterTurn(bool turn) { mTurn = turn; }
		static void SetCnt(int n) { cnt = n; }

	private:
		Peglin* mPeglin;
		HPbar* mHPbar;

		Image* forest1_bg;
		Image* forest1_tile;
		
		Image* tileSet0;
		Image* tileSet1;
		Image* tileSet2;
		Image* plunger;
		Image* backScreen;

		std::vector<class Bouncer*> mBouncers;
		std::vector<class BouncerTile*> mBouncerTiles;

		std::vector<class Peg*> mPegs;

		static bool mTurn;
		static int cnt;
	};
}

