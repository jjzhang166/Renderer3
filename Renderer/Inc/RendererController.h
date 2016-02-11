/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#pragma once
#ifdef RENDERER_EXPORTS
#define RENDERER_API __declspec(dllexport)
#else
#define RENDERER_API __declspec(dllimport)
#endif

#include "DeviceResoureces.h"
#include "Renderer.h"
namespace Renderer
{

	class CRendererController
	{
		std::shared_ptr<CDeviceResoureces> m_deviceResources;
		std::unique_ptr<CRenderer> m_renderer;
	public:
		RENDERER_API CRendererController(HWND mainWindow, unsigned int uwidth = 1600u, unsigned int uheight = 1024u);
		RENDERER_API ~CRendererController();
		RENDERER_API void Draw();
	};

}