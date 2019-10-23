#include "stdafx.h"
#include "d3dFramework.h"
#include "resource.h"

/*
	用于初始化d3d9设备
*/
bool d3d9Initial(
	HINSTANCE hInstance,		// 应用程序的句柄
	WNDPROC WndProc,			// 窗口过程函数
	int width,					// 屏幕宽度
	int hegiht,					// 屏幕高度
	bool fullScreen,			// 是否全屏显示
	D3DDEVTYPE deviceType,		// 设备类型
	IDirect3DDevice9 ** device	// 指向IDirect3DDevice9的指针的指针
) {
	HWND hwnd = d3d9CreateWindow(hInstance,WndProc,width,hegiht,fullScreen);

	if (!hwnd) {
		MessageBoxA(0,"d3d9CreateWindow Failed",0,0);
		return false;
	}

	// 创建D3D9接口
	IDirect3D9* d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9) {
		MessageBoxA(0,"DIrect3DCreate9 failed",0,0);
		return false;
	}

	// 校验硬件设备是否支持顶点运算
	int vp = d3d9CheckHardwareVP(d3d9,deviceType);
	// 创建并填充d3dpp结构
	D3DPRESENT_PARAMETERS d3dpp = d3d9CreatePP(hwnd,width,hegiht,fullScreen);

	return d3d9CreateDevice(d3d9,deviceType,hwnd,vp,d3dpp,device);

}

// 创建窗口,并返回该窗口的句柄
HWND d3d9CreateWindow(
	HINSTANCE hInstance,
	WNDPROC WndProc,
	int width,
	int height,
	bool fullScrenn
) {
	// 设计窗口类
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

	// 注册窗口类
	if (!RegisterClass(&wc)) {
		MessageBoxA(0,"RegisterClass Failed",0,0);
		return 0;
	}

	// 创建窗口
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
	// 显示以及更新窗口
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

	// 返回以创建的窗口的句柄
	return hwnd;
}

/*
	校验硬件是否支持顶点运算(即硬件光照计算,应该指的是着色器这一块)
	返回支持的类型,支持即返回D3DCREATE_HARDWARE_VERTEXPROCESSING,
	不支持即返回D3DCREATE_SOFTWARE_VERTEXPROCESSING
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
	创建d3d9设备的参数
*/
D3DPRESENT_PARAMETERS d3d9CreatePP(
	HWND hwnd,
	int width,
	int height,
	bool fullScreen
) {
	D3DPRESENT_PARAMETERS d3dpp;

	// 后备缓冲区的宽度
	d3dpp.BackBufferWidth = width;
	// 后备缓冲区中的高度
	d3dpp.BackBufferHeight = height;
	// 后备缓冲区的数量,通常为1
	d3dpp.BackBufferCount = 1;
	// 后备缓冲区的格式,这里设置为ARGB,都为8位字节
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	// 后台缓冲使用的多重采样类型
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	// 多重采样质量水平
	d3dpp.MultiSampleQuality = 0;
	// 指定了交换链中缓存的页面置换方式
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// 与设备相关的窗口句柄
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = !fullScreen;
	// 表示d3d自动应用深度/模板缓冲
	d3dpp.EnableAutoDepthStencil = true;
	// 24位精度的深度缓冲
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	return d3dpp;
}

/*
	用于创建IDirect3DDevice9
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
		初始化错误检验
	*/
	if (hr == D3DERR_INVALIDCALL) {
		MessageBoxA(0,"方法调用无效. 比如方法的一个参数是无效值.",0,0);
	}
	else if(hr == D3DERR_NOTAVAILABLE)
	{
		MessageBoxA(0, "设备不支持检验技术(queried technique).", 0, 0);		
	}
	else if( hr == D3DERR_OUTOFVIDEOMEMORY)
	{
		MessageBoxA(0, "Direct3D 没有足够显存来完成操作.", 0, 0);

	}

	// 如果创建失败,尝试减少深度缓冲区精度
	if (FAILED(hr)) {
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		hr = d3d9->CreateDevice(D3DADAPTER_DEFAULT, deviceType, hwnd, vp, &d3dpp, device);
		if (FAILED(hr)) {
			MessageBoxA(0,"d3d9CreateDevice Failed",0,0);
			d3d9->Release();
			return false;
		}
	}

	// 释放IDirect3D9对象(创建完IDirect3DDevice9对象就不需要这个对象了)
	d3d9->Release();
	return true;
}

/*
	Direct3D的消息循环框架
*/
int d3d9MessageLoop(
	bool(*p_Display)(float time, IDirect3DDevice9 *Device),
	IDirect3DDevice9* Device
) {
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));
	// 最近一次进行游戏更新的时间	
	static float lastUpdateTime = (float)(timeGetTime());
	while (msg.message != WM_QUIT){
		// 如果消息队列中有消息那么就处理消息
		if (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
			// 翻译消息,主要是翻译消息中的按键信息(鼠标/键盘)
			TranslateMessage(&msg);
			// 分发消息,将消息交给窗口过程函数处理(即WndProc函数)
			DispatchMessage(&msg);
		}else{
			// 如果没有消息需要处理,就执行游戏内部循环
			
			// 计算帧率
			float nowTime = (float)timeGetTime();	// 当前时间,单位ms
			// 两次更新之间的间隔时间(以秒计算)
			float intervalTime = (nowTime - lastUpdateTime) / 1000;
			p_Display(intervalTime,Device);
			lastUpdateTime = nowTime;
		}
	}

	return true;
}