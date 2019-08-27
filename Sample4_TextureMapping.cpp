#include "stdafx.h"
#include "Sample4_TextureMapping.h"

// �ķ��嶥�㻺��
IDirect3DVertexBuffer9 *Quad = 0;
// ����
IDirect3DTexture9 *Tex = 0;

const DWORD Sample4::Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

void Sample4::init(IDirect3DDevice9* Device, int Width, int Height) {
	 // �������㻺��
	Device->CreateVertexBuffer(
		6*sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&Quad,
		0
	);

	// ��䶥�㻺��
	Vertex *v;
	Quad->Lock(0,0,(void**)&v,0);

	//			    x     y     z    nx   ny    nz    u    v
	v[0] = Vertex(-1.0f,-1.0f,1.25f,0.0f,0.0f,-1.0f,0.0f,3.0f);
	v[1] = Vertex(-1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
	v[3] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	v[4] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
	v[5] = Vertex(1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f);

	Quad->Unlock();

	// ���ļ��д�������
	D3DXCreateTextureFromFileA(
		Device,
		"D:\\CPPInstance\\LearnDirect3D\\LearnDirect3D\\Image\\29126173.bmp",
		&Tex
	);

	Device->SetTexture(0,Tex);

	// �����������ģʽ,��Ϊ˫���Բ���
	Device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);	// ����Ŵ�Ĺ���ģʽ
	Device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);	// ������С�Ĺ���ģʽ

	// �����������ģʽ
	Device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
	Device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);

	// �趨ʹ�õ�mipmap��ʽ
	Device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_POINT);		

	Device->SetRenderState(D3DRS_LIGHTING,false);

	// ����ͶӰ����
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)Width / (float)Height,
		1.0f,
		1000.0f
	);
	Device->SetTransform(D3DTS_PROJECTION,&proj);
	
}

void Sample4::render(IDirect3DDevice9* Device, float deltaTime) {
	// �����㻺�����뵽�Դ�
	Device->SetStreamSource(0,Quad,0,sizeof(Sample4::Vertex));
	Device->SetFVF(Sample4::Vertex::FVF);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
}

void Sample4::onDestory() {
	Quad->Release();
}