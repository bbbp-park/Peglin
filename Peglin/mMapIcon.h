#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class MapIcon : public GameObject
	{
	public:
		MapIcon();
		~MapIcon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		void SetIconType(eIconType type) { mType = type; }

	private:
		Image* mImage;
		std::vector<Image*> mImages;

		eIconType mType;
		Vector2 mPos;
	};
}

