#include "bTrees.h"
#include "bResources.h"
#include "bTransform.h"
#include "bCamera.h"
#include "bImage.h"

namespace b
{
	Trees::Trees()
		: treeTop(nullptr)
		, treeBottom(nullptr)
		, mPos(Vector2::Zero)
	{
	}

	Trees::~Trees()
	{
	}

	void Trees::Initialize()
	{
		treeTop = Resources::Load<Image>(L"treeTop", L"..\\Resources\\sprite\\Background\\treetop_.bmp");
		treeBottom = Resources::Load<Image>(L"treeTop", L"..\\Resources\\sprite\\Background\\treetop_.bmp");
	}

	void Trees::Update()
	{
		Transform* tr = GetComponent<Transform>();

		mPos = Vector2(-990, -600);
		mPos = Camera::CalculatePos(mPos);
		tr->SetPos(mPos);
	}

	void Trees::Render(HDC hdc)
	{
		TransparentBlt(hdc, mPos.x, mPos.y
			, treeTop->GetWidth() * 2.4
			, treeTop->GetHeight() * 2.4
			, treeTop->GetHdc(), 0, 0
			, treeTop->GetWidth()
			, treeTop->GetHeight()
			, RGB(255, 0, 255));

		TransparentBlt(hdc, mPos.x, mPos.y + 2000
			, treeBottom->GetWidth() * 2.4
			, treeBottom->GetHeight() * 2.4
			, treeBottom->GetHdc(), 0, 0
			, treeBottom->GetWidth()
			, treeBottom->GetHeight()
			, RGB(255, 0, 255));
	}

	void Trees::Release()
	{
	}
}
