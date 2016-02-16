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
#include "..\Inc\ShaderPass.h"
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

		CShaderPass pass(m_deviceResources->GetD3DDevice());
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