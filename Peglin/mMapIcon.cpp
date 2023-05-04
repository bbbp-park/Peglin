#include "mMapIcon.h"
#include "bResources.h"
#include "bTransform.h"
#include "bImage.h"
#include "bCamera.h"
#include "bCollider.h"

namespace b
{
	MapIcon::MapIcon()
		: mImage(nullptr)
		, mImages({})
		, mType(eIconType::Skull)
		, mPos(Vector2::Zero)
		, lockPos(Vector2::Zero)
	{
	}

	MapIcon::~MapIcon()
	{
	}

	void MapIcon::Initialize()
	{
		mImages.push_back(Resources::Load<Image>(L"skull", L"..\\Resources\\sprite\\Background\\skull.bmp"));
		mImages.push_back(Resources::Load<Image>(L"moleIcon", L"..\\Resources\\sprite\\Background\\Mole_map_icon.bmp"));

		mImage = mImages[(UINT)mType];

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector2(4.0f, 4.0f));

		GameObject::Initialize();
	}

	void MapIcon::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();

		mPos = lockPos;
		mPos = Camera::CalculatePos(mPos);
		tr->SetPos(mPos);
	}

	void MapIcon::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		Transform* tr = GetComponent<Transform>();
		Vector2 scale = tr->GetScale();

		TransparentBlt(hdc, mPos.x, mPos.y
			, mImage->GetWidth() * scale.x
			, mImage->GetHeight() * scale.y
			, mImage->GetHdc(), 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, RGB(255, 0, 255));
	}

	void MapIcon::Release()
	{
		GameObject::Release();
	}

	void MapIcon::SetIconType(eIconType type)
	{
		mType = type;

		mImage = mImages[(UINT)mType];
	}
}