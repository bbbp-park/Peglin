#include "bText.h"
#include "bTransform.h"
#include "bInput.h"

namespace b
{
	Text::Text()
		: str(L"")
		, pos(Vector2::Zero)
		, isChange(false)
		, textHeight(45)
	{
	}

	Text::~Text()
	{
	}

	void Text::Initialize()
	{
		GameObject::Initialize();
	}

	void Text::Update()
	{
		GameObject::Update();
	}

	void Text::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		pos = tr->GetPos();

		Vector2 mousePos = Input::GetMousePos();

		SetBkMode(hdc, 1);
		SetTextColor(hdc, RGB(219, 219, 219));

		if (isChange)
		{
			if (mousePos.x >= pos.x - 150.0f && mousePos.x <= pos.x + 150.0f
				&& mousePos.y >= pos.y - 10.0f && mousePos.y <= pos.y + 90.0f)
			{
				SetTextColor(hdc, RGB(219, 219, 219));
			}
			else
			{
				SetTextColor(hdc, RGB(106, 107, 110));
			}
		}

		HFONT hFont = CreateFont(textHeight, 0, 0, 0, 10, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("¸¼Àº °íµñ"));
		SetTextAlign(hdc, TA_CENTER);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
		TextOut(hdc, pos.x, pos.y, str, wcslen(str));

		///*HFONT hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("..\\Resources\\font\\Silver.ttf"));
		//HFONT oldFont = (HFONT)SelectObject(hdc, hFont);*/
		//TextOut(hdc, 20, 20, L"´Ù¶÷Áã", strlen("´Ù¶÷Áã"));

		Vector2 mPos = Input::GetMousePos();
		wchar_t strX[50] = {};
		swprintf_s(strX, 50, L"x : %f", mPos.y);
		TextOut(hdc, 800, 0, strX, wcsnlen_s(strX, 50));

		// 219, 219, 219
		// 106, 107, 110
	}

	void Text::Release()
	{
		GameObject::Release();
	}
}