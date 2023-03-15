#pragma once
#include "bGameObject.h"
#include "bImage.h"

namespace b
{
	class SpeedUp : public GameObject
	{
	public:
		SpeedUp();
		~SpeedUp();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetIndicator(bool down) { isDown = down; }
		bool GetIndicator() { return isDown; }

	private:
		Image* indicator;
		Image* indicator_up;
		Image* indicator_down;

		bool isDown;
	};
}

