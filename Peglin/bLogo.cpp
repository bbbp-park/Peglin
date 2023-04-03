#include "bLogo.h"
#include "bAnimator.h"
#include "bTransform.h"

namespace b
{
	Logo::Logo()
		: mAnimator(nullptr)
	{
	}

	Logo::~Logo()
	{
	}

	void Logo::Initialize()
	{
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