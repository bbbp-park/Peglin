#pragma once
#include "bGameObject.h"

namespace b
{
	class Image;
	class Peg : public GameObject
	{
	public:
		Peg();
		~Peg();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		virtual void Release() override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetType(ePegType type) { mType = type; }
		ePegType GetType() { return mType; }

		void deletePeg();
		void deleteBomb();

	private:
		Collider* collider;
		class Animator* mAnimator;

		std::vector<Image*> mImages;
		ePegType mType;

		int durability;
	};

}
