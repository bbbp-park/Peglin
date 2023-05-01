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
				// white
				SetTextColor(hdc, RGB(219, 219, 219));
			}
			else
			{
				// gray
				SetTextColor(hdc, RGB(106, 107, 110));
			}
		}

		HFONT hFont = CreateFont(textHeight, 0, 0, 0, 10, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("¸¼Àº °íµñ"));
		SetTextAlign(hdc, TA_CENTER);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
		TextOut(hdc, pos.x, pos.y, str, wcslen(str));
	}

	void Text::Release()
	{
		GameObject::Release();
	}
}