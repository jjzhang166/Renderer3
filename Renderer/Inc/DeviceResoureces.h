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


#include "..\stdafx.h"

namespace Renderer
{

	class CDeviceResoureces
	{
		

		// Direct3D objects.
		Microsoft::WRL::ComPtr<ID3D11Device>			m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>		m_d3dContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain>			m_swapChain;

		// Direct3D rendering objects. Required for 3D.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_d3dRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_d3dDepthStencilView;
		D3D11_VIEWPORT									m_screenViewport;

		// DirectWrite drawing components.
		Microsoft::WRL::ComPtr<IDWriteFactory>			m_dwriteFactory;
		Microsoft::WRL::ComPtr<IWICImagingFactory>		m_wicFactory;

		// Cached reference to the Window.
		HWND m_window;

		// Cached device properties.
		D3D_FEATURE_LEVEL								m_d3dFeatureLevel;
		SIZE											m_d3dRenderTargetSize;
		SIZE											m_outputSize;


		// Private Functions
		void CreateDeviceIndependentResources();
		void CreateDeviceResources();
		void CreateWindowSizeDependentResources();
	public:
		RENDERER_API CDeviceResoureces(HWND mainWindow, unsigned int uwidth, unsigned int uheight);

		RENDERER_API void ResizeWindow(unsigned int uwidth, unsigned int uheight);
		// Default no vsync
		RENDERER_API void Present(unsigned int uvsync = 0);

		// The size of the render target, in pixels.
		RENDERER_API SIZE	GetOutputSize() const { return m_outputSize; }

		/***************
		* D3D Accessors.
		***************/
		RENDERER_API ID3D11Device*					GetD3DDevice() const { return m_d3dDevice.Get(); }
		RENDERER_API ID3D11DeviceContext*			GetD3DDeviceContext() const { return m_d3dContext.Get(); }
		RENDERER_API IDXGISwapChain*				GetSwapChain() const { return m_swapChain.Get(); }
		RENDERER_API D3D_FEATURE_LEVEL				GetDeviceFeatureLevel() const { return m_d3dFeatureLevel; }
		RENDERER_API ID3D11RenderTargetView*		GetBackBufferRenderTargetView() const { return m_d3dRenderTargetView.Get(); }
		RENDERER_API ID3D11DepthStencilView*		GetDepthStencilView() const { return m_d3dDepthStencilView.Get(); }
		RENDERER_API D3D11_VIEWPORT					GetScreenViewport() const { return m_screenViewport; }

		/***************
		* D2D Accessors.
		***************/
		RENDERER_API IDWriteFactory*				GetDWriteFactory() const { return m_dwriteFactory.Get(); }
		RENDERER_API IWICImagingFactory*			GetWicImagingFactory() const { return m_wicFactory.Get(); }

	};

}