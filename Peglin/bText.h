#pragma once
#include "bGameObject.h"

namespace b
{
	class Text : public GameObject
	{
	public:
		Text();
		~Text();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetText(wchar_t& t) { wcscpy_s(str, &t); }
		void SetIsChange(bool b) { isChange = b; }
		void SetTextHeight(int h) { textHeight = h; }

	private:
		wchar_t str[50] = {};
		Vector2 pos;
		bool isChange;
		int textHeight;
	};
}

