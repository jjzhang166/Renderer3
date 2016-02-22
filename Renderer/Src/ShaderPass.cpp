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
	}

	CShaderPass::CShaderPass(ID3D11Device* d3dDevice,
		const char* vs_file, const char* ps_file, const char* hs_file, const char* ds_file, const char* gs_file,
		unsigned int blendState, unsigned int depthStencilState, unsigned int rasterizerStates) :
		m_blendState(blendState),
		m_depthStencilState(depthStencilState),
		m_rasterizerStates(rasterizerStates)

	{
		if (vs_file)
		{
			m_pVertexShader = new CShaderHandle<ID3D11VertexShader>(d3dDevice, vs_file);
		}
		if (ps_file)
		{
			m_pPixelShader = new CShaderHandle<ID3D11PixelShader>(d3dDevice, ps_file);
		}
		if (gs_file)
		{
			m_pGeometryShader = new CShaderHandle<ID3D11GeometryShader>(d3dDevice, gs_file);
		}
		if (hs_file)
		{
			m_pHullShader = new CShaderHandle<ID3D11HullShader>(d3dDevice, hs_file);
		}
		if (ds_file)
		{
			m_pDomainShader = new CShaderHandle<ID3D11DomainShader>(d3dDevice, ds_file);
		}
		
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
		if (m_pVertexShader)
		{
			deviceContext->VSSetShader(m_pVertexShader->m_shader.Get(), nullptr, 0);
		}
		if (m_pPixelShader)
		{
			deviceContext->PSSetShader(m_pPixelShader->m_shader.Get(), nullptr, 0);
		}
		if (m_pGeometryShader)
		{
			deviceContext->GSSetShader(m_pGeometryShader->m_shader.Get(), nullptr, 0);
		}
		if (m_pHullShader)
		{
			deviceContext->HSSetShader(m_pHullShader->m_shader.Get(), nullptr, 0);
		}
		if (m_pDomainShader)
		{
			deviceContext->DSSetShader(m_pDomainShader->m_shader.Get(), nullptr, 0);
		}
		static CCommonStateObjects commonState;
		deviceContext->OMSetBlendState(commonState.m_blendStates[m_blendState], nullptr, 0xffffffff);
		deviceContext->OMSetDepthStencilState(commonState.m_depthStencilStates[m_depthStencilState], 0);
		deviceContext->RSSetState(commonState.m_rasterizerStates[m_rasterizerStates]);
	}
	/*virtual*/ void CShaderPass::End(IRenderNode* pCurrentView) /*final*/
	{
		auto deviceContext = CRendererController::m_deviceResources->GetD3DDeviceContext();

		deviceContext->VSSetShader(nullptr, nullptr, 0);
		deviceContext->PSSetShader(nullptr, nullptr, 0);
		deviceContext->GSSetShader(nullptr, nullptr, 0);
		deviceContext->HSSetShader(nullptr, nullptr, 0);
		deviceContext->DSSetShader(nullptr, nullptr, 0);
		//Reset states
		deviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
		deviceContext->OMSetDepthStencilState(nullptr, 0);
		deviceContext->RSSetState(nullptr);
	}
}