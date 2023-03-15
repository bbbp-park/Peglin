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

	private:
		Image* image;
	};
}

