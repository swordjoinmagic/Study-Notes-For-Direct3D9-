#pragma once
#include "stdafx.h"
#include "d3d9.h"

#ifndef SAMPLE1 //���û�ж�������� 
#define SAMPLE1 //���������  
// ��ʼ��
namespace Sample1 {

	// ���嶥��ṹ�͸ýṹ�������ʽ
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

	// �����ĳ�ʼ������,һ�����ڳ�ʼ���������������
	void init(IDirect3DDevice9* Device,int Width,int Height);
	
	// ��������Ⱦ����,һ�����ڻ���ͼ��
	void Render(IDirect3DDevice9* Device, float timeDelta);

	// �����Ľ�������һ�����ڽ����������
	void onDestory();
}

#endif 
