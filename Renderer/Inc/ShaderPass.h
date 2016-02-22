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

	private:
		unsigned int m_blendState;
		unsigned int m_depthStencilState;
		unsigned int m_rasterizerStates;

		//Shaders
		CShaderHandle<ID3D11VertexShader>*		m_pVertexShader = nullptr;
		CShaderHandle<ID3D11PixelShader>*		m_pPixelShader = nullptr;
		CShaderHandle<ID3D11HullShader>*		m_pHullShader = nullptr;
		CShaderHandle<ID3D11DomainShader>*		m_pDomainShader = nullptr;
		CShaderHandle<ID3D11GeometryShader>*	m_pGeometryShader = nullptr;


	public:
		CShaderPass(ID3D11Device* d3dDevice, unsigned int blendState = 0, unsigned int depthStencilState = 1, unsigned int rasterizerStates = 0);
		CShaderPass(ID3D11Device* d3dDevice,
			const char* vs_file, const char* ps_file, const char* hs_file, const char* ds_file, const char* gs_file,
			unsigned int blendState = 0, unsigned int depthStencilState = 1, unsigned int rasterizerStates = 0);
		~CShaderPass();

		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
	};
}
