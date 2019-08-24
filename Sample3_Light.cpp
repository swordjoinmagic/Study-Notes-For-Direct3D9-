#include "stdafx.h"
#include "Sample3_Light.h"

// ��׶�Ķ��㻺��
IDirect3DVertexBuffer9 *Pyramid = 0;

const DWORD Sample3::Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255,255,255));
const D3DXCOLOR BACK(D3DCOLOR_XRGB(0, 0, 0));

D3DMATERIAL9 InitMtrl(D3DXCOLOR a,D3DXCOLOR d,D3DXCOLOR s,D3DXCOLOR e,float p) {
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}


void Sample3::init(IDirect3DDevice9* Device, int Width, int Height) {
	// ���ù��պ���
	Device->SetRenderState(D3DRS_LIGHTING,true);

	// �������㻺��
	Device->CreateVertexBuffer(
		12 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&Pyramid,
		0
	);

	// ��䶥�㻺��
	Vertex *v;
	Pyramid->Lock(0,0,(void**)&v,0);

	// front
	v[0] = Vertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);
	v[1] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, -0.707f);
	v[2] = Vertex(1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);

	// left
	v[3] = Vertex(-1.0f, 0.0f, 1.0f, -0.707f, 0.707f, 0);
	v[4] = Vertex(0.0f, 1.0f, 0.0f, -0.707f, 0.707f, 0);
	v[5] = Vertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0);

	// right
	v[6] = Vertex(1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0);
	v[7] = Vertex(0.0f, 1.0f, 0.0f, 0.707f, 0.707f, 0);
	v[8] = Vertex(1.0f, 0.0f, 1.0f, 0.707f, 0.707f, 0);

	// back
	v[9] = Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	v[10] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, 0.707f);
	v[11] = Vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);

	Pyramid->Unlock();

	// �������
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = WHITE;
	mtrl.Diffuse = WHITE;
	mtrl.Specular = WHITE;
	mtrl.Emissive = BACK;
	mtrl.Power = 5.0f;

	// ���ò���
	Device->SetMaterial(&mtrl);

	// ����ƽ�й�
	D3DLIGHT9 dir;
	ZeroMemory(&dir,sizeof(dir));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = WHITE;
	dir.Specular = WHITE * 0.3f;
	dir.Ambient = WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(1.0f,0.0f,0.0f);
	Device->SetLight(0,&dir);
	Device->LightEnable(0,true);

	// ���ø߹ⷴ��
	Device->SetRenderState(D3DRS_NORMALIZENORMALS,true);
	Device->SetRenderState(D3DRS_SPECULARENABLE,true);

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

}

static float x = 0;

void Sample3::render(IDirect3DDevice9* Device, float deltaTime) {

	D3DXMATRIX modelMatrix;
	D3DXMatrixRotationX(&modelMatrix,x);
	x += deltaTime * D3DX_PI/4;
	if (x >= 6.28) x = 0;
	Device->SetTransform(D3DTS_WORLD,&modelMatrix);

	D3DXMATRIX view;
	D3DXMatrixTranslation(
		&view,
		0,0,2.0f
	);
	Device->SetTransform(D3DTS_VIEW,&view);

	Device->SetFVF(Vertex::FVF);
	// �����㻺�����������
	Device->SetStreamSource(0, Pyramid, 0, sizeof(Vertex));

	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void Sample3::onDestory() {
	Pyramid->Release();
}

