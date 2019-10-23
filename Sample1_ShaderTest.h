#pragma once
#ifndef SAMPLE1
#define SAMPLE1

#include "stdafx.h"

class Sample1 {
private:
	UINT Width, Height;
	IDirect3DDevice9* Device;

	IDirect3DPixelShader9* fragmentShader;
	ID3DXConstantTable* fragmentShaderConstTable;
	IDirect3DVertexShader9* vertexShader;
	ID3DXConstantTable* vertexShaderConstTable;
	ID3DXMesh* teapot;

	D3DXHANDLE modelMatrixHandle;
	D3DXHANDLE viewMatrixHandle;
	D3DXHANDLE projectionMatrixHandle;
	D3DXHANDLE MainTexHandle;

	IDirect3DTexture9* MainTex;
	D3DXCONSTANT_DESC MainTexDesc;

public:
	Sample1(IDirect3DDevice9* device,UINT width,UINT height):Device(device),Width(width),Height(height) {}

	void init();
	void render(float deltaTime);
	void destory();
};

#endif
