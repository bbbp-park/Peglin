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
	{/*
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));

		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\rock.bmp");*/

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
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(2.0f, 2.0f));
		Vector2 pos = tr->GetPos();

		mImage = Resources::Load<Image>(L"Rock", L"..\\Resources\\sprite\\Ball\\rock.bmp");

		TransparentBlt(hdc, pos.x, pos.y, mImage->GetWidth(), mImage->GetHeight(), mImage->GetHdc(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), RGB(255, 0, 255));
	}

	void Ball::Release()
	{

	}
}