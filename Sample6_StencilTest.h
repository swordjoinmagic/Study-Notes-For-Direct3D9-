#pragma once

#include <d3d9.h>

class Sample6 {
private:
	IDirect3DVertexBuffer9 *quad;	// 用于混合的背景
	ID3DXMesh *Teapot = 0;
	IDirect3DDevice9* Device;
	int Width, Height;
public:
	Sample6(IDirect3DDevice9* device,int width,int height) : Device(device),Width(width),Height(height) {}
	void init();
	void render(float deltTime);
	void destory();

	struct Vertex {
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;;
		float _x, _y, _z;
		float _nx, _ny, _nz;
		D3DCOLOR color;
		Vertex() {}
		Vertex(float x, float y, float z, float nx, float ny, float nz,byte r, byte g, byte b)
			: _x(x),_y(y),_z(z),_nx(nx),_ny(ny),_nz(nz){
			color = D3DCOLOR_XRGB(r,g,b);
		}
	} vertex;
	
};