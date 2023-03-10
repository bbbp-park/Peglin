#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class Ball : public GameObject
	{
	public:
		Ball();
		~Ball();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

	private:
		Image* mImage;
	};

}
