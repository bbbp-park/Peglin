#pragma once
#include "bEngine.h"

namespace b
{
	class GameObject;
	class Camera
	{
	public:
		enum class eCameraEffectType
		{
			None,
			FadeIn,
			FadeOut,
			End,
		};

		static void Initiailize();
		static void Update();
		static void Render(HDC hdc);
		static void Clear();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }

		static void StartFadeIn()
		{
			mType = eCameraEffectType::FadeIn;
			mCuttonAlpha = 1.0f;
			mAlphaTime = 0.0f;
		}

		static void StartFadeOut()
		{
			mType = eCameraEffectType::FadeOut;
			mCuttonAlpha = 1.0f;
			mAlphaTime = 0.0f;
		}

	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

		static eCameraEffectType mType;
		static class Image* mCutton;
		static float mCuttonAlpha;
		static float mAlphaTime;
		static float mEndTime;

		static bool mbMove;
	};
}

