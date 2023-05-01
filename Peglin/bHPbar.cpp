#include "bHPbar.h"
#include "bResources.h"
#include "bPeglin.h"
#include "bTransform.h"
#include "bMonster.h"

namespace b
{
	HPbar::HPbar()
		: hpUIs({})
		, bars({})
		, mType(eHpType::Player)
		, hp(0)
		, maxHp(0)
	{
	}

	HPbar::~HPbar()
	{
	}

	void HPbar::Initialize()
	{
		hpUIs.push_back(Resources::Load<Image>(L"HpUI", L"..\\Resources\\sprite\\UI\\HealthUI\\health_ui_v3.bmp"));
		hpUIs.push_back(Resources::Load<Image>(L"MonsterHpUI", L"..\\Resources\\sprite\\UI\\HealthUI\\enemy_health_ui_extended.bmp"));

		bars.push_back(Resources::Load<Image>(L"bar", L"..\\Resources\\sprite\\UI\\HealthUI\\hpBar1.bmp"));
		bars.push_back(Resources::Load<Image>(L"MonsterBar", L"..\\Resources\\sprite\\UI\\HealthUI\\enemy_health_ui_bar.bmp"));

		Transform* tr = GetComponent<Transform>();

		GameObject::Initialize();
	}

	void HPbar::Update()
	{
		GameObject::Update();
	}

	void HPbar::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();

		if (this->GetHpType() == eHpType::Player)
		{
			TransparentBlt(hdc, pos.x, pos.y
				, hpUIs[0]->GetWidth() * scale.x
				, hpUIs[0]->GetHeight() * scale.y
				, hpUIs[0]->GetHdc(), 0, 0
				, hpUIs[0]->GetWidth()
				, hpUIs[0]->GetHeight()
				, RGB(255, 0, 255));

			float width = bars[0]->GetWidth() * scale.x;
			float height = bars[0]->GetHeight() * scale.y;
			float mod = (float)hp / maxHp;

			if (mod < 1)
				width *= mod;

			TransparentBlt(hdc, pos.x + 61, pos.y + 22
				, width
				, height
				, bars[0]->GetHdc(), 0, 0
				, bars[0]->GetWidth()
				, bars[0]->GetHeight()
				, RGB(255, 0, 255));
		}
		
		if (this->GetHpType() == eHpType::Monster)
		{
			pos.x -= 30.0f;
			pos.y -= 80.0f;

			TransparentBlt(hdc, pos.x, pos.y
				, hpUIs[1]->GetWidth() * scale.x
				, hpUIs[1]->GetHeight() * scale.y
				, hpUIs[1]->GetHdc(), 0, 0
				, hpUIs[1]->GetWidth()
				, hpUIs[1]->GetHeight()
				, RGB(255, 0, 255));

			float width = bars[1]->GetWidth() * scale.x;
			float height = bars[1]->GetHeight() * scale.y;
			float mod = (float)hp / maxHp;

			if (mod < 1)
				width *= mod;

			TransparentBlt(hdc, pos.x + 11, pos.y + 36				
				, width
				, height + 1
				, bars[1]->GetHdc(), 0, 0
				, bars[1]->GetWidth()
				, bars[1]->GetHeight()
				, RGB(255, 0, 255));
		}
		
		GameObject::Render(hdc);
	}

	void HPbar::Release()
	{
		GameObject::Release();
	}
}