#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include "GameTimer.h"

class D3DApp
{
protected:
	HINSTANCE mhAppInst;	//응용 프로그램 인스턴스 핸들
	HWND mhMainWnd;			//주 창 핸들
	bool mAppPaused;		//응용 프로그램 일시정지 여부
	bool mMinmized;			//응용 프로그램 최소화 여부
	bool mMaxmized;			//응용 프로그램 최대화 여부
	bool mResizing;			//사용자 크기 조정용 테두리를 끌고있는 상태인가?
	UINT m4xMsaaQuality;		//4xMSAA 품질 수준

	//경과 시간과 게임 전체 시간을 측정하는데에 쓰인다.
	GameTimer mTimer;

	//DX용 변수
	ID3D11Device* md3dDevice;						//D3D11 장치
	ID3D11DeviceContext* md3dImmediateContext;		//
	IDXGISwapChain* mSwapChain;						//페이지 전환을 위한 교환 사슬
	ID3D11Texture2D* mDepthStencilBuffer;			//깊이-스텐실 버퍼를 위한 2D 텍스쳐
	ID3D11RenderTargetView* mRenderTargetView;		//
	ID3D11DepthStencilView* mDepthStencilView;		//깊이-스텐실 뷰
	D3D11_VIEWPORT mScreenViewport;

	//다음 변수들은 D3DApp 생성자에서 기본값들로 초기화된다. 그러나 필요하다면 파생 클래스의 생성자에서 다른 값들로 초기화해도 된다.
	std::wstring mMainWndCaption;					//창의 제목. D3DApp의 기본값은 "D3D11 Application"이다.
	D3D_DRIVER_TYPE md3dDriverType;					//구동기 종류(하드웨어 장치 또는 표준 장치등) D3DApp의 기본 값은 D3D_DRIVER_TYPE_HARDWARE이다.

	//창의 클라이언트 영역의 초기크기. 기본 값은 800x600
	//그러나 이후 창의 크기가 바뀌면 현재 클라이언트 영역의 크기에 맞게 동적으로 갱신됨.
	int mClientWidth;
	int mClientHeight;

	bool mEnable4xMSAA;								//4xMSAA 사용 여부.
public:
	D3DApp(HINSTANCE hInstance);					//생성자 자료 멤버들을 기본값으로 초기화
	virtual ~D3DApp();								//소멸자. D3DApp 클래스가 획득한 COM 인터페이스들을 해제.

	HINSTANCE AppInst() const;						//응용 프로그램 인스턴스 핸들의 복사본 반환
	HWND MainWnd() const;							//주 창의 핸들의 복사본을 반환
	float AspectRatio() const;						//후면 버퍼의 종횡비를 반환.

	int Run();										//응용 프로그램 메세지 루프를 감싼 메서드. 
													//Windows 메시지가 전혀 없을 때에도 게임의 로직을 처리할 수 있도록 하기 위해 PeekMessage함수를 사용.

	//프레임워크 메서드들. 파생 클라이언트 클래스는 이 메서드들을 자신의 요구에 맞게 재정의
	virtual void Init();							//프로그램 고유의 초기화 코드 실행.
	virtual void OnResize();						//WM_SIZE 메시지가 발생했을 때 MsgProc에서 호출
	virtual void UpdateScene(float dt) = 0;			//매 프레임 호출. 응용 프로그램을 갱신하는데에 필요한 코드 실행.
	virtual void DrawScene() = 0;					//매 프레임 호출. 후면 버퍼에 실제로 그리기위한 렌더링 명령들을 실행.
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);		
													//응용 프로그램 주 창의 메시지 처리기능을 구현하는 함수.
	//마우스 입력 처리를 위한 편의용 가상 메서드들
	virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
	virtual void OnMouseUp(WPARAM btnState, int x, int y) {}
	virtual void OnMouseMove(WPARAM btnState, int x, int y) {}

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameState();						//평균 초당 프레임 수와 평균 초당 밀리초를 계산한다.
};

