#include "bText.h"
#include "bTransform.h"
#include "bInput.h"
#include "bTime.h"
#include "bObject.h"
#include "bRigidbody.h"
#include "bSound.h"
#include "bResources.h"

namespace b
{
	Text::Text()
		: str(L"")
		, mPos(Vector2::Zero)
		, isChange(false)
		, textHeight(45)
		, bDelete(false)
		, mTime(0.0f)
		, bActive(false)
		, mRigidbody(nullptr)
		, once(false)
	{
	}

	Text::~Text()
	{
	}

	void Text::Initialize()
	{
		GameObject::Initialize();

		mRigidbody = AddComponent<Rigidbody>();
		mRigidbody->SetMass(1.0f);
		mRigidbody->SetGravity(Vector2::Zero);
		mRigidbody->SetGround(false);
		mRigidbody->SetVelocity(Vector2::Zero);
	}

	void Text::Update()
	{
		GameObject::Update();

		if (bDelete)
		{
			mTime += Time::DeltaTime();

			if (mTime >= 1.2f)
			{
				object::Destory(this);
				return;
			}
		}

		if (bActive)
		{
			Vector2 vel = mRigidbody->GetVelocity();
			//float time = Time::DeltaTime();
			//time *= 10000;
			//int direction = (int)time % 2;

			//if ((int)time % 2 == 0)
			//{
			//	
			//}
			//else
			//{
			//	vel.x = -15.0f;
			//	vel.y = -10.0f;
			//}
			
			vel.x = 15.0f;
			vel.y = -10.0f;
			mRigidbody->SetVelocity(vel);
		}
	}

	void Text::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();

		Vector2 mousePos = Input::GetMousePos();

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(219, 219, 219));

		if (isChange)
		{
			if (mousePos.x >= mPos.x - 150.0f && mousePos.x <= mPos.x + 150.0f
				&& mousePos.y >= mPos.y - 10.0f && mousePos.y <= mPos.y + 90.0f)
			{
				if (once == false)
				{
					Sound* cursorMove = Resources::Load<Sound>(L"cursorMove", L"..\\Resources\\audio\\UI_Cursor_Move_06.wav");
					cursorMove->Play(false);
					once = true;
				}
				// white
				SetTextColor(hdc, RGB(219, 219, 219));
			}
			else
			{
				// gray
				SetTextColor(hdc, RGB(106, 107, 110));
				once = false;
			}
		}

		HFONT hFont = CreateFont(textHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("¸¼Àº °íµñ"));
		SetTextAlign(hdc, TA_CENTER);
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
		DeleteObject(oldFont);
		TextOut(hdc, mPos.x, mPos.y, str, wcslen(str));
	}

	void Text::Release()
	{
		GameObject::Release();
	}
}