#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class Monster : public GameObject
	{
	public:
		
		struct Info
		{
			int hp;
			int maxHp;
			int power;
		};

		Monster();
		~Monster();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetMonsterType(eMonsterType type);
		void SetHp(int hp) { mInfo.hp = hp; }
		void SetPower(int power) { mInfo.power = power; }

		void SetEventComplete(bool b) { eventComplete = b; }
		bool GetEventComplete() { return eventComplete; }
		eMonsterState GetMonsterState() { return mState; }

		void StumpDeathCompleteEvent();
		void StumpMoveCompleteEvent();
		void StumpAttackCompleteEvent();

		int GetHp() { return mInfo.hp; }

		void StartEvent();

	private:
		void attack();
		void death();
		void idle();
		void move();


	private:
		class HpBar* hpBar;
		class Text* hpText;

		Animator* mAnimator;
		Info mInfo;
		eMonsterType mType;

		class Rigidbody* mRigidbody;
		bool eventComplete;

		Vector2 distance;
		int bombCnt;

		eMonsterState mState;
		class Text* mText;
	};
}

