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
#include "..\Inc\Renderer.h"

namespace Renderer
{
	CRendererController::CRendererController(HWND mainWindow, unsigned int uwidth, unsigned int uheight)
	{
		m_deviceResources = std::make_shared<CDeviceResoureces>(mainWindow, uwidth, uheight);
		std::unique_ptr<CRenderer> renderer(new CRenderer(m_deviceResources));
		m_renderer = std::move(renderer);
	}


	CRendererController::~CRendererController()
	{
	}

	void CRendererController::Draw()
	{
		m_renderer->Render();
	}
}