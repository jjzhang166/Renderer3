/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#include "stdafx.h"
#include "..\stdafx.h"
#include "..\Inc\Material.h"
#include "..\Inc\RenderSet.h"
#include "..\Inc\View.h"

namespace Renderer
{
	CMaterial::CMaterial() : m_shaderEffects(new CRenderSet), m_renderables(new CRenderSet)
	{
	}


	CMaterial::~CMaterial()
	{
	}

	/*virtual*/ void CMaterial::Begin(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = *((CView*)pCurrentView);
		view.currentState = MATERIAL_BEGIN;
	}


	/*virtual*/ void CMaterial::End(IRenderNode* pCurrentView) /*final*/
	{
		
		CView& view = *((CView*)pCurrentView);
		view.currentState = MATERIAL_END;
	}
	
	void CMaterial::AddtoShaderEffect(CShaderEffect* pShaderEffect)
	{
		
	}
}