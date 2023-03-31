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

		void SetMenuBar(bool power);

		HWND GetHwnd() { return mHwnd; }
		HWND GetToolHwnd() { return mToolHwnd; }
		HDC GetHdc() { return mHdc; }
		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }

		void SetToolHwnd(HWND hwnd) { mToolHwnd = hwnd; }

	private:
		void clear();

	private:
		// main
		HWND mHwnd;
		HDC mHdc;
		HMENU mMenubar;

		// back buffer
		HBITMAP mBackBuffer;
		HDC mBackHDC;

		// tool
		HWND mToolHwnd;

		UINT mWidth;
		UINT mHeight;

		Vector2 mPos;
	};
}

