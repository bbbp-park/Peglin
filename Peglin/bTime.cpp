#include "bTime.h"
#include "bApplication.h"

extern b::Application application;

namespace b
{
	double Time::mDeltaTime = 0.0l;
	double Time::mSecond = 0.0f;
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};

	void Time::Initiailize()
	{
		// CPU ���� ������ ��������
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷��� ó�� �����Ҷ� ������
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differenceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differenceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCpuFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = application.GetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"FPS : %d", (UINT)FPS);

			SetWindowText(hWnd, szFloat);

			mSecond = 0.0f;
		}
	}
}