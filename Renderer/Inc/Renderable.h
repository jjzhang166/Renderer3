/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#pragma once
#include "RenderNode.h"

namespace Renderer
{
	class CMaterial;
	class CRenderable :public IRenderNode
	{
		CMaterial&			m_Material;
		DirectX::XMFLOAT4X4 m_d3dWorldMatrix;
		float				m_Depth;
		unsigned int		m_uStartVertex;
		unsigned int		m_uStartIndex;
		unsigned int		m_uNumofVertices;
		unsigned int		m_uNumofIndices;
	public:
		CRenderable( CMaterial& material);
		~CRenderable();
	};
}
