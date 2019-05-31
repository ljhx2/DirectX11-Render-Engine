#pragma once

#ifndef _GEOMETRY_GENERATOR_H_
#define _GEOMETRY_GENERATOR_H_


#include "Mesh.h"
#include "VertexType.h"

class CGeometryGenerator
{
public:
	//static CMesh*			CreateBox();		//Vertex_PC
	static CMesh*			CreateBoxPNT();		//Vertex_PNT
	static CMesh*			CreateBox();		//Vertex_PTNTan
	static CMesh*			CreateSphere();
	static CMesh*			CreateCylinder();
	static CMesh*			CreatePlane();


private:
	static void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, std::vector<Vertex_PTNTan>& vertices, std::vector<UINT>& indices);
	static void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, UINT sliceCount, UINT stackCount, std::vector<Vertex_PTNTan>& vertices, std::vector<UINT>& indices);

	
public:
	CGeometryGenerator();
	~CGeometryGenerator();
};


#endif // !_GEOMETRY_GENERATOR_H_
