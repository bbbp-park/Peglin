#pragma once
#include "bResource.h"

namespace b
{
	class Image : public Resource
	{
	public:
		static Image* Create(const std::wstring& name, UINT widht, UINT height, COLORREF rgb = RGB(255, 255, 255));

		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		COLORREF GetPixel(int x, int y);
		void SetPixel(int x, int y, COLORREF color);

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		int GetWidth() { return mWidth; }
		int GetHeight() { return mHeight; }

	private:
		HDC mHdc;
		HBITMAP mBitmap;
		UINT mWidth;
		UINT mHeight;
	};
}

