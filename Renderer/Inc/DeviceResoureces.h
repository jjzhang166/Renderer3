/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#pragma once

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the RENDERER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RENDERER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef RENDERER_EXPORTS
#define RENDERER_API __declspec(dllexport)
#else
#define RENDERER_API __declspec(dllimport)
#endif




namespace Renderer
{

	class CDeviceResoureces
	{
		void CreateDeviceIndependentResources();
		void CreateDeviceResources();
		void CreateWindowSizeDependentResources();

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
	public:
		RENDERER_API CDeviceResoureces(HWND _mainWindow, unsigned int _width = 1600u, unsigned int _height = 1024u);
		RENDERER_API ~CDeviceResoureces();

		RENDERER_API void ResizeWindow(unsigned int _width, unsigned int _height);
		// Default no vsync
		RENDERER_API void Present(unsigned int vsync = 0);

		// The size of the render target, in pixels.
		RENDERER_API SIZE	GetOutputSize() const { return m_outputSize; }

		/***************
		* D3D Accessors.
		***************/
		RENDERER_API ID3D11Device*				GetD3DDevice() const { return m_d3dDevice.Get(); }
		RENDERER_API ID3D11DeviceContext*		GetD3DDeviceContext() const { return m_d3dContext.Get(); }
		RENDERER_API IDXGISwapChain*				GetSwapChain() const { return m_swapChain.Get(); }
		RENDERER_API D3D_FEATURE_LEVEL			GetDeviceFeatureLevel() const { return m_d3dFeatureLevel; }
		RENDERER_API ID3D11RenderTargetView*		GetBackBufferRenderTargetView() const { return m_d3dRenderTargetView.Get(); }
		RENDERER_API ID3D11DepthStencilView*		GetDepthStencilView() const { return m_d3dDepthStencilView.Get(); }
		RENDERER_API D3D11_VIEWPORT				GetScreenViewport() const { return m_screenViewport; }

		/***************
		* D2D Accessors.
		***************/
		RENDERER_API IDWriteFactory*				GetDWriteFactory() const { return m_dwriteFactory.Get(); }
		RENDERER_API IWICImagingFactory*			GetWicImagingFactory() const { return m_wicFactory.Get(); }

	};

}