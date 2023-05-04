#include "bHPbar.h"
#include "bResources.h"
#include "bPeglin.h"
#include "bTransform.h"
#include "bMonster.h"
#include "bText.h"
#include "bObject.h"

namespace b
{
	HpBar::HpBar()
		: hpUIs({})
		, bars({})
		, mType(eHpType::Player)
		, hp(0)
		, maxHp(0)
		, hpText(nullptr)
		, mIcon(nullptr)
	{
	}

	HpBar::~HpBar()
	{
	}

	void HpBar::Initialize()
	{
		hpUIs.push_back(Resources::Load<Image>(L"HpUI", L"..\\Resources\\sprite\\UI\\HealthUI\\health_ui_v3.bmp"));
		hpUIs.push_back(Resources::Load<Image>(L"MonsterHpUI", L"..\\Resources\\sprite\\UI\\HealthUI\\enemy_health_ui_extended.bmp"));
		hpUIs.push_back(Resources::Load<Image>(L"MoleHpUI", L"..\\Resources\\sprite\\UI\\HealthUI\\health_ui_no_heart.bmp"));

		bars.push_back(Resources::Load<Image>(L"bar", L"..\\Resources\\sprite\\UI\\HealthUI\\hpBar1.bmp"));
		bars.push_back(Resources::Load<Image>(L"MonsterBar", L"..\\Resources\\sprite\\UI\\HealthUI\\enemy_health_ui_bar.bmp"));

		mIcon = Resources::Load<Image>(L"MoleIcon", L"..\\Resources\\sprite\\Boss\\Mole\\Mole_health_icon.bmp");

		hpText = object::Instantiate<Text>(eLayerType::Effect);
		wchar_t str[50] = L"";
		int num = swprintf_s(str, 50, L"%d / ", hp);
		num += swprintf_s(str + num, 50 - num, L"%d", maxHp);
		hpText->SetText(*str);
		hpText->SetIsChange(false);
		hpText->SetTextHeight(32);

		GameObject::Initialize();
	}

	void HpBar::Update()
	{
		GameObject::Update();

		wchar_t str[50] = L"";
		int num = swprintf_s(str, 50, L"%d / ", hp);
		num += swprintf_s(str + num, 50 - num, L"%d", maxHp);
		hpText->SetText(*str);

		if (this->GetHpType() == eHpType::Player)
		{
			
		}
		else if (this->GetHpType() == eHpType::Monster)
		{
			
		}
	}

	void HpBar::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();

		if (this->GetHpType() == eHpType::Player)
		{
			Transform* textTr = hpText->GetComponent<Transform>();
			Vector2 textPos = pos;

			TransparentBlt(hdc, pos.x, pos.y
				, hpUIs[(UINT)eHpType::Player]->GetWidth() * scale.x
				, hpUIs[(UINT)eHpType::Player]->GetHeight() * scale.y
				, hpUIs[(UINT)eHpType::Player]->GetHdc(), 0, 0
				, hpUIs[(UINT)eHpType::Player]->GetWidth()
				, hpUIs[(UINT)eHpType::Player]->GetHeight()
				, RGB(255, 0, 255));

			float width = bars[(UINT)eHpType::Player]->GetWidth() * scale.x;
			float height = bars[(UINT)eHpType::Player]->GetHeight() * scale.y;
			float mod = (float)hp / maxHp;

			if (mod < 1)
				width *= mod;

			TransparentBlt(hdc, pos.x + 61, pos.y + 22
				, width
				, height
				, bars[(UINT)eHpType::Player]->GetHdc(), 0, 0
				, bars[(UINT)eHpType::Player]->GetWidth()
				, bars[(UINT)eHpType::Player]->GetHeight()
				, RGB(255, 0, 255));

			textPos.x += 140.0f;
			textPos.y -= 20.0f;
			textTr->SetPos(textPos);
			hpText->SetTextHeight(32);

		} 
		else if (this->GetHpType() == eHpType::Monster)
		{
			pos.x -= 30.0f;
			pos.y -= 80.0f;

			Transform* textTr = hpText->GetComponent<Transform>();
			Vector2 textPos = pos;

			TransparentBlt(hdc, pos.x, pos.y
				, hpUIs[(UINT)eHpType::Monster]->GetWidth() * scale.x
				, hpUIs[(UINT)eHpType::Monster]->GetHeight() * scale.y
				, hpUIs[(UINT)eHpType::Monster]->GetHdc(), 0, 0
				, hpUIs[(UINT)eHpType::Monster]->GetWidth()
				, hpUIs[(UINT)eHpType::Monster]->GetHeight()
				, RGB(255, 0, 255));

			float width = bars[(UINT)eHpType::Monster]->GetWidth() * scale.x;
			float height = bars[(UINT)eHpType::Monster]->GetHeight() * scale.y;
			float mod = (float)hp / maxHp;

			if (mod < 1)
				width *= mod;

			TransparentBlt(hdc, pos.x + 11, pos.y + 36				
				, width
				, height + 1
				, bars[(UINT)eHpType::Monster]->GetHdc(), 0, 0
				, bars[(UINT)eHpType::Monster]->GetWidth()
				, bars[(UINT)eHpType::Monster]->GetHeight()
				, RGB(255, 0, 255));


			textPos.x += 60.0f;
			textPos.y -= 3.0f;
			textTr->SetPos(textPos);
			hpText->SetTextHeight(28);
		}
		else if (mType == eHpType::Mole)
		{
			Transform* textTr = hpText->GetComponent<Transform>();
			Vector2 textPos = pos;

			TransparentBlt(hdc, pos.x, pos.y
				, hpUIs[(UINT)eHpType::Mole]->GetWidth() * scale.x
				, hpUIs[(UINT)eHpType::Mole]->GetHeight() * scale.y
				, hpUIs[(UINT)eHpType::Mole]->GetHdc(), 0, 0
				, hpUIs[(UINT)eHpType::Mole]->GetWidth()
				, hpUIs[(UINT)eHpType::Mole]->GetHeight()
				, RGB(255, 0, 255));

			TransparentBlt(hdc, pos.x + 10, pos.y + 10
				, mIcon->GetWidth() * scale.x
				, mIcon->GetHeight() * scale.y
				, mIcon->GetHdc(), 0, 0
				, mIcon->GetWidth()
				, mIcon->GetHeight()
				, RGB(255, 0, 255));

			float width = bars[(UINT)eHpType::Player]->GetWidth() * scale.x;
			float height = bars[(UINT)eHpType::Player]->GetHeight() * scale.y;
			float mod = (float)hp / maxHp;

			if (mod < 1)
				width *= mod;

			TransparentBlt(hdc, pos.x + 61, pos.y + 22
				, width
				, height
				, bars[(UINT)eHpType::Player]->GetHdc(), 0, 0
				, bars[(UINT)eHpType::Player]->GetWidth()
				, bars[(UINT)eHpType::Player]->GetHeight()
				, RGB(255, 0, 255));

			textPos.x += 140.0f;
			textPos.y -= 20.0f;
			textTr->SetPos(textPos);
			hpText->SetTextHeight(32);
		}
	}

	void HpBar::Release()
	{
		GameObject::Release();
	}
}