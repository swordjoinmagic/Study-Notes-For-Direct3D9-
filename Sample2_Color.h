#pragma once

#ifndef SAMPLE2 //如果没有定义这个宏 
#define SAMPLE2 //定义这个宏  

namespace Sample2 {

	struct ColorVertex{
		float x, y, z;
		D3DCOLOR color;	// 精度为8-bit的color类型
		// 灵活顶点格式
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
