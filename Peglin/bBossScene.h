#pragma once
#include "bScene.h"

namespace b
{
	class Image;
	class BossScene : public Scene
	{
	public:
		BossScene();
		~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		static void SetPlayerTurn(bool turn) { mTurn = turn; }
		static std::vector<class Monster*>& GetMonsters() { return mMonsters; }
		static void AddMonster(Vector2 pos, eMonsterType type);

		static void SetRedPegs();
		void SetNormalPegs();
		static void Refresh(bool isCrit);

	private:
		void CreateOrb();
		void SetCritPegs();
		void SetRefreshPegs();

	private:
		class Peglin* mPeglin;

		Image* forest2_bg;
		Image* forest2_tile;

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
		bool isClear;
		float mTime;
		int i;
	};
}

