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
#include "..\Inc\RendererController.h"
#include "..\Inc\ShaderEffect.h"
#include "..\Inc\RenderSet.h"
#include "..\Inc\ShaderPass.h"
#include "..\Inc\Material.h"
#include "..\Inc\View.h"
#include "..\Inc\InputLayoutManager.h"
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
	/*std::unique_ptr<StreamManager> CRendererController::m_StreamManager;*/


	CRendererController::CRendererController(HWND mainWindow, unsigned int uwidth, unsigned int uheight) : m_View(nullptr)
	{
		assert(!m_bInstantiated && "Only one CRendererController instance is allowed.");
		m_deviceResources = std::make_shared<CDeviceResoureces>(mainWindow, uwidth, uheight);
		m_bInstantiated = true;

		CInputLayoutManager::GetRef().Initilize();
		XMFLOAT3 up(0.0f, 1.0f, 0.0f);
		XMFLOAT3 side(1.0f, 0.0f, 0.0f);
		XMFLOAT3 forward(0.0f, 0.0f, -1.0f);
		XMFLOAT3 position(0.0f, 75.0f, 100.0f);

		auto view = XMMatrixLookToLH(XMLoadFloat3(&position), XMLoadFloat3(&forward), XMLoadFloat3(&up));
		auto proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
		XMFLOAT4X4 view4x4, proj4x4;
		XMStoreFloat4x4(&view4x4, view);
		XMStoreFloat4x4(&proj4x4, proj);
		m_View = new CView(view4x4, proj4x4);
		m_View->m_MainRTVs = m_deviceResources->GetBackBufferRenderTargetView();
		m_View->m_DepthView = m_deviceResources->GetDepthStencilView();
		m_ShaderEffect = new CShaderEffect();
		m_View->m_opaqueShaderEffects->AddtoHead(m_ShaderEffect);
		m_ShaderEffect->m_ShaderPasses->AddtoHead(new CShaderPass(m_deviceResources->GetD3DDevice(), "CSO\\VertexShader.cso", "CSO\\PixelShader.cso", nullptr, nullptr, nullptr, 0, 1, 2));
		m_Material = new CMaterial();
		m_ShaderEffect->m_Materials->AddtoHead(m_Material);
		//m_Material->m_renderables->AddtoHead(new CRenderable(*m_Material, world4x4, "test.mesh"));
		XMFLOAT4X4 world4x4;
		srand(time(nullptr));
		for (size_t i = 0; i < 10000; i++)
		{

			XMStoreFloat4x4(&world4x4, XMMatrixScaling(0.01f, 0.01f, 0.01f) * XMMatrixRotationAxis(XMLoadFloat3(&up), XMConvertToRadians(RandomFloat(-100.0f, 100.0f))) * XMMatrixTranslation(RandomFloat(-100.0f, 100.0f), RandomFloat(-100.0f, 100.0f), RandomFloat(-100.0f, 100.0f)));
			m_Material->m_renderables->AddtoHead(new CRenderable(*m_Material, world4x4, "Teddy_Idle.mesh"));
		}
	}


	CRendererController::~CRendererController()
	{
		//Release Device Resources
		m_deviceResources.reset();
	}

	void CRendererController::Draw()
	{
		auto d3dDeviceContext = m_deviceResources->GetD3DDeviceContext();
		FLOAT clearClor[4] = { 0.0f,1.0f,1.0f,1.0f };
		d3dDeviceContext->ClearRenderTargetView(m_deviceResources->GetBackBufferRenderTargetView(), clearClor);
		d3dDeviceContext->ClearDepthStencilView(m_deviceResources->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 1);

		m_View->Begin(m_View);
		for (auto eachShaderEffect : m_View->m_opaqueShaderEffects->m_set)
		{
			CShaderEffect* SEptr = (CShaderEffect*)eachShaderEffect;
			SEptr->Begin(m_View);
			for (auto eachMateial : SEptr->m_Materials->m_set)
			{
				CMaterial* MATptr = (CMaterial*)eachMateial;
				MATptr->Begin(m_View);
				for (auto eachRenderable : MATptr->m_renderables->m_set)
				{
					CRenderable* RENptr = (CRenderable*)eachRenderable;
					RENptr->Begin(m_View);
					RENptr->End(m_View);
				}
				MATptr->End(m_View);
			}
			SEptr->End(m_View);
		}
		m_View->End(m_View);




		m_deviceResources->Present();
	}


	void CRendererController::CreateDeviceResources()
	{

	}
}