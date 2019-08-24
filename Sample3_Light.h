#pragma once

#ifndef SAMPLE3 //如果没有定义这个宏 
#define SAMPLE3 //定义这个宏  

namespace Sample3 {

	struct Vertex{
		float x, y, z;
		float _nx, _ny, _nz;
		static const DWORD FVF;
		Vertex() {}

		Vertex(float _x,float _y,float _z,float nx,float ny,float nz) {
			x = _x; y = _y; z = _z;
			_nx = nx; _ny = ny; _nz = nz;
		}
	};

	void init(IDirect3DDevice9* Device, int Width, int Height);
	void render(IDirect3DDevice9* Device, float deltaTime);

	void onDestory();

}

#endif