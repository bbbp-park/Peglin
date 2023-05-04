#pragma once
#include "bScene.h"

namespace b
{
	class HpBar;
	class Peglin;
	class Image;
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

		static void SetPlayerTurn(bool turn) { mTurn = turn; }

		// false = monster turn, true = player turn
		static bool GetPlayerTurn() { return mTurn; }
		static std::vector<class Monster*>& GetMonsters() { return mMonsters; }
		static bool GetIsClear() { return isClear; }

		static void SetRedPegs();
		void SetNormalPegs();
		static void Refresh(bool isCrit);

	private:
		void CreateOrb();
		void SetCritPegs();
		void SetRefreshPegs();

	private:
		Peglin* mPeglin;

		Image* forest1_bg;
		Image* forest1_tile;
		
		Image* tileSet0;
		Image* tileSet1;
		Image* tileSet2;
		Image* plunger;
		Image* backScreen;

		std::vector<class Bouncer*> mBouncers;
		std::vector<class BouncerTile*> mBouncerTiles;

		class Orb* mOrb;
		static std::vector<class Peg*> mPegs;
		std::vector<int> CritIdx;
		std::vector<int> RefreshIdx;
		static std::vector<class Monster*> mMonsters;

		static bool mTurn;
		int cnt;
		static bool isClear;
		float mTime;
		int i;
	};
}

