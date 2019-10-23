#include "stdafx.h"
#include "Sample6_StencilTest.h"


void Sample6::init() {
	// �����豭Mesh
	D3DXCreateTeapot(Device, &Teapot, 0);

	// ���þ��涥�㻺��
	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&quad,
		0
	);

	// �������涥�㻺��
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

	// ����ͶӰ����
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


	//// ����ģ����Բ���

	//// ����ģ�����
	//Device->SetRenderState(D3DRS_STENCILENABLE, true);
	//// ����ģ�����Ϊ����ͨ��
	//Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	//// ����ģ��ο�ֵ
	//Device->SetRenderState(D3DRS_STENCILREF, 0x1);
	//// ����ģ������
	//Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	//// ���õ���Ȳ���ʧ��ʱ,��θ���ģ���ֵ(����Ϊ���ֲ���)
	//Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	//// ����ģ�����ʧ��ʱ,��θ���ģ���ֵ
	//Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	//// ����ģ�����ͨ��ʱ,��ģ��ο�ֵ���浱ǰģ��ֵ
	//Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);


	//// ��һ��,��������Ƶ�ģ�建����(��,������λ�õ�ģ��ֵ����Ϊ1)

	//// ȡ����Ȳ���,������BlendΪ0,1
	//Device->SetRenderState(D3DRS_ZWRITEENABLE,false);
	//Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ZERO);
	//Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	//// ���ƾ��浽ģ�建����
	
}

void Sample6::destory() {
	Device->Release();
}