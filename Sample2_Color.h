#pragma once

#ifndef SAMPLE2 //���û�ж�������� 
#define SAMPLE2 //���������  

namespace Sample2 {

	struct ColorVertex{
		float x, y, z;
		D3DCOLOR color;	// ����Ϊ8-bit��color����
		// �����ʽ
		static const DWORD FVF;

		ColorVertex(){}
		ColorVertex(float _x,float _y,float _z,D3DCOLOR _color) {
			x = _x;
			y = _y;
			z = _z;
			color = _color;
		}
	};

	void init(IDirect3DDevice9* Device, int Width, int Height);

	void render(IDirect3DDevice9* Device,float deltaTime);

	void onDestory();
}

#endif
