/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#include "stdafx.h"
#include "..\Inc\RenderSet.h"

namespace Renderer
{
	CRenderSet::CRenderSet()
	{
	}


	CRenderSet::~CRenderSet()
	{
	}

	void CRenderSet::AddtoHead(IRenderNode* node)
	{
		m_set.push_front(node);

	}
	void CRenderSet::AddtoTail(IRenderNode* node)
	{
		m_set.push_back(node);
	}
	void CRenderSet::Sort(CompareFunc sortMethod)
	{
		m_set.sort(sortMethod);
	}
}