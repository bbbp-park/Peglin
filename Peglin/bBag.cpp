#include "bBag.h"
#include "bAnimator.h"
#include "bInput.h"

namespace b
{
	Bag::Bag()
		: mAnimator(nullptr)
	{
	}

	Bag::~Bag()
	{
	}

	void Bag::Initialize()	
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\UI\\Bag", Vector2::Zero, 0.15f);
		
		GameObject::Initialize();
	}

	void Bag::Update()
	{
		if (Input::GetKeyDown(eKeyCode::I))
		{
			mAnimator->Play(L"UIBag", false);
		}
		GameObject::Update();
	}

	void Bag::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bag::Release()
	{
		GameObject::Release();
	}
}