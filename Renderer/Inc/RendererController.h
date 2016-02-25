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
	class CCommonStateObjects;
	class CRendererController
	{
		static bool m_bInstantiated;
		/*static std::unique_ptr<StreamManager> m_StreamManager;*/
		std::unique_ptr<CView> m_View;
		std::unique_ptr<CShaderEffect> m_ShaderEffect;
		std::unique_ptr<CMaterial> m_Material;
		TwBar* m_TweakBar;
		
	public:
		RENDERER_API static std::shared_ptr<CDeviceResoureces> m_deviceResources;
		static std::unique_ptr<CCommonStateObjects> m_CommonState;
		RENDERER_API CRendererController(HWND mainWindow, unsigned int uwidth = 1920u, unsigned int uheight = 1080u);
		RENDERER_API ~CRendererController();
		RENDERER_API void CreateDeviceResources();
		RENDERER_API void Draw();
	private:
		CRendererController(const CRendererController&);
		CRendererController& operator=(const CRendererController&);
	};

}