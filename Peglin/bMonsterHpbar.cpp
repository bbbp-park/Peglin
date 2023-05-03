//#include "bMonsterHpbar.h"
//#include "bResources.h"
//#include "bObject.h"
//#include "bText.h"
//#include "bImage.h"
//
//namespace b
//{
//	MonsterHpbar::MonsterHpbar()
//		: hpUI(nullptr)
//		, bar(nullptr)
//		, hp(0)
//		, maxHp(0)
//		, hpText(nullptr)
//	{
//	}
//
//	MonsterHpbar::~MonsterHpbar()
//	{
//	}
//	void MonsterHpbar::Initialize()
//	{
//		hpUI = Resources::Load<Image>(L"monsterHpUI", L"..\\Resources\\sprite\\UI\\HealthUI\\enemy_health_ui_extended.bmp");
//		bar = Resources::Load<Image>(L"monsterBar", L"..\\Resources\\sprite\\UI\\HealthUI\\enemy_health_ui_bar.bmp");
//
//		hpText = object::Instantiate<Text>(eLayerType::Effect);
//		wchar_t str[50] = L"";
//		int num = swprintf_s(str, 50, L"%d / ", hp);
//		num += swprintf_s(str + num, 50 - num, L"%d", maxHp);
//		hpText->SetText(*str);
//		hpText->SetIsChange(false);
//		hpText->SetTextHeight(32);
//
//		GameObject::Initialize();
//	}
//
//	void MonsterHpbar::Update()
//	{
//		GameObject::Update();
//
//		wchar_t str[50] = L"";
//		int num = swprintf_s(str, 50, L"%d / ", hp);
//		num += swprintf_s(str + num, 50 - num, L"%d", maxHp);
//		hpText->SetText(*str);
//	}
//
//	void MonsterHpbar::Render(HDC hdc)
//	{
//		Transform* tr = GetComponent<Transform>();
//		Vector2 scale = tr->GetScale();
//		Vector2 pos = tr->GetPos();
//
//		pos.x -= 30.0f;
//		pos.y -= 80.0f;
//
//		TransparentBlt(hdc, pos.x, pos.y
//			, hpUI->GetWidth() * scale.x
//			, hpUI->GetHeight() * scale.y
//			, hpUI->GetHdc(), 0, 0
//			, hpUI->GetWidth()
//			, hpUI->GetHeight()
//			, RGB(255, 0, 255));
//
//		float width = bar->GetWidth() * scale.x;
//		float height = bar->GetHeight() * scale.y;
//		float mod = (float)hp / maxHp;
//
//		if (mod < 1)
//			width *= mod;
//
//		TransparentBlt(hdc, pos.x + 11, pos.y + 36
//			, width
//			, height + 1
//			, bar->GetHdc(), 0, 0
//			, bar->GetWidth()
//			, bar->GetHeight()
//			, RGB(255, 0, 255));
//
//		Transform* textTr = hpText->GetComponent<Transform>();
//		Vector2 textPos = pos;
//		textPos.x += 60.0f;
//		textPos.y -= 3.0f;
//		textTr->SetPos(textPos);
//		hpText->SetTextHeight(28);
//		GameObject::Render(hdc);
//	}
//
//	void MonsterHpbar::Release()
//	{
//	}
//}