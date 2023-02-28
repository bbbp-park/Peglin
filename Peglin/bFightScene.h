#pragma once
#include "bScene.h"
#include "bImage.h"

namespace b
{
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
	private:
		Image* forest1_bg;
		Image* forest1_tile;
		Image* forest2_bg;
		Image* forest2_tile;
	};
}

