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

		Animator* animator = AddComponent<Animator>();

		/*animator->CreateAnimation(L"Idle", mImage, Vector2::Zero, 9, 8, 9, Vector2::Zero, 0.15);*/
		animator->CreateAnimation(L"Idle", mImage, Vector2(0.0f, 32.0f * 0), 9, 8, 4, Vector2::Zero, 0.15);

		animator->Play(L"Idle", true);
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