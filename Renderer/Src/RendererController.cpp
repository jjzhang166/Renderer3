/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#include "stdafx.h"
#ifdef _DEBUG
#include <vld.h>
#endif // _DEBUG

#include "..\stdafx.h"
#include <DDSTextureLoader.h>
#include "..\Inc\RendererController.h"
#include "..\Inc\ShaderEffect.h"
#include "..\Inc\RenderSet.h"
#include "..\Inc\ShaderPass.h"
#include "..\Inc\Material.h"
#include "..\Inc\View.h"
#include "..\Inc\InputLayoutManager.h"
#include "..\Inc\CommonStateObjects.h"
#include "..\Inc\Renderable.h"

using namespace DirectX;
using namespace std;
namespace Renderer
{
	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}


	bool CRendererController::m_bInstantiated = false;
	std::shared_ptr<CDeviceResoureces> CRendererController::m_deviceResources;
	std::unique_ptr<CCommonStateObjects> CRendererController::m_CommonState;

#ifdef _DEBUG
	TwBar* CRendererController::m_TweakBar;
#endif // _DEBUG

	/*std::unique_ptr<StreamManager> CRendererController::m_StreamManager;*/


	CRendererController::CRendererController(HWND mainWindow, unsigned int uwidth, unsigned int uheight) :
		m_View(nullptr),
		m_ShaderEffect(nullptr),
		m_Material(nullptr)
	{
		assert(!m_bInstantiated && "Only one CRendererController instance is allowed.");
		m_deviceResources = std::make_shared<CDeviceResoureces>(mainWindow, uwidth, uheight);
		m_bInstantiated = true;


#ifdef _DEBUG
		TwInit(TW_DIRECT3D11, m_deviceResources->GetD3DDevice());
		m_TweakBar = TwNewBar("TweakBar");
		int barSize[2] = { 500, 400 };
		TwSetParam(m_TweakBar, NULL, "size", TW_PARAM_INT32, 2, barSize);
#endif // _DEBUG

		CInputLayoutManager::GetRef().Initilize();
		m_CommonState = unique_ptr<CCommonStateObjects>(new CCommonStateObjects);
		//Bind all samplers
		auto deviceContext = m_deviceResources->GetD3DDeviceContext();
		deviceContext->VSSetSamplers(0, CCommonStateObjects::COUNT_SS, m_CommonState->m_samplerStates);
		deviceContext->PSSetSamplers(0, CCommonStateObjects::COUNT_SS, m_CommonState->m_samplerStates);
		deviceContext->HSSetSamplers(0, CCommonStateObjects::COUNT_SS, m_CommonState->m_samplerStates);
		deviceContext->GSSetSamplers(0, CCommonStateObjects::COUNT_SS, m_CommonState->m_samplerStates);
		deviceContext->DSSetSamplers(0, CCommonStateObjects::COUNT_SS, m_CommonState->m_samplerStates);


		XMFLOAT3 up(0.0f, 1.0f, 0.0f);
		XMFLOAT3 side(1.0f, 0.0f, 0.0f);
		XMFLOAT3 forward(0.0f, 0.0f, -1.0f);
		XMFLOAT3 position(0.0f, 75.0f, 100.0f);

		auto view = XMMatrixLookToLH(XMLoadFloat3(&position), XMLoadFloat3(&forward), XMLoadFloat3(&up));
		auto proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
		XMFLOAT4X4 view4x4, proj4x4;
		XMStoreFloat4x4(&view4x4, view);
		XMStoreFloat4x4(&proj4x4, proj);
		m_View = unique_ptr<CView>(new CView(view4x4, proj4x4));
		m_View->AddaRTV(m_deviceResources->GetBackBufferRenderTargetView());
		m_View->SetDepthView(m_deviceResources->GetDepthStencilView());



		m_ShaderEffect = new CShaderEffect();
		m_View->GetOpaqueShaderEffects()->AddtoHead(m_ShaderEffect);
		m_ShaderEffect->m_ShaderPass = unique_ptr<CShaderPass>(new CShaderPass(m_deviceResources->GetD3DDevice(), "CSO\\VertexShader.cso", "CSO\\PixelShader.cso", nullptr, nullptr, nullptr, 0, 1, 2));
		m_Material = new CMaterial();
		ID3D11ShaderResourceView* testSRV = nullptr;
		DirectX::CreateDDSTextureFromFile(m_deviceResources->GetD3DDevice(), L"Teddy_D.dds", nullptr, &testSRV);
		m_Material->AddMap(0, testSRV);
		m_ShaderEffect->m_Materials->AddtoHead(m_Material);
		XMFLOAT4X4 world4x4;
		for (size_t i = 0; i < 1; i++)
		{
			XMStoreFloat4x4(&world4x4, XMMatrixIdentity());
			auto newRenderable = new CRenderable(*m_Material, world4x4, "Teddy_Idle.mesh");
			m_Renderables.push_back(newRenderable);
			m_Material->m_Renderables->AddtoHead(newRenderable);
		}



	}


	CRendererController::~CRendererController()
	{

#ifdef _DEBUG
		TwTerminate();
#endif // _DEBUG

		m_CommonState.reset(nullptr);
		delete m_ShaderEffect;
		delete m_Material;
		for (auto& eachRenderable : m_Renderables)
		{
			delete eachRenderable;
		}
		////D3D debug memory leak report


		/*Microsoft::WRL::ComPtr<ID3D11Debug> pDebug;
		m_deviceResources->GetD3DDevice()->QueryInterface(IID_PPV_ARGS(&pDebug));
		if (pDebug != nullptr)
		{
			pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
			pDebug = nullptr;
		}
*/

		//Release Device Resources
		m_deviceResources.reset();

	}

	void CRendererController::Draw()
	{
		auto d3dDeviceContext = m_deviceResources->GetD3DDeviceContext();
		FLOAT clearClor[4] = { 0.0f,0.0f,0.0f,1.0f };
		d3dDeviceContext->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), clearClor);
		d3dDeviceContext->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 1);

		m_View->Begin(m_View.get());
		for (auto& eachShaderEffect : m_View->GetOpaqueShaderEffects()->m_Set)
		{
			CShaderEffect& SEptr = (CShaderEffect&)(*eachShaderEffect);
			SEptr.Begin(m_View.get());
			for (auto& eachMateial : SEptr.m_Materials->m_Set)
			{
				CMaterial& MATptr = (CMaterial&)(*eachMateial);
				MATptr.Begin(m_View.get());
				for (auto& eachRenderable : MATptr.m_Renderables->m_Set)
				{
					CRenderable& RENptr = (CRenderable&)(*eachRenderable);
					RENptr.Begin(m_View.get());
					RENptr.End(m_View.get());
				}
				MATptr.End(m_View.get());
			}
			SEptr.End(m_View.get());
		}
#ifdef _DEBUG
		TwDraw();
#endif // _DEBUG
		m_View->End(m_View.get());




	}

#ifdef _DEBUG
	int CRendererController::TweakBarEventWin(HWND& wnd, UINT& msg, WPARAM& wParam, LPARAM& lParam)
	{
		return TwEventWin(wnd, msg, wParam, lParam);
	}
#endif // _DEBUG
}