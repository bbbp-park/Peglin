#include "bHPbar.h"
#include "bResources.h"

namespace b
{
	HPbar::HPbar()
	{
	}

	HPbar::~HPbar()
	{
	}

	void HPbar::Initialize()
	{
		image = Resources::Load<Image>(L"HPbar", L"..\\Resources\\sprite\\UI\\HealthUI\\health_ui_v3.bmp");
		GameObject::Initialize();
	}

	void HPbar::Update()
	{
		GameObject::Update();
	}

	void HPbar::Render(HDC hdc)
	{
		TransparentBlt(hdc, 100, 285
			, image->GetWidth() * 3.7
			, image->GetHeight() * 3.7
			, image->GetHdc(), 0, 0
			, image->GetWidth()
			, image->GetHeight()
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void HPbar::Release()
	{
		GameObject::Release();
	}
}