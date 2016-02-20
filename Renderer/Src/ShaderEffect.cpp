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
		CView& view = *((CView*)pCurrentView);
		view.currentState = SHADEREFFECT_BEGIN;

	}
	/*virtual*/ void CShaderEffect::End(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = *((CView*)pCurrentView);
		view.currentState = SHADEREFFECT_END;;
	}
}