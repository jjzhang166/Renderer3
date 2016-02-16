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
	template<typename Shadertype> class CShaderHandle;

	class CShaderPass : public IRenderNode
	{
		CShaderHandle<ID3D11VertexShader>*		m_pVertexShader = nullptr;
		CShaderHandle<ID3D11PixelShader>*		m_pPixelShader = nullptr;
		CShaderHandle<ID3D11HullShader>*		m_pHullShader = nullptr;
		CShaderHandle<ID3D11DomainShader>*		m_pDomainShader = nullptr;
		CShaderHandle<ID3D11GeometryShader>*	m_pGeometryShader = nullptr;


	public:
		CShaderPass(ID3D11Device* d3dDevice);
		~CShaderPass();

		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
	};
}
