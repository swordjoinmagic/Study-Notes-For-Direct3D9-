#pragma once
#include "stdafx.h"
#include "d3d9.h"

#ifndef SAMPLE1 //如果没有定义这个宏 
#define SAMPLE1 //定义这个宏  
// 初始化
namespace Sample1 {

	// 定义顶点结构和该结构的灵活顶点格式
	struct Vertex {
		float _x, _y, _z;
		static const DWORD FVF;

		Vertex() {}
		Vertex(float x, float y, float z) {
			_x = x;
			_y = y;
			_z = z;
		}
	};

	// 样例的初始化方法,一般用于初始化顶点和索引缓冲
	void init(IDirect3DDevice9* Device,int Width,int Height);
	
	// 样例的渲染方法,一般用于绘制图形
	void Render(IDirect3DDevice9* Device, float timeDelta);

	// 样例的结束方法一般用于结束这个样例
	void onDestory();
}

#endif 
