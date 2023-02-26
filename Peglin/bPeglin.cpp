#include "bPeglin.h"
#include "bTime.h"
#include "bSceneManager.h";
#include "bInput.h";
#include "bResources.h"


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
		iPeglin = Resources::Load<Image>(L"Peglin", L"..\\Resources\\sprite.bmp\\Peglin.bmp");

		GameObject::Initialize();
	}

	void Peglin::Update()
	{
		GameObject::Update();


	}

	void Peglin::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		BitBlt(hdc, 0, 0, iPeglin->getWidth(), iPeglin->getHeight(), iPeglin->GetHdc(), 0, 0, SRCCOPY);
	}

	void Peglin::Release()
	{
		GameObject::Release();
	}
}