#include "bMonster.h"
#include "bTransform.h"
#include "bAnimator.h"
#include "bCollider.h"

namespace b
{
	Monster::Monster()
		: mAnimator(nullptr)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		/*Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(800.0f, 240.0f));
		tr->SetScale(Vector2(3.0f, 3.0f));*/

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\Slime\\GreenSlime\\Idle", Vector2::Zero, 0.15f);

		mAnimator->Play(L"GreenSlimeIdle", true);

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-15.0f, -20.0f));
		collider->SetSize(Vector2(60.0f, 60.0f));

		GameObject::Initialize();
	}

	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Monster::Release()
	{
		GameObject::Release();
	}
	void Monster::OnCollisionEnter(Collider* other)
	{
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}
}