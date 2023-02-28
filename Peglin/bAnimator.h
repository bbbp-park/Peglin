#pragma once
#include "bComponent.h"
#include "bAnimation.h"
#include "bImage.h"

namespace b
{
	class Animator : public Component
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

		Animator();
		~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		// �ϼ��� ��������Ʈ ��Ʈ�� �����ؼ� �ִϸ��̼��� ����
		void CreateAnimation(const std::wstring& name, Image* sheet, Vector2 leftTop, UINT coulmn, UINT row, UINT spriteLenght, Vector2 offset, float duration);

		// ��������Ʈ�� �̿��ؼ� �ִϸ��̼� ����
		void CreateAnimations();

		Animation* FindAnimation(const std::wstring& name);
		void Play(const std::wstring& name, bool loop);

		Event* FindEvents(const std::wstring* name);

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		Image* mSpriteSheet;
		bool mbLoop;
	};
}
