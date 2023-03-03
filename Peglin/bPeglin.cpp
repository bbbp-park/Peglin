#include "bPeglin.h"
#include "bTime.h"
#include "bSceneManager.h";
#include "bInput.h";
#include "bResources.h"
#include "bTransform.h"
#include "bAnimator.h"


namespace b
{
	Peglin::Peglin()
	{
	}

	Peglin::~Peglin()
	{
	}

	void Peglin::Initialize()
	{
		Image* mImage = Resources::Load<Image>(L"Peglin", L"..\\Resources\\sprite.bmp\\peglin.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Peglin\\Idle", Vector2::Zero, 0.15f);

		mAnimator->Play(L"PeglinIdle", true);
		GameObject::Initialize();
	}

	void Peglin::Update()
	{
		GameObject::Update();

		/*Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();*/
	}

	void Peglin::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Peglin::Release()
	{
		GameObject::Release();
	}
}