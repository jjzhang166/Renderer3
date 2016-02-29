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
#include "..\Inc\Material.h"
#include "..\Inc\RenderSet.h"
#include "..\Inc\View.h"
#include "..\Inc\ShaderEffect.h"
#include "..\Inc\RendererController.h"

namespace Renderer
{
	CMaterial::CMaterial() :  m_Renderables(new CRenderSet)
	{
		for (unsigned int i = 0; i < CMaterialInput::MAP_COUNT; i++)
		{
			m_MaterialInput.m_TextureMap[i] = nullptr;
		}
		
	}


	CMaterial::~CMaterial()
	{
		for (auto& eachMap : m_MaterialInput.m_TextureMap)
		{
			if (eachMap.second)
			{
				eachMap.second->Release();
				eachMap.second = nullptr;
			}
		}
	}

	/*virtual*/ void CMaterial::Begin(IRenderNode* pCurrentView) /*final*/
	{
		CView& view = (CView&)(*pCurrentView);
		view.m_CurrentState = MATERIAL_BEGIN;
		view.m_CurrentMaterial = this;
		auto deviceContext = CRendererController::m_deviceResources->GetD3DDeviceContext();
		ID3D11ShaderResourceView* SRVs[CMaterialInput::MAP_COUNT];
		for (unsigned int i = 0; i < CMaterialInput::MAP_COUNT; i++)
		{
			SRVs[i] = m_MaterialInput.m_TextureMap[i];
		}
		deviceContext->VSSetShaderResources(CMaterialInput::HEIGHT, 1, &SRVs[CMaterialInput::HEIGHT]);
		deviceContext->PSSetShaderResources(0, CMaterialInput::MAP_COUNT, SRVs);
	}


	/*virtual*/ void CMaterial::End(IRenderNode* pCurrentView) /*final*/
	{
		auto deviceContext = CRendererController::m_deviceResources->GetD3DDeviceContext();
		CView& view = (CView&)(*pCurrentView);
		view.m_CurrentState = MATERIAL_END;
		deviceContext->VSSetShaderResources(CMaterialInput::HEIGHT, 0, nullptr);
		deviceContext->PSSetShaderResources(0, 0, nullptr);

		view.m_CurrentMaterial = nullptr;
	}
	
	void CMaterial::AddMap(unsigned int _mapType, ID3D11ShaderResourceView* _mapView)
	{
		m_MaterialInput.m_TextureMap[_mapType] = _mapView;
	}
	void CMaterial::AddVector3(std::string _name, DirectX::XMFLOAT3 _value)
	{
		m_MaterialInput.m_Vector3Map[_name] = _value;
	}
	void CMaterial::AddFloat(std::string _name, float _value)
	{
		m_MaterialInput.m_FloatMap[_name] = _value;
	}
}