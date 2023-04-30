#pragma once
#include "bGameObject.h"

namespace b
{
	class Animator;
	class Monster : public GameObject
	{
	public:
		enum class eMonsterType
		{
			Stump
		};

		enum class eStumpState
		{
			Idle,
			Move,
			Attack,
			Dead,
		};

		struct Info
		{
			int hp;
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

		void SetIdx(int i) { idx = i; }

		void SetMonsterType(eMonsterType type);
		void SetHp(int hp) { mInfo.hp = hp; }
		void SetPower(int power) { mInfo.power = power; }

		void SetEventComplete(bool b) { eventComplete = b; }
		bool GetEventComplete() { return eventComplete; }

		void StumpDeathCompleteEvent();
		void StumpMoveCompleteEvent();
		void StumpAttackCompleteEvent();




		void StartEvent();

	private:
		void attack();
		void death();
		void idle();
		void move();


	private:
		Animator* mAnimator;
		Info mInfo;
		eMonsterType mType;

		class Rigidbody* mRigidbody;
		bool eventComplete;

		int idx;
		float mTime;
		Vector2 distance;

		eStumpState stumpState;
	};
}

