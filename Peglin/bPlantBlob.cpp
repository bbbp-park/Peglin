#include "bPlantBlob.h"
#include "bAnimator.h"
#include "bCollider.h"
#include "bTransform.h"
#include "bPeglin.h"
#include "bObject.h"
#include "bTime.h"
#include "bResources.h"

namespace b
{
	int PlantBlob::power = 0;

	PlantBlob::PlantBlob()
		: mAnimator(nullptr)
	{
	}

	PlantBlob::~PlantBlob()
	{
	}

	void PlantBlob::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimations(L"..\\Resources\\sprite\\Monster\\SmallPlant\\Blob", Vector2::Zero, 0.15f);
		mAnimator->Play(L"SmallPlantBlob", true);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(3.0f, 3.0f));

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(-5.0f, 5.0f));
		collider->SetSize(Vector2(35.0f, 35.0f));

		GameObject::Initialize();
	}

	void PlantBlob::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		pos.x -= 20.0f * Time::DeltaTime();

		tr->SetPos(pos);
	}

	void PlantBlob::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PlantBlob::Release()
	{
		GameObject::Release();
	}

	void PlantBlob::OnCollisionEnter(Collider* other)
	{
		Peglin* peglin = dynamic_cast<Peglin*>(other->GetOwner());
		peglin->CalHp(power);
		object::Destory(this);
	}

	void PlantBlob::OnCollisionStay(Collider* other)
	{
	}

	void PlantBlob::OnCollisionExit(Collider* other)
	{
	}
}