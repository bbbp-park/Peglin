#include "bBall.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"
#include "bObject.h"
#include "bCollider.h"

namespace b
{
	Ball::Ball()
		: mImage(nullptr)
		, mTime(0.0f)
	{
	}

	Ball::~Ball()
	{
	}

	void Ball::Initialize()
	{
		/*mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\rock.bmp");*/

		Collider* collider = AddComponent<Collider>();
		collider->SetCenter(Vector2(5.0f, 5.0f));
		collider->SetSize(Vector2(35.0f, 35.0f));

		GameObject::Initialize();
	}

	void Ball::Update()
	{
		Transform* tr = GetComponent<Transform>();
		
		Vector2 pos = tr->GetPos();
		pos.x += 600.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 2.0f)
		{
			//object::Destory(this);
		}

		GameObject::Update();
	}

	void Ball::Render(HDC hdc)
	{
		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\Rock\\rock.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Ball::Release()
	{
		GameObject::Release();
	}

	void Ball::OnCollisionEnter(Collider* other)
	{
		object::Destory(this);
	}

	void Ball::OnCollisionStay(Collider* other)
	{
	}

	void Ball::OnCollisionExit(Collider* other)
	{
	}
}