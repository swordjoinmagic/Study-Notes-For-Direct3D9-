#include "stdafx.h"
#include "Sample2_Color.h"

// 模型-世界变换矩阵
D3DXMATRIX World;

// 三角形的顶点序列
IDirect3DVertexBuffer9 *Triangle = 0;

const DWORD Sample2::ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

void Sample2::init(IDirect3DDevice9* device, int Width, int Height) {	
	// 创建顶点缓冲
	device->CreateVertexBuffer(
		3 * sizeof(Sample2::ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&Triangle,
		0
	);

	// 填充顶点缓冲
	ColorVertex *v;

	Triangle->Lock(0,0,(void**)&v,0);

	v[0] = ColorVertex(-1.0f,0.0f,2.0f,D3DCOLOR_XRGB(255,0,0));
	v[1] = ColorVertex(0.0f, 1.0f, 2.0f, D3DCOLOR_XRGB(0, 255, 0));
	v[2] = ColorVertex(1.0f, 0.0f, 2.0f, D3DCOLOR_XRGB(0, 0, 255));

	Triangle->Unlock();

	// 设置投影矩阵
	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)Width/(float)Height,
		1.0f,
		1000.0f
	);
	device->SetTransform(D3DTS_PROJECTION,&proj);

	device->SetRenderState(D3DRS_LIGHTING,false);
}

void Sample2::render(IDirect3DDevice9* Device, float deltaTime) {
	Device->SetFVF(ColorVertex::FVF);
	// 将顶点缓冲输入进流中
	Device->SetStreamSource(0,Triangle,0,sizeof(ColorVertex));

	// 设置平移矩阵
	D3DXMatrixTranslation(&World,-1.25f,0.0f,0.0f);
	Device->SetTransform(D3DTS_WORLD,&World);

	// 设置渲染状态
	Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_FLAT);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST,0,1);

	// 另一个平移矩阵
	D3DXMatrixTranslation(&World,1.25f,0.0f,0.0f);
	Device->SetTransform(D3DTS_WORLD, &World);

	// 设置为高洛德着色
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

}

void Sample2::onDestory() {
	Triangle->Release();
}