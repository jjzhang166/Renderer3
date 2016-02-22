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
	class CView : public IRenderNode
	{
	public:
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
	
		eRenderState currentState;
		CView(DirectX::XMFLOAT4X4 d3dViewMatrix, DirectX::XMFLOAT4X4 d3dProjMatrix);
		~CView();
		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
		inline DirectX::XMFLOAT4X4 ViewMatrix() const { return m_d3dViewMatrix; }
		inline DirectX::XMFLOAT4X4 ProjectionMatrix() const { return m_d3dProjMatrix; }
	};
}
