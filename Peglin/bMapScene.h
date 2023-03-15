#pragma once
#include "bScene.h"
#include "bImage.h"

namespace b
{
	class SpeedUp;
	class MapPeglin;
	class MapScene : public Scene
	{
	public:
		MapScene();
		~MapScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
		MapPeglin* mMapPeglin;

		Image* treeTop;

		SpeedUp* mSpeedUp;
	};
}

