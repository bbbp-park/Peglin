#pragma once
#include "bResource.h"

namespace b
{
	class Image : public Resource
	{
	public:
		Image();
		~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		HDC GetHdc() { return mHdc; }
		HBITMAP GetBitmap() { return mBitmap; }
		UINT getWidth() { return mWidth; }
		UINT getHeight() { return mHeight; }

	private:
		HDC mHdc;
		HBITMAP mBitmap;
		UINT mWidth;
		UINT mHeight;
	};
}

