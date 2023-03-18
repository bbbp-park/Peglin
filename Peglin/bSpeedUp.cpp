#include "bSpeedUp.h"
#include "bResources.h"
#include "bTransform.h"
#include "bInput.h"

namespace b
{
	SpeedUp::SpeedUp()
		: isDown(false)
	{
	}

	SpeedUp::~SpeedUp()
	{
	}

	void SpeedUp::Initialize()
	{
		indicator_up = Resources::Load<Image>(L"indicator_up", L"..\\Resources\\sprite\\UI\\SpeedUp\\speedup_indicator_up.bmp");

		indicator_down = Resources::Load<Image>(L"indicator_down", L"..\\Resources\\sprite\\UI\\SpeedUp\\speedup_indicator_down.bmp");

		indicator = indicator_up;

		GameObject::Initialize();
	}

	void SpeedUp::Update()
	{
		if (isDown)
		{
			indicator = indicator_down;
		}
		else
		{
			indicator = indicator_up;
		}

		GameObject::Update();
	}

	void SpeedUp::Render(HDC hdc)
	{
		TransparentBlt(hdc, 100, 750
			, indicator->GetWidth() * 2.4
			, indicator->GetHeight() * 2.4
			, indicator->GetHdc(), 0, 0
			, indicator->GetWidth()
			, indicator->GetHeight()
			, RGB(255, 0, 255));
		GameObject::Render(hdc);
	}

	void SpeedUp::Release()
	{
		GameObject::Release();
	}

}