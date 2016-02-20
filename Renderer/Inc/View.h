#pragma once
/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/


#include "RenderNode.h"
namespace Renderer
{
	class CRenderSet;
	class CView : IRenderNode
	{
		DirectX::XMFLOAT4X4 m_d3dViewMatrix;
		DirectX::XMFLOAT4X4 m_d3dProjMatrix;
		std::unique_ptr<CRenderSet> m_opaqueShaderEffects;
		std::unique_ptr<CRenderSet> m_transparentRenderables;

		ID3D11RenderTargetView* m_MainRTVs;
		ID3D11DepthStencilView* m_DepthView;
		//State Ids
		IRenderNode* currentShaderEffects;
		IRenderNode* currentShaderPass;
		IRenderNode* currentMaterial;
		IRenderNode* currentRenderable;
	public:
		eRenderState currentState;
		CView(DirectX::XMFLOAT4X4 d3dViewMatrix, DirectX::XMFLOAT4X4 d3dProjMatrix);
		~CView();
		virtual void Begin(IRenderNode* pCurrentView);
		virtual void End(IRenderNode* pCurrentView);
	};
}
