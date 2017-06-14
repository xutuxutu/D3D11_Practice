#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <iostream>
#include "GameTimer.h"

class D3DApp
{
protected:
	HINSTANCE mhAppInst;	//���� ���α׷� �ν��Ͻ� �ڵ�
	HWND mhMainWnd;			//�� â �ڵ�
	bool mAppPaused;		//���� ���α׷� �Ͻ����� ����
	bool mMinmized;			//���� ���α׷� �ּ�ȭ ����
	bool mMaxmized;			//���� ���α׷� �ִ�ȭ ����
	bool mResizing;			//����� ũ�� ������ �׵θ��� �����ִ� �����ΰ�?
	UINT m4xMsaaQuality;		//4xMSAA ǰ�� ����

	//��� �ð��� ���� ��ü �ð��� �����ϴµ��� ���δ�.
	GameTimer mTimer;

	//DX�� ����
	ID3D11Device* md3dDevice;						//D3D11 ��ġ
	ID3D11DeviceContext* md3dImmediateContext;		//
	IDXGISwapChain* mSwapChain;						//������ ��ȯ�� ���� ��ȯ �罽
	ID3D11Texture2D* mDepthStencilBuffer;			//����-���ٽ� ���۸� ���� 2D �ؽ���
	ID3D11RenderTargetView* mRenderTargetView;		//
	ID3D11DepthStencilView* mDepthStencilView;		//����-���ٽ� ��
	D3D11_VIEWPORT mScreenViewport;

	//���� �������� D3DApp �����ڿ��� �⺻����� �ʱ�ȭ�ȴ�. �׷��� �ʿ��ϴٸ� �Ļ� Ŭ������ �����ڿ��� �ٸ� ����� �ʱ�ȭ�ص� �ȴ�.
	std::wstring mMainWndCaption;					//â�� ����. D3DApp�� �⺻���� "D3D11 Application"�̴�.
	D3D_DRIVER_TYPE md3dDriverType;					//������ ����(�ϵ���� ��ġ �Ǵ� ǥ�� ��ġ��) D3DApp�� �⺻ ���� D3D_DRIVER_TYPE_HARDWARE�̴�.

	//â�� Ŭ���̾�Ʈ ������ �ʱ�ũ��. �⺻ ���� 800x600
	//�׷��� ���� â�� ũ�Ⱑ �ٲ�� ���� Ŭ���̾�Ʈ ������ ũ�⿡ �°� �������� ���ŵ�.
	int mClientWidth;
	int mClientHeight;

	bool mEnable4xMSAA;								//4xMSAA ��� ����.
public:
	D3DApp(HINSTANCE hInstance);					//������ �ڷ� ������� �⺻������ �ʱ�ȭ
	virtual ~D3DApp();								//�Ҹ���. D3DApp Ŭ������ ȹ���� COM �������̽����� ����.

	HINSTANCE AppInst() const;						//���� ���α׷� �ν��Ͻ� �ڵ��� ���纻 ��ȯ
	HWND MainWnd() const;							//�� â�� �ڵ��� ���纻�� ��ȯ
	float AspectRatio() const;						//�ĸ� ������ ��Ⱦ�� ��ȯ.

	int Run();										//���� ���α׷� �޼��� ������ ���� �޼���. 
													//Windows �޽����� ���� ���� ������ ������ ������ ó���� �� �ֵ��� �ϱ� ���� PeekMessage�Լ��� ���.

	//�����ӿ�ũ �޼����. �Ļ� Ŭ���̾�Ʈ Ŭ������ �� �޼������ �ڽ��� �䱸�� �°� ������
	virtual void Init();							//���α׷� ������ �ʱ�ȭ �ڵ� ����.
	virtual void OnResize();						//WM_SIZE �޽����� �߻����� �� MsgProc���� ȣ��
	virtual void UpdateScene(float dt) = 0;			//�� ������ ȣ��. ���� ���α׷��� �����ϴµ��� �ʿ��� �ڵ� ����.
	virtual void DrawScene() = 0;					//�� ������ ȣ��. �ĸ� ���ۿ� ������ �׸������� ������ ��ɵ��� ����.
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);		
													//���� ���α׷� �� â�� �޽��� ó������� �����ϴ� �Լ�.
	//���콺 �Է� ó���� ���� ���ǿ� ���� �޼����
	virtual void OnMouseDown(WPARAM btnState, int x, int y) {}
	virtual void OnMouseUp(WPARAM btnState, int x, int y) {}
	virtual void OnMouseMove(WPARAM btnState, int x, int y) {}

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameState();						//��� �ʴ� ������ ���� ��� �ʴ� �и��ʸ� ����Ѵ�.
};

