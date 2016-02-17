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
#include "..\Inc\ShaderPass.h"
#include "..\Inc\ShaderHandle.h"
#include "..\Inc\RendererController.h"
#include "..\Inc\CommonStateObjects.h"
namespace Renderer
{

	CShaderPass::CShaderPass(ID3D11Device* d3dDevice, unsigned int blendState, unsigned int depthStencilState, unsigned int rasterizerStates) :
		m_blendState(blendState),
		m_depthStencilState(depthStencilState),
		m_rasterizerStates(rasterizerStates),
		m_pVertexShader(nullptr),
		m_pPixelShader(nullptr),
		m_pHullShader(nullptr),
		m_pDomainShader(nullptr),
		m_pGeometryShader(nullptr)

	{
		m_pVertexShader = new CShaderHandle<ID3D11VertexShader>(d3dDevice, "VertexShader.cso");
		m_pPixelShader = new CShaderHandle<ID3D11PixelShader>(d3dDevice, "PixelShader.cso");

	}

	CShaderPass::CShaderPass(ID3D11Device* d3dDevice, unsigned int blendState, unsigned int depthStencilState, unsigned int rasterizerStates,
		const char* vs_file, const char* ps_file, const char* hs_file, const char* ds_file, const char* gs_file) :
		m_blendState(blendState),
		m_depthStencilState(depthStencilState),
		m_rasterizerStates(rasterizerStates),
		m_pVertexShader(new CShaderHandle<ID3D11VertexShader>(d3dDevice, vs_file)),
		m_pPixelShader(new CShaderHandle<ID3D11PixelShader>(d3dDevice, ps_file)),
		m_pHullShader(new CShaderHandle<ID3D11HullShader>(d3dDevice, hs_file)),
		m_pDomainShader(new CShaderHandle<ID3D11DomainShader>(d3dDevice, ds_file)),
		m_pGeometryShader(new CShaderHandle<ID3D11GeometryShader>(d3dDevice, gs_file))

	{
	}


	CShaderPass::~CShaderPass()
	{
		if (m_pVertexShader)
		{
			delete m_pVertexShader;
		}
		if (m_pPixelShader)
		{
			delete m_pPixelShader;
		}
		if (m_pHullShader)
		{
			delete m_pHullShader;
		}
		if (m_pDomainShader)
		{
			delete m_pDomainShader;
		}
		if (m_pGeometryShader)
		{
			delete m_pGeometryShader;
		}
	}

	/*virtual*/ void CShaderPass::Begin(IRenderNode* pCurrentView) /*final*/
	{
		auto deviceContext = CRendererController::m_deviceResources->GetD3DDeviceContext();
		deviceContext->OMSetBlendState(CCommonStateObjects::m_blendStates[m_blendState], nullptr, 0xffffffff);
		deviceContext->OMSetDepthStencilState(CCommonStateObjects::m_depthStencilStates[m_depthStencilState], 0);
		deviceContext->RSSetState(CCommonStateObjects::m_rasterizerStates[m_rasterizerStates]);
	}
	/*virtual*/ void CShaderPass::End(IRenderNode* pCurrentView) /*final*/
	{
		auto deviceContext = CRendererController::m_deviceResources->GetD3DDeviceContext();
		//Reset states
		deviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
		deviceContext->OMSetDepthStencilState(nullptr, 0);
		deviceContext->RSSetState(nullptr);
	}
}