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
#include <AntTweakBar.h>

namespace Renderer
{

	class StreamManager;
	class CView;
	class CShaderEffect;
	class CMaterial;

	class CRendererController
	{
		static bool m_bInstantiated;
		/*static std::unique_ptr<StreamManager> m_StreamManager;*/
		CView* m_View;
		CShaderEffect* m_ShaderEffect;
		CMaterial* m_Material;
		TwBar* bar;
	public:
		RENDERER_API static std::shared_ptr<CDeviceResoureces> m_deviceResources;
		RENDERER_API CRendererController(HWND mainWindow, unsigned int uwidth = 1920u, unsigned int uheight = 1080u);
		RENDERER_API ~CRendererController();
		RENDERER_API void CreateDeviceResources();
		RENDERER_API void Draw();
	private:
		CRendererController(const CRendererController&);
		CRendererController& operator=(const CRendererController&);
	};

}