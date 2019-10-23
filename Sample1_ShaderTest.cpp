#include "stdafx.h"
#include "Sample1_ShaderTest.h"

void Sample1::init() {

	// 创建茶杯mesh
	//D3DXCreateTeapot(Device, &teapot, 0);
	D3DXCreateBox(Device,1,1,1,&teapot,0);

	// 创建纹理
	D3DXCreateTextureFromFileA(Device,"Image/Checkerboard.png",&MainTex);

	HRESULT hr = 0;
	ID3DXBuffer* vertexShaderBuffer = 0;
	ID3DXBuffer* errorBuffer = 0;

	hr = D3DXCompileShaderFromFileA("Shader/Sample1 ShaderTest/v.hlsl", 0, 0, "main", "vs_2_0", D3DXSHADER_DEBUG, &vertexShaderBuffer, &errorBuffer, &vertexShaderConstTable);

	// 检查编译错误
	if (errorBuffer) {
		MessageBoxA(0, (char*)errorBuffer->GetBufferPointer(), 0, 0);
		errorBuffer->Release();
	}
	if (FAILED(hr)) {
		MessageBoxA(0, "编译顶点着色器错误~", 0, 0);
		return;
	}

	// 创建顶点着色器程序
	hr = Device->CreateVertexShader((DWORD*)vertexShaderBuffer->GetBufferPointer(), &vertexShader);
	if (FAILED(hr)) {
		MessageBoxA(0,"创建顶点着色器程序错误!",0,0);
		return;
	}

	vertexShaderBuffer->Release();

	// 获得顶点着色器各个uniform变量的指针
	modelMatrixHandle = vertexShaderConstTable->GetConstantByName(0,"model");
	viewMatrixHandle = vertexShaderConstTable->GetConstantByName(0,"view");
	projectionMatrixHandle = vertexShaderConstTable->GetConstantByName(0,"projection");

	// 编译片元着色器
	ID3DXBuffer* fragShaderBuffer = 0;
	hr = D3DXCompileShaderFromFile(L"Shader/Sample1 ShaderTest/f.hlsl",0,0,"main","ps_2_0",D3DXSHADER_DEBUG,&fragShaderBuffer,&errorBuffer,&fragmentShaderConstTable);

	// 检验片元着色器编译错误
	if (errorBuffer) {
		MessageBoxA(0,(char*)errorBuffer->GetBufferPointer(),0,0);
		errorBuffer->Release();
	}
	if (FAILED(hr)) {
		MessageBoxA(0,"编译片元着色器错误!",0,0);
		return;
	}
	// 创建片元着色器
	hr = Device->CreatePixelShader((DWORD*)fragShaderBuffer->GetBufferPointer(),&fragmentShader);
	if (FAILED(hr)) {
		MessageBoxA(0,"创建片元着色器错误!",0,0);
	}

	UINT count = 0;
	MainTexHandle = fragmentShaderConstTable->GetConstantByName(0,"MainTex");
	fragmentShaderConstTable->GetConstantDesc(MainTexHandle,&MainTexDesc,&count);
	
	Device->SetTexture(MainTexDesc.RegisterIndex,MainTex);
	// 设置纹理过滤模式
	Device->SetSamplerState(MainTexDesc.RegisterIndex,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	Device->SetSamplerState(MainTexDesc.RegisterIndex,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
}

float angle = 0;
void Sample1::render(float deltaTime) {

	angle = angle + 1.0f * deltaTime;

	// 设置mvp矩阵
	vector3 pos(0,0,0);
	vector3 target(0,0,0);
	vector3 up(0,1.0f,0);
	vector3 cameraPos(0,0,-3);
	float fov = D3DX_PI / 2.0f;
	float Near = 0.1f;
	float Far = 10.0f;

	matrix4x4 model,view,projection;
	matrix4x4 translation, rotation;
	D3DXMatrixRotationY(&rotation, angle);
	D3DXMatrixTranslation(&translation,pos.x,pos.y,pos.z);
	model = rotation * translation;
	D3DXMatrixLookAtLH(&view,&cameraPos,&target,&up);
	D3DXMatrixPerspectiveFovLH(&projection,fov,(float)Width/(float)Height,Near,Far);

	// 设置mvp矩阵
	vertexShaderConstTable->SetMatrix(Device,modelMatrixHandle,&model);
	vertexShaderConstTable->SetMatrix(Device, viewMatrixHandle, &view);
	vertexShaderConstTable->SetMatrix(Device, projectionMatrixHandle, &projection);

	Device->SetVertexShader(vertexShader);
	Device->SetPixelShader(fragmentShader);

	teapot->DrawSubset(0);

	
}

void Sample1::destory() {
	Device->Release();
}