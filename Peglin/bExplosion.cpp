#include "bExplosion.h"
#include "bAnimator.h"
#include "bObject.h"
#include "bFightScene.h"
#include "bResources.h"

namespace b
{
	bool Explosion::mEnd = false;

	Explosion::Explosion()
		: mAnimator(nullptr)
	{
	}

	Explosion::~Explosion()
	{
	}

	void Explosion::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Ball\\Bomb\\Explosion", Vector2::Zero, 0.1f);

		mAnimator->Play(L"BombExplosion", false);

		mAnimator->GetCompleteEvent(L"BombExplosion") = std::bind(&Explosion::explosionCompleteEvent, this);

		GameObject::Initialize();
	}

	void Explosion::Update()
	{

		GameObject::Update();
	}

	void Explosion::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}

	void Explosion::Release()
	{

		GameObject::Release();
	}

	void Explosion::explosionCompleteEvent()
	{
		
		object::Destory(this);
		mEnd = true;
	}
}