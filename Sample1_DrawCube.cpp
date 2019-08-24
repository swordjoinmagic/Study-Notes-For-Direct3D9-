#include "stdafx.h"
#include "Sample1_DrawCube.h"

static float y = 0.0f;
// 初始化立方体的顶点和索引缓冲
IDirect3DVertexBuffer9 *VB = 0;
IDirect3DIndexBuffer9 *IB = 0;
const DWORD Sample1::Vertex::FVF = D3DFVF_XYZ;

void Sample1::init(IDirect3DDevice9* Device, int Width, int Height) {

	// 创建顶点缓冲和索引缓冲
	Device->CreateVertexBuffer(
		8 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0
	);

	Device->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0
	);

	// 填充顶点数据
	Vertex *verteics;
	VB->Lock(0, 0, (void**)&verteics, 0);

	verteics[0] = Vertex(-1.0f, -1.0f, -1.0f);
	verteics[1] = Vertex(-1.0f, 1.0f, -1.0f);
	verteics[2] = Vertex(1.0f, 1.0f, -1.0f);
	verteics[3] = Vertex(1.0f, -1.0f, -1.0f);
	verteics[4] = Vertex(-1.0f, -1.0f, 1.0f);
	verteics[5] = Vertex(-1.0f, 1.0f, 1.0f);
	verteics[6] = Vertex(1.0f, 1.0f, 1.0f);
	verteics[7] = Vertex(1.0f, -1.0f, 1.0f);

	VB->Unlock();

	WORD *indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	// frontSide
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// backSide
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// leftSide
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// rightSide
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	IB->Unlock();

	D3DXVECTOR3 position(0.0f, 0.0f, -5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	Device->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)Width / (float)Height,
		1.0f,
		1000.0f
	);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void Sample1::Render(IDirect3DDevice9* Device, float deltaTime) {
	D3DXMATRIX Rx, Ry;
	D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);

	D3DXMatrixRotationY(&Ry, y);
	y += 3.14f / 4.0f * deltaTime;
	if (y >= 6.28f) y = 0.0f;

	D3DXMATRIX p = Rx * Ry;
	Device->SetTransform(D3DTS_WORLD, &p);

	Device->SetStreamSource(0, VB, 0, sizeof(Vertex));
	Device->SetIndices(IB);
	Device->SetFVF(Vertex::FVF);

	// draw cube
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

void Sample1::onDestory() {
	// 释放顶点缓冲和索引缓冲
	IB->Release();
	VB->Release();
}