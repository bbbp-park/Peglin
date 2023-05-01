#pragma once
#include "bGameObject.h"
#include "bImage.h"

namespace b
{
	class HPbar : public GameObject
	{
	public:
		HPbar();
		~HPbar();

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
	};
}

