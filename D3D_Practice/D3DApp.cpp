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
	//��� FPS�� ����ϸ�, �ϳ��� �������� �������ϴµ��� �ɸ��� ��� �ð��� ����Ѵ�.
	//���� �� ���ġ���� â�� �����ٿ� �߰��Ѵ�.

	static int frameCnt = 0;				//������ ��
	static float timeElapsed = 0;			//��� �ð�

	//�� �� ȣ���� ������ 1������ ����.
	frameCnt++;

	//1�ʵ����� ��� ������ ���� ���
}

