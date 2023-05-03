#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class HpBar : public GameObject
	{
	public:
		HpBar();
		~HpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetHpType(eHpType type) { mType = type; }
		eHpType GetHpType() { return mType; }

		void SetHp(int h) { hp = h; }
		void SetMaxHp(int h) { maxHp = h; }

	private:
		std::vector<Image*> hpUIs;
		std::vector<Image*> bars;

		eHpType mType;

		int hp;
		int maxHp;
		class Text* hpText;
	};
}

