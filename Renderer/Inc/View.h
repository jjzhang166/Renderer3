#pragma once
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
	class CView : IRenderNode
	{
		DirectX::XMFLOAT4X4 m_d3dViewMatrix;
		DirectX::XMFLOAT4X4 m_d3dProjMatrix;
		CRenderSet* m_opaqueShaderEffects;
		CRenderSet* m_transparentRenderables;
		IRenderNode* currentShaderEffects;
		IRenderNode* currentShaderPass;
		IRenderNode* currentMaterial;
		IRenderNode* currentRenderable;
		eRenderState currentState = eRenderState::APPLYVIEW;
	public:
		CView();
		~CView();
		virtual void Begin(IRenderNode* pCurrentView);
		virtual void End(IRenderNode* pCurrentView);
	};
}
