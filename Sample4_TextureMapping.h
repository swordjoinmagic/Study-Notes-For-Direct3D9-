#pragma once

#ifndef SAMPLE4 //如果没有定义这个宏 
#define SAMPLE4 //定义这个宏  

namespace Sample4 {

	const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255,255,255));
	const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0,0,0));
	const D3DXCOLOR RED(D3DCOLOR_XRGB(255,0,0));



	struct Vertex{
		float _x, _y, _z;
		float _nx, _ny, _nz;
		float _u, _v;

		Vertex() {}
		Vertex(float x,float y,float z,float nx,float ny,float nz,float u,float v) {
			_x = x; _y = y; _z = z;
			_nx = nx; _ny = ny; _nz = nz;
			_u = u; _v = v;
		}

		static const DWORD FVF;
	};

	void init(IDirect3DDevice9* Device, int Width, int Height);
	void render(IDirect3DDevice9* Device, float deltaTime);

	void onDestory();

}

#endif