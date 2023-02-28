#pragma once
#include "bEntity.h"

namespace b
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;
			Vector2 size;
			Vector2 offSet;
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offSet(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

		Animation();
		~Animation();

		void Initialize();
		void Update();
		void Render(HDC hdc);

		void Create(Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLenght, Vector2 offset, float duration);
		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private:
		Animator* mAnimator;
		Image* mSheetImage;
		std::vector<Sprite> mSpriteSheet;
		float mTime;
		bool mbComplete;
		int mSpriteIndex;
	};
}
