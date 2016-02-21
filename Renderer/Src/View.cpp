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
	CView::CView(XMFLOAT4X4 d3dViewMatrix, XMFLOAT4X4 d3dProjMatrix) : m_d3dViewMatrix(d3dViewMatrix),m_d3dProjMatrix(d3dProjMatrix)
	{
		m_MainRTVs = CRendererController::m_deviceResources->GetBackBufferRenderTargetView();
		m_DepthView = CRendererController::m_deviceResources->GetDepthStencilView();
	}


	CView::~CView()
	{
	}


	/*virtual*/ void CView::Begin(IRenderNode* pCurrentView) /*final*/
	{
		currentState = VIEW_BEGIN;
		CRendererController::m_deviceResources->GetD3DDeviceContext()->OMSetRenderTargets(1, &m_MainRTVs, m_DepthView);
	}

	/*virtual*/ void CView::End(IRenderNode* pCurrentView) /*final*/
	{
		currentState = VIEW_END;
		CRendererController::m_deviceResources->GetD3DDeviceContext()->OMSetRenderTargets(0, nullptr, nullptr);
	}
}