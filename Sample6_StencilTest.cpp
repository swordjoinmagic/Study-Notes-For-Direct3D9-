#include "stdafx.h"
#include "Sample6_StencilTest.h"


void Sample6::init() {
	// 创建茶杯Mesh
	D3DXCreateTeapot(Device, &Teapot, 0);

	// 设置镜面顶点缓冲
	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&quad,
		0
	);

	// 创建镜面顶点缓冲
	Vertex *v;
	quad->Lock(0, 0, (void**)&v, 0);
	//			    x     y     z    nx   ny    nz   
	v[0] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f,1,1,1);
	v[1] = Vertex(-1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1, 1, 1);
	v[2] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1, 1, 1);
	v[3] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1, 1, 1);
	v[4] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1, 1, 1);
	v[5] = Vertex(1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 1, 1, 1);
	quad->Unlock();

	// 设置投影矩阵
	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)Width / (float)Height,
		1.0f,
		1000.0f
	);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	D3DXMATRIX view;
	D3DXMatrixLookAtLH(
		&view,
		&D3DXVECTOR3(0, 0, -5.0f),
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 1, 0)
	);
	Device->SetTransform(D3DTS_VIEW, &view);

}

void Sample6::render(float deltaTime) {

	Device->SetRenderState(D3DRS_SHADEMODE,D3DSHADE_GOURAUD);

	D3DXMATRIX w;
	D3DXMatrixScaling(&w, 3, 3, 3);
	Device->SetTransform(D3DTS_WORLD, &w);
	Device->SetFVF(Vertex::FVF);
	Device->SetStreamSource(0, quad, 0, sizeof(Vertex));
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);


	//// 设置模板测试参数

	//// 开启模板测试
	//Device->SetRenderState(D3DRS_STENCILENABLE, true);
	//// 设置模板测试为总是通过
	//Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	//// 设置模板参考值
	//Device->SetRenderState(D3DRS_STENCILREF, 0x1);
	//// 设置模板掩码
	//Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	//// 设置当深度测试失败时,如何更新模板的值(这里为保持不变)
	//Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	//// 设置模板测试失败时,如何更新模板的值
	//Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	//// 设置模板测试通过时,将模板参考值代替当前模板值
	//Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);


	//// 第一步,将镜面绘制到模板缓冲中(即,将镜面位置的模板值设置为1)

	//// 取消深度测试,并设置Blend为0,1
	//Device->SetRenderState(D3DRS_ZWRITEENABLE,false);
	//Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ZERO);
	//Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//// 绘制镜面到模板缓冲中
	
}

void Sample6::destory() {
	Device->Release();
}