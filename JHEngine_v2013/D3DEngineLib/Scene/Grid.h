#pragma once

#ifndef _GRID_H_
#define _GRID_H_

#include "..\Resource\VertexType.h"
#include "..\Resource\Mesh.h"

class CScene;

class CGrid
{
public:
	void			Setup(float fGap, int nNumHalf);
	void			Render();

private:
	void			MakeVertices(float fGap, int nNumHalf);
	void			MakeEffect();
	void			MakeMesh();

public:
	CGrid(CScene* ownerScene);
	~CGrid();

private:
	bool							m_isDisable;
	CScene*							m_ownerScene;

	std::vector<Vertex_PC>			m_LineVertex;
	int								m_nNumHalf;
	CMesh*							m_mesh;

	ID3DX11Effect*					m_fx;
	ID3DX11EffectTechnique*			m_tech;
	ID3DX11EffectMatrixVariable*	m_fxWorldViewProj;

};

#endif // !_GRID_H_