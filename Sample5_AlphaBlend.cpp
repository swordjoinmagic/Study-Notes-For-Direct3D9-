#include "stdafx.h"
#include "Sample5_AlphaBlend.h"

const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));

D3DMATERIAL9 InitMtrlA(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p) {
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}

ID3DXMesh *Teapot = 0;
D3DMATERIAL9 TeapotMatrl;

IDirect3DVertexBuffer9 *backGroundQuad;	// ���ڻ�ϵı���
IDirect3DTexture9 *backgroundTex;
D3DMATERIAL9 backgroundMtrl;

const D3DMATERIAL9 WHITE_MATRL = InitMtrlA(WHITE,WHITE,WHITE,BLACK,8.0f);
const D3DMATERIAL9 RED_MATRL = InitMtrlA(RED,RED,RED,BLACK,8.0f);

const DWORD Sample5::Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

void Sample5::init(IDirect3DDevice9* Device, int Width, int Height) {

	// �����豭Mesh
	D3DXCreateTeapot(Device,&Teapot,0);

	// ��ʼ��teapot����
	TeapotMatrl = RED_MATRL;
	TeapotMatrl.Diffuse.a = 0.5f;

	// ��ʼ������quad
	backgroundMtrl = WHITE_MATRL;
	
	// ���ñ������㻺��
	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&backGroundQuad,
		0
	);

	// ��䶥�㻺��
	Vertex *v;
	backGroundQuad->Lock(0, 0, (void**)&v, 0);

	//			    x     y     z    nx   ny    nz    u    v
	v[0] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	v[1] = Vertex(-1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
	v[3] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	v[4] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
	v[5] = Vertex(1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f);

	backGroundQuad->Unlock();

	// ���ļ��д�������
	D3DXCreateTextureFromFileA(
		Device,
		"D:\\CPPInstance\\LearnDirect3D\\LearnDirect3D\\Image\\29126173.bmp",
		&backgroundTex
	);

	// ���ñ�������
	Device->SetTexture(0,backgroundTex);
	// �����������ģʽ,��Ϊ˫���Բ���
	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// ����Ŵ�Ĺ���ģʽ
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// ������С�Ĺ���ģʽ

	// �����������ģʽ
	Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	// �趨ʹ�õ�mipmap��ʽ
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// ����ƽ�й�
	D3DLIGHT9 dir;
	ZeroMemory(&dir, sizeof(dir));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = WHITE;
	dir.Specular = WHITE * 0.3f;
	dir.Ambient = WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(0, 0.0f, 1.0f);
	Device->SetLight(0, &dir);
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_LIGHTING, true);


	// ���ø߹ⷴ��
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

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

void Sample5::render(IDirect3DDevice9* Device, float deltaTime) {

	// ��������
	if (GetAsyncKeyState('A') & 0x8000f) {
		TeapotMatrl.Diffuse.a += 0.01f;
	}
	if (GetAsyncKeyState('S') & 0x8000f) {
		TeapotMatrl.Diffuse.a -= 0.01f;
	}

	// clamp���ʵ�Alpha
	if (TeapotMatrl.Diffuse.a > 1.0f) 
		TeapotMatrl.Diffuse.a = 1.0f;	
	if (TeapotMatrl.Diffuse.a < 0.0f)
		TeapotMatrl.Diffuse.a = 0.0f;

	// ���Ʊ���Quad
	D3DXMATRIX w;
	D3DXMatrixScaling(&w,3,3,3);
	Device->SetTransform(D3DTS_WORLD,&w);
	Device->SetFVF(Vertex::FVF);
	Device->SetStreamSource(0,backGroundQuad,0,sizeof(Vertex));
	Device->SetMaterial(&backgroundMtrl);
	Device->SetTexture(0,backgroundTex);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);

	// ���Ʋ豭
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE,true);

	D3DXMatrixScaling(&w,1.5f,1.5f,1.5f);
	Device->SetTransform(D3DTS_WORLD,&w);
	Device->SetMaterial(&TeapotMatrl);
	Device->SetTexture(0,0);
	Teapot->DrawSubset(0);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE,false);


}

void Sample5::onDestory() {
	Teapot->Release();
	backGroundQuad->Release();
}