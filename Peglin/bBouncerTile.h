#pragma once
#include "bGameObject.h"

namespace b
{
	class BouncerTile : public GameObject
	{
	public:
		BouncerTile();
		~BouncerTile();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		virtual void Release();

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		class Image* tileImage;
		Collider* tileCol;
	};
}

