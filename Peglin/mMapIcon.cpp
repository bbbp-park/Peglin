#include "mMapIcon.h"
#include "bResources.h"
#include "bTransform.h"
#include "bImage.h"
#include "bCamera.h"

namespace b
{
	MapIcon::MapIcon()
		: mImage(nullptr)
		, mImages({})
		, mType(eIconType::Skull)
		, mPos(Vector2::Zero)
	{
	}

	MapIcon::~MapIcon()
	{
	}

	void MapIcon::Initialize()
	{
		mImages.push_back(Resources::Load<Image>(L"skull", L"..\\Resources\\sprite\\Background\\skull.bmp"));
		mImages.push_back(Resources::Load<Image>(L"moleIcon", L"..\\Resources\\sprite\\Background\\Mole_map_icon.bmp"));

		mImage = mImages[0];

		Transform* tr = GetComponent<Transform>();
		mPos = tr->GetPos();
	}

	void MapIcon::Update()
	{
		if (mType == eIconType::Skull)
			mImage = mImages[(UINT)eIconType::Skull];

		if (mType == eIconType::Mole)
			mImage = mImages[(UINT)eIconType::Mole];

		/*Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();
		pos = Camera::CalculatePos(pos);
		tr->SetPos(pos);*/
		//Vector2 mPos;
		mPos = Vector2(800, 600);
		mPos = Camera::CalculatePos(mPos);
		Transform* tr = GetComponent<Transform>();
		tr->SetPos(mPos);
	}

	void MapIcon::Render(HDC hdc)
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPos();

		TransparentBlt(hdc, mPos.x, mPos.y
			, mImage->GetWidth() * 4.0f
			, mImage->GetHeight() * 4.0f
			, mImage->GetHdc(), 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, RGB(255, 0, 255));
	}

	void MapIcon::Release()
	{
	}
}