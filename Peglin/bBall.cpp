#include "bBall.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"
#include "bObject.h"

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
	}

	void Ball::Update()
	{
		Transform* tr = GetComponent<Transform>();
		//Vector2 dir = Vector2(500.0f, 500.f) - tr->GetPos();
		//dir.Normalize();

		//Vector2 pos = tr->GetPos();
		//pos.x += 100.0f * dir.x * Time::DeltaTime();
		//pos.y += 100.0f * dir.y * Time::DeltaTime();
		Vector2 pos = tr->GetPos();
		pos.x += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);

		mTime += Time::DeltaTime();

		if (mTime > 2.0f)
		{
			object::Destory(this);
		}
	}

	void Ball::Render(HDC hdc)
	{
		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\Rock\\rock.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 scale = tr->GetScale();
		Vector2 pos = tr->GetPos();
		pos.x -= mImage->GetWidth();
		pos.y -= mImage->GetHeight();

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth() * scale.x, mImage->GetHeight() * scale.y, mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void Ball::Release()
	{

	}
}