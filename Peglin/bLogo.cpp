#include "bLogo.h"
#include "bAnimator.h"
#include "bTransform.h"

namespace b
{
	Logo::Logo()
	{
	}

	Logo::~Logo()
	{
	}

	void Logo::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(Vector2(10.0f, 140.0f));
		tr->SetScale(Vector2(7.0f, 7.0f));

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Logo", Vector2::Zero, 0.15f);

		mAnimator->Play(L"spriteLogo", true);
		GameObject::Initialize();
	}

	void Logo::Update()
	{
		GameObject::Update();
	}

	void Logo::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Logo::Release()
	{
		GameObject::Release();
	}
}