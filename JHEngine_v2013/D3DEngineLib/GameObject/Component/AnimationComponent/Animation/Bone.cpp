#include "..\..\..\..\Common.h"
#include "Bone.h"


CBone::CBone()
	: m_parent(NULL)
{
}


CBone::~CBone()
{
	for (int i = 0; i < m_children.size(); ++i)
	{
		delete m_children[i];
	}
}
