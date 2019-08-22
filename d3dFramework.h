#pragma once

#include "d3d9.h"

bool d3d9Initial(
	HINSTANCE hInstance,		// Ӧ�ó���ľ��
	WNDPROC WndProc	,			// ���ڹ��̺���
	int width,					// ��Ļ���
	int hegiht,					// ��Ļ�߶�
	bool fullScreen,			// �Ƿ�ȫ����ʾ
	D3DDEVTYPE deviceType,		// �豸����
	IDirect3DDevice9 ** device	// ָ��IDirect3DDevice9��ָ���ָ��
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