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
	class CRenderable;
	class CRendererController
	{
	private:
		static bool m_bInstantiated;
		/*static std::unique_ptr<StreamManager> m_StreamManager;*/
		std::unique_ptr<CView> m_View;
		CShaderEffect* m_ShaderEffect;
		CMaterial* m_Material;
		std::vector<CRenderable*> m_Renderables;

		
		
	public:
#ifdef _DEBUG
		static TwBar* m_TweakBar;
#endif // _DEBUG
		RENDERER_API static std::shared_ptr<CDeviceResoureces> m_deviceResources;
		static std::unique_ptr<CCommonStateObjects> m_CommonState;
		RENDERER_API CRendererController(HWND mainWindow, unsigned int uwidth = 1920u, unsigned int uheight = 1080u);
		RENDERER_API ~CRendererController();
		RENDERER_API void Draw();

#ifdef _DEBUG
		RENDERER_API int TweakBarEventWin(HWND& wnd, UINT& msg, WPARAM& wParam, LPARAM& lParam);
#endif // _DEBUG
	private:
		CRendererController(const CRendererController&) = delete;
		CRendererController& operator=(const CRendererController&) = delete;
	};

}