#pragma once

#include "d3d9.h"

bool d3d9Initial(
	HINSTANCE hInstance,		// 应用程序的句柄
	WNDPROC WndProc	,			// 窗口过程函数
	int width,					// 屏幕宽度
	int hegiht,					// 屏幕高度
	bool fullScreen,			// 是否全屏显示
	D3DDEVTYPE deviceType,		// 设备类型
	IDirect3DDevice9 ** device	// 指向IDirect3DDevice9的指针的指针
);

HWND d3d9CreateWindow(
	HINSTANCE hInstance,
	WNDPROC WndProc,
	int width,
	int height,
	bool fullScrenn
);

int d3d9CheckHardwareVP(
	IDirect3D9* d3d9,
	D3DDEVTYPE deviceType
);

D3DPRESENT_PARAMETERS d3d9CreatePP(
	HWND hwnd,
	int width,
	int hegiht,
	bool fullScreen
);

bool d3d9CreateDevice(
	IDirect3D9* d3d9,
	D3DDEVTYPE deviceType,
	HWND hwnd,
	int vp,
	D3DPRESENT_PARAMETERS d3dpp,
	IDirect3DDevice9 **device
);

int d3d9MessageLoop(
	bool (* p_Display)( float time, IDirect3DDevice9 *Device),
	IDirect3DDevice9* Device
);