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
		for (auto& eachShaderPass : m_ShaderPasses->m_set)
		{
			delete eachShaderPass;
		}
	}

	/*virtual*/ void CShaderEffect::Begin(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = (CView&)(*pCurrentView);
		view.currentState = SHADEREFFECT_BEGIN;
		for (auto& eachShaderPass : m_ShaderPasses->m_set)
		{
			eachShaderPass->Begin(pCurrentView);
		}

	}
	/*virtual*/ void CShaderEffect::End(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = (CView&)(*pCurrentView);
		view.currentState = SHADEREFFECT_END;
		for (auto& eachShaderPass : m_ShaderPasses->m_set)
		{
			eachShaderPass->End(pCurrentView);
		}
	}
}