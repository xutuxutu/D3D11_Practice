#include "D3DApp.h"

D3DApp::D3DApp(HINSTANCE hInstance)
{
}


D3DApp::~D3DApp()
{
}

LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			mAppPaused = true;
		}
		else
		{
			mAppPaused = false;
		}
	}
}

void D3DApp::CalculateFrameState()
{
	//평균 FPS를 계산하며, 하나의 프레임을 렌더링하는데에 걸리는 평균 시간도 계산한다.
	//또한 이 통계치들을 창의 제목줄에 추가한다.

	static int frameCnt = 0;				//프레임 수
	static float timeElapsed = 0;			//경과 시간

	//한 번 호출할 때마다 1프레임 증가.
	frameCnt++;

	//1초동안의 평균 프레임 수를 계산
}

