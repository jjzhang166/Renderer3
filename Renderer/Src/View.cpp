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
#include "..\Inc\View.h"
#include "..\Inc\RenderSet.h"
#include "..\Inc\RendererController.h"

using namespace std;
using namespace DirectX;
namespace Renderer
{
	CView::CView(XMFLOAT4X4 d3dViewMatrix, XMFLOAT4X4 d3dProjMatrix) : m_CurrentState(NULLSTATE), m_d3dViewMatrix(d3dViewMatrix), m_d3dProjMatrix(d3dProjMatrix), m_opaqueShaderEffects(new CRenderSet)
	{
		
	}



	void CView::SetOpaqueShaderEffects(CRenderSet* _newShaderEffects)
	{
		m_opaqueShaderEffects.reset(_newShaderEffects);
	}
	void CView::SetTransparentRenderables(CRenderSet* _newTransparentRenderables)
	{
		m_transparentRenderables.reset(_newTransparentRenderables);
	}

	CView::~CView()
	{
	}


	/*virtual*/ void CView::Begin(IRenderNode* pCurrentView) /*final*/
	{
		m_CurrentState = VIEW_BEGIN;
		CRendererController::m_deviceResources->GetD3DDeviceContext()->OMSetRenderTargets((unsigned)m_RTVs.size(), m_RTVs.data(), m_DepthView);
	}

	/*virtual*/ void CView::End(IRenderNode* pCurrentView) /*final*/
	{
		m_CurrentState = VIEW_END;
		CRendererController::m_deviceResources->GetD3DDeviceContext()->OMSetRenderTargets(0, nullptr, nullptr);
	}
}