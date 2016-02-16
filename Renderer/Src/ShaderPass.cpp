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

namespace Renderer
{
	CShaderPass::CShaderPass(ID3D11Device* d3dDevice) :
		m_pVertexShader(nullptr),
		m_pPixelShader(nullptr),
		m_pHullShader(nullptr),
		m_pDomainShader(nullptr),
		m_pGeometryShader(nullptr)

	{
		m_pVertexShader = new CShaderHandle<ID3D11VertexShader>(d3dDevice, "VertexShader.cso");
		m_pPixelShader = new CShaderHandle<ID3D11PixelShader>(d3dDevice, "PixelShader.cso");
	
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

	}
	/*virtual*/ void CShaderPass::End(IRenderNode* pCurrentView) /*final*/
	{

	}
}