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
	class CRenderSet;
	class CShaderEffect : public IRenderNode
	{
	public:
		std::unique_ptr<CRenderSet> m_ShaderPasses = nullptr;
		std::unique_ptr<CRenderSet>  m_Materials = nullptr;
		CShaderEffect();
		~CShaderEffect();

		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
	};
}
