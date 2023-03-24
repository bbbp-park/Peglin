#pragma once
#include "bEngine.h"

namespace b
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void Render();

		HWND GetHwnd() { return mHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

	private:
		void clear();

	private:
		HWND mHwnd;
		HDC mHdc;

		// back buffer
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}

