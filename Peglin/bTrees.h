#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class Trees : public GameObject
	{
	public:
		Trees();
		~Trees();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* treeTop;
		Image* treeBottom;

		Vector2 mPos;
	};
}

