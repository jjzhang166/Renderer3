/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#include "stdafx.h"
#include "..\Inc\ShaderEffect.h"
#include "..\Inc\View.h"
#include "..\Inc\RenderSet.h"

namespace Renderer
{
	CShaderEffect::CShaderEffect() : m_ShaderPasses(new CRenderSet), m_Materials(new CRenderSet)
	{
	}


	CShaderEffect::~CShaderEffect()
	{
	}

	/*virtual*/ void CShaderEffect::Begin(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = (CView&)(*pCurrentView);
		view.currentState = SHADEREFFECT_BEGIN;
		m_ShaderPasses->m_set.front()->Begin(pCurrentView);

	}
	/*virtual*/ void CShaderEffect::End(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = (CView&)(*pCurrentView);
		view.currentState = SHADEREFFECT_END;
		m_ShaderPasses->m_set.front()->End(pCurrentView);
	}
}