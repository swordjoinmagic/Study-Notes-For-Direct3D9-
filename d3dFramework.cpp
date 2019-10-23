#include "stdafx.h"
#include "d3dFramework.h"
#include "resource.h"

/*
	���ڳ�ʼ��d3d9�豸
*/
bool d3d9Initial(
	HINSTANCE hInstance,		// Ӧ�ó���ľ��
	WNDPROC WndProc,			// ���ڹ��̺���
	int width,					// ��Ļ���
	int hegiht,					// ��Ļ�߶�
	bool fullScreen,			// �Ƿ�ȫ����ʾ
	D3DDEVTYPE deviceType,		// �豸����
	IDirect3DDevice9 ** device	// ָ��IDirect3DDevice9��ָ���ָ��
) {
	HWND hwnd = d3d9CreateWindow(hInstance,WndProc,width,hegiht,fullScreen);

	if (!hwnd) {
		MessageBoxA(0,"d3d9CreateWindow Failed",0,0);
		return false;
	}

	// ����D3D9�ӿ�
	IDirect3D9* d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9) {
		MessageBoxA(0,"DIrect3DCreate9 failed",0,0);
		return false;
	}

	// У��Ӳ���豸�Ƿ�֧�ֶ�������
	int vp = d3d9CheckHardwareVP(d3d9,deviceType);
	// ���������d3dpp�ṹ
	D3DPRESENT_PARAMETERS d3dpp = d3d9CreatePP(hwnd,width,hegiht,fullScreen);

	return d3d9CreateDevice(d3d9,deviceType,hwnd,vp,d3dpp,device);

}

// ��������,�����ظô��ڵľ��
HWND d3d9CreateWindow(
	HINSTANCE hInstance,
	WNDPROC WndProc,
	int width,
	int height,
	bool fullScrenn
) {
	// ��ƴ�����
	WNDCLASS wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIconW(0,IDI_APPLICATION);
	wc.hCursor = LoadCursorW(0,IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = TEXT("d3dWindow");

	// ע�ᴰ����
	if (!RegisterClass(&wc)) {
		MessageBoxA(0,"RegisterClass Failed",0,0);
		return 0;
	}

	// ��������
	HWND hwnd = CreateWindow(
		TEXT("d3dWindow"),
		TEXT("d3dProject"),
		WS_EX_TOPMOST|WS_OVERLAPPEDWINDOW,
		0,
		0,
		width,
		height,
		0,0,
		hInstance,
		0
	);

	if (!hwnd) {
		MessageBoxA(0,"CreateWindows Failed",0,0);
		return 0;
	}
	// ��ʾ�Լ����´���
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	// �����Դ����Ĵ��ڵľ��
	return hwnd;
}

/*
	У��Ӳ���Ƿ�֧�ֶ�������(��Ӳ�����ռ���,Ӧ��ָ������ɫ����һ��)
	����֧�ֵ�����,֧�ּ�����D3DCREATE_HARDWARE_VERTEXPROCESSING,
	��֧�ּ�����D3DCREATE_SOFTWARE_VERTEXPROCESSING
*/
int d3d9CheckHardwareVP(IDirect3D9* d3d9,D3DDEVTYPE deviceType) {
	int vp = 0;
	D3DCAPS9 caps;
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT,deviceType,&caps);
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}else{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	return vp;
}

/*
	����d3d9�豸�Ĳ���
*/
D3DPRESENT_PARAMETERS d3d9CreatePP(
	HWND hwnd,
	int width,
	int height,
	bool fullScreen
) {
	D3DPRESENT_PARAMETERS d3dpp;

	// �󱸻������Ŀ��
	d3dpp.BackBufferWidth = width;
	// �󱸻������еĸ߶�
	d3dpp.BackBufferHeight = height;
	// �󱸻�����������,ͨ��Ϊ1
	d3dpp.BackBufferCount = 1;
	// �󱸻������ĸ�ʽ,��������ΪARGB,��Ϊ8λ�ֽ�
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	// ��̨����ʹ�õĶ��ز�������
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	// ���ز�������ˮƽ
	d3dpp.MultiSampleQuality = 0;
	// ָ���˽������л����ҳ���û���ʽ
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// ���豸��صĴ��ھ��
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = !fullScreen;
	// ��ʾd3d�Զ�Ӧ�����/ģ�建��
	d3dpp.EnableAutoDepthStencil = true;
	// 24λ���ȵ���Ȼ���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return d3dpp;
}

/*
	���ڴ���IDirect3DDevice9
*/
bool d3d9CreateDevice(
	IDirect3D9* d3d9,
	D3DDEVTYPE deviceType,
	HWND hwnd,
	int vp,
	D3DPRESENT_PARAMETERS d3dpp,
	IDirect3DDevice9 **device
) {
	HRESULT hr = 0;
	hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT,deviceType,hwnd,vp,&d3dpp,device);

	/*
		��ʼ���������
	*/
	if (hr == D3DERR_INVALIDCALL) {
		MessageBoxA(0,"����������Ч. ���緽����һ����������Чֵ.",0,0);
	}
	else if(hr == D3DERR_NOTAVAILABLE)
	{
		MessageBoxA(0, "�豸��֧�ּ��鼼��(queried technique).", 0, 0);		
	}
	else if( hr == D3DERR_OUTOFVIDEOMEMORY)
	{
		MessageBoxA(0, "Direct3D û���㹻�Դ�����ɲ���.", 0, 0);

	}

	// �������ʧ��,���Լ�����Ȼ���������
	if (FAILED(hr)) {
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);
		if (FAILED(hr)) {
			MessageBoxA(0,"d3d9CreateDevice Failed",0,0);
			d3d9->Release();
			return false;
		}
	}

	// �ͷ�IDirect3D9����(������IDirect3DDevice9����Ͳ���Ҫ���������)
	d3d9->Release();
	return true;
}

/*
	Direct3D����Ϣѭ�����
*/
int d3d9MessageLoop(
	bool(*p_Display)(float time, IDirect3DDevice9 *Device),
	IDirect3DDevice9* Device
) {
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));
	// ���һ�ν�����Ϸ���µ�ʱ��	
	static float lastUpdateTime = (float)(timeGetTime());
	while (msg.message != WM_QUIT){
		// �����Ϣ����������Ϣ��ô�ʹ�����Ϣ
		if (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			// ������Ϣ,��Ҫ�Ƿ�����Ϣ�еİ�����Ϣ(���/����)
			TranslateMessage(&msg);
			// �ַ���Ϣ,����Ϣ�������ڹ��̺�������(��WndProc����)
			DispatchMessage(&msg);
		}else{
			// ���û����Ϣ��Ҫ����,��ִ����Ϸ�ڲ�ѭ��
			
			// ����֡��
			float nowTime = (float)timeGetTime();	// ��ǰʱ��,��λms
			// ���θ���֮��ļ��ʱ��(�������)
			float intervalTime = (nowTime - lastUpdateTime) / 1000;
			p_Display(intervalTime,Device);
			lastUpdateTime = nowTime;
		}
	}

	return true;
}