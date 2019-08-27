#pragma once
namespace Sample5 {

	struct Vertex {
		float _x, _y, _z;
		float _nx, _ny, _nz;
		float _u, _v;

		Vertex() {}
		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) {
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