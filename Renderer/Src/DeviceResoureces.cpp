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
#include "..\Inc\DeviceResoureces.h"
using namespace DirectX;
using namespace Microsoft::WRL;




namespace Renderer
{
	CDeviceResoureces::CDeviceResoureces(HWND mainWindow,unsigned int uwidth, unsigned int uheight) :
		m_window(mainWindow),
		m_screenViewport(),
		m_d3dFeatureLevel(D3D_FEATURE_LEVEL_11_0),
		m_d3dRenderTargetSize({ static_cast<LONG>(uwidth), static_cast<LONG>(uheight) }),
		m_outputSize({ static_cast<LONG>(uwidth), static_cast<LONG>(uheight) })
	{
		m_outputSize.cx = max(m_outputSize.cx, 1);
		m_outputSize.cy = max(m_outputSize.cy, 1);
		CreateDeviceIndependentResources();
		CreateDeviceResources();
		CreateWindowSizeDependentResources();
	}



	void CDeviceResoureces::CreateDeviceResources()
	{
		// This flag adds support for surfaces with a different color channel ordering
		// than the API default. It is required for compatibility with Direct2D.
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		if (SdkLayersAvailable())
		{
			// If the project is in a debug build, enable debugging via SDK Layers with this flag.
			creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
		}
#endif

		// This array defines the set of DirectX hardware feature levels this app will support.
		// Note the ordering should be preserved.
		// Don't forget to declare your application's minimum required feature level in its
		// description.  All applications are assumed to support 9.1 unless otherwise stated.
		D3D_FEATURE_LEVEL requestLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};

	
		// Detect Dedicated GPU
		ComPtr<IDXGIFactory> factoryPtr;
		ComPtr<IDXGIAdapter> adapterPtr;
		std::vector<ComPtr<IDXGIAdapter>> adapters;

		CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&factoryPtr);

		unsigned int bestAdapterIndex = 0;
		SIZE_T bestMemSize = 0;

		for (unsigned int i = 0;
		factoryPtr->EnumAdapters(i, &adapterPtr) != DXGI_ERROR_NOT_FOUND;
			++i)
		{
			adapters.push_back(adapterPtr);
			DXGI_ADAPTER_DESC desc;
			adapterPtr->GetDesc(&desc);
			if (desc.DedicatedVideoMemory > bestMemSize)
			{
				bestAdapterIndex = i;
				bestMemSize = desc.DedicatedVideoMemory;
			}
		}


		HRESULT hr = D3D11CreateDevice(
			adapters[bestAdapterIndex].Get(),
			D3D_DRIVER_TYPE_UNKNOWN,
			0,							
			creationFlags,				
			requestLevels,				
			ARRAYSIZE(requestLevels),	
			D3D11_SDK_VERSION,			
			&m_d3dDevice,				
			&m_d3dFeatureLevel,			
			&m_d3dContext				
			);






	}

	void CDeviceResoureces::CreateDeviceIndependentResources()
	{
		//// Initialize the DirectWrite Factory.
		//AssertIfFailed(
		//	DWriteCreateFactory(
		//		DWRITE_FACTORY_TYPE_SHARED,
		//		__uuidof(IDWriteFactory),
		//		&m_dwriteFactory
		//		)
		//	);

		//// Initialize the Windows Imaging Component (WIC) Factory.
		//AssertIfFailed(
		//	CoCreateInstance(
		//		CLSID_WICImagingFactory,
		//		nullptr,
		//		CLSCTX_INPROC_SERVER,
		//		IID_PPV_ARGS(&m_wicFactory)
		//		)
		//	);
	}
	
	// These resources need to be recreated every time the window size is changed.
	void CDeviceResoureces::CreateWindowSizeDependentResources()
	{
		// Clear the previous window size specific context.
		ID3D11RenderTargetView* nullViews[] = { nullptr };
		m_d3dContext->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
		m_d3dRenderTargetView = nullptr;
		m_d3dDepthStencilView = nullptr;
		m_d3dContext->Flush();

		m_d3dRenderTargetSize.cx = m_outputSize.cx;
		m_d3dRenderTargetSize.cy = m_outputSize.cy;

		if (m_swapChain != nullptr)
		{
			// If the swap chain already exists, resize it.
			AssertIfFailed(
				m_swapChain->ResizeBuffers(
				2, // Double-buffered swap chain.
				lround(m_d3dRenderTargetSize.cx),
				lround(m_d3dRenderTargetSize.cy),
				DXGI_FORMAT_B8G8R8A8_UNORM,
				0)
				);

		}
		else
		{
			// Otherwise, create a new one using the same adapter as the existing Direct3D device.
			DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
			ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
			swapChainDesc.BufferDesc.Width = lround(m_d3dRenderTargetSize.cx);		// Match the size of the window.
			swapChainDesc.BufferDesc.Height = lround(m_d3dRenderTargetSize.cy);
			swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// This is the most common swap chain format.
			swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapChainDesc.SampleDesc.Count = 1;								// Don't use multi-sampling.
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = 1;									// Use double-buffering to minimize latency.
			swapChainDesc.Flags = 0;
			swapChainDesc.OutputWindow = m_window;
			swapChainDesc.Windowed = true;
			// This sequence obtains the DXGI factory that was used to create the Direct3D device above.
			ComPtr<IDXGIDevice> dxgiDevice;
			AssertIfFailed(
				m_d3dDevice.As(&dxgiDevice)
				);

			ComPtr<IDXGIAdapter> dxgiAdapter;
			AssertIfFailed(
				dxgiDevice->GetAdapter(&dxgiAdapter)
				);

			ComPtr<IDXGIFactory> dxgiFactory;
			AssertIfFailed(
				dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
				);

			AssertIfFailed(
				dxgiFactory->CreateSwapChain(
					m_d3dDevice.Get(),
					&swapChainDesc,
					&m_swapChain
					)
				);
		}

	
		// Create a render target view of the swap chain back buffer.
		ComPtr<ID3D11Texture2D> backBuffer;
		AssertIfFailed(
			m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))
			);

		AssertIfFailed(
			m_d3dDevice->CreateRenderTargetView(
				backBuffer.Get(),
				nullptr,
				&m_d3dRenderTargetView
				)
			);

		// Create a depth stencil view for use with 3D rendering if needed.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_R24G8_TYPELESS,
			lround(m_d3dRenderTargetSize.cx),
			lround(m_d3dRenderTargetSize.cy),
			1, // This depth stencil view has only one texture.
			1, // Use a single mipmap level.
			D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE
			);

		ComPtr<ID3D11Texture2D> depthStencil;
		AssertIfFailed(
			m_d3dDevice->CreateTexture2D(
				&depthStencilDesc,
				nullptr,
				&depthStencil
				)
			);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D, DXGI_FORMAT_D24_UNORM_S8_UINT);
		AssertIfFailed(
			m_d3dDevice->CreateDepthStencilView(
				depthStencil.Get(),
				&depthStencilViewDesc,
				&m_d3dDepthStencilView
				)
			);

		// Set the 3D rendering viewport to target the entire window.
		m_screenViewport = CD3D11_VIEWPORT(
			0.0f,
			0.0f,
			static_cast<FLOAT>(m_d3dRenderTargetSize.cx),
			static_cast<FLOAT>(m_d3dRenderTargetSize.cy)
			);

		m_d3dContext->RSSetViewports(1, &m_screenViewport);

		
	}

	void CDeviceResoureces::ResizeWindow(unsigned int uwidth, unsigned int uheight)
	{
		m_outputSize.cx = uwidth;
		m_outputSize.cy = uheight;
		CreateWindowSizeDependentResources();
	}
	void CDeviceResoureces::Present(unsigned int uvsync)
	{
		m_swapChain->Present(uvsync, 0);
	}
}