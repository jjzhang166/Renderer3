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
#include "..\Inc\DeviceResoureces.h"
#include "..\Inc\ShaderHandle.h"

namespace Renderer
{
	bool CRendererController::m_bInstantiated = false;
	std::shared_ptr<CDeviceResoureces> CRendererController::m_deviceResources;
	/*std::unique_ptr<BlendStateManager> CRendererController::m_blendStateManager;
	std::unique_ptr<DepthStencilStateManager> CRendererController::m_DepthStenciStateManager;
	std::unique_ptr<StreamManager> CRendererController::m_StreamManager;*/


	CRendererController::CRendererController(HWND mainWindow, unsigned int uwidth, unsigned int uheight)
	{
		assert(!m_bInstantiated && "Only one CRendererController instance is allowed.");
		m_deviceResources = std::make_shared<CDeviceResoureces>(mainWindow, uwidth, uheight);
		m_bInstantiated = true;

		//CShaderHandle<ID3D11VertexShader> vs(m_deviceResources->GetD3DDevice(), "VertexShader.cso");
		//CShaderHandle<ID3D11ComputeShader> cs(m_deviceResources->GetD3DDevice(), "ComputeShader.cso");
		//CShaderHandle<ID3D11PixelShader> ps(m_deviceResources->GetD3DDevice(), "PixelShader.cso");
		//CShaderHandle<ID3D11HullShader> hs(m_deviceResources->GetD3DDevice(), "HullShader.cso");
		//CShaderHandle<ID3D11DomainShader> ds(m_deviceResources->GetD3DDevice(), "DomainShader.cso");
		//CShaderHandle<ID3D11GeometryShader> gs(m_deviceResources->GetD3DDevice(), "GeometryShader.cso");

	}


	CRendererController::~CRendererController()
	{
		//Release Device Resources
		m_deviceResources.reset();
	}

	void CRendererController::Draw()
	{

	}


	void CRendererController::CreateDeviceResources()
	{

	}
}