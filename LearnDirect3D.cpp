//LearnDirect3D.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "LearnDirect3D.h"
#include "d3dFramework.h"
#include "Sample6_StencilTest.h"
#include "Sample1_ShaderTest.h"

bool Update(float deltaTime, IDirect3DDevice9 *Device);
void Construct();
void Destruct();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

const int Width = 800;
const int Height = 600;

// IDirect3DDevice9设备
IDirect3DDevice9* Device = NULL;

Sample1* sample;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow){

	if (!d3d9Initial(hInstance,(WNDPROC)WndProc,Width,Height,false,D3DDEVTYPE_HAL,&Device)) {
		MessageBoxA(0,"d3dInitial Failed",0,0);
		return 0;
	}

	// 创建模型
	Construct();

	// 消息循环&&游戏循环
	d3d9MessageLoop(Update, Device);

	// 模型销毁
	Destruct();

	Device->Release();

	return 0;
}


// 游戏循环函数
bool Update(float deltaTime, IDirect3DDevice9 *Device) {
	if (Device) {
		// 每次开始渲染之前,清除颜色缓冲区,深度缓冲区和模板缓冲
		Device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,D3DCOLOR_XRGB(0, 0, 0),1.0f,0);

		Device->BeginScene();

		//==================
		// 绘制内容写于此处
		//****************
		sample->render(deltaTime);

		Device->EndScene();

		// 交换双缓冲(即把后台缓冲提交到表面缓冲这)
		Device->Present(0,0,0,0);
	}

	return true;
}

// 模型创建
void Construct() {
	sample = new Sample1(Device,Width,Height);
	sample->init();
}


// 销毁模型
void Destruct() {
	sample->destory();
	delete sample;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
