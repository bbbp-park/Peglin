#include "bBall.h"
#include "bTransform.h"
#include "bTime.h"
#include "bResources.h"
#include "bImage.h"

namespace b
{
	Ball::Ball()
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
		Vector2 pos = tr->GetPos();
		pos.x += 100.0f * Time::DeltaTime();
		tr->SetPos(pos);
	}

	void Ball::Render(HDC hdc)
	{
		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\rock.bmp");

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