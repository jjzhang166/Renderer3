#pragma once
/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/


#include "RenderNode.h"
namespace Renderer
{
	class CRenderSet;
	
	class CView : public IRenderNode
	{
		friend class CShaderEffect;
		friend class CShaderPass;
		friend class CMaterial;
		friend class CRenderable;
	private:
		eRenderState m_CurrentState;
		//State Ids
		CShaderEffect* m_CurrentShaderEffects;
		CShaderPass* m_CurrentShaderPass;
		CMaterial* m_CurrentMaterial;
		CRenderable* m_CurrentRenderable;
		


		DirectX::XMFLOAT4X4 m_d3dViewMatrix;
		DirectX::XMFLOAT4X4 m_d3dProjMatrix;

		std::unique_ptr<CRenderSet> m_opaqueShaderEffects;
		std::unique_ptr<CRenderSet> m_transparentRenderables;

		std::vector<ID3D11RenderTargetView*> m_RTVs;
		ID3D11DepthStencilView* m_DepthView;
	public:
	
		/*std::vector<ILight*> m_Lights;
		std::vector<ID3D11RenderTargetView*> m_ShadowMaps;*/

		//Accessors
		inline CRenderSet* GetOpaqueShaderEffects() const { return m_opaqueShaderEffects.get(); }
		inline CRenderSet* GetTransparentRenderables() const { return m_transparentRenderables.get(); }
		inline DirectX::XMFLOAT4X4 GetViewMatrix() const { return m_d3dViewMatrix; }
		inline DirectX::XMFLOAT4X4 GetProjMatrix() const { return m_d3dProjMatrix; }
		inline std::vector<ID3D11RenderTargetView*> GetRTVs() const { return m_RTVs; }
		inline ID3D11DepthStencilView* GetDepthView() const { return m_DepthView; }

		//Mutators
		inline void SetOpaqueShaderEffects(CRenderSet* _newShaderEffects);
		inline void SetTransparentRenderables(CRenderSet* _newTransparentRenderables);
		inline void SetViewMatrix(DirectX::XMFLOAT4X4 _viewMatrix) { m_d3dViewMatrix = _viewMatrix; }
		inline void SetProjMatrix(DirectX::XMFLOAT4X4 _projMatrix) { m_d3dProjMatrix = _projMatrix; }
		inline void SetDepthView(ID3D11DepthStencilView* _DepthView)  {  m_DepthView= _DepthView; }

		inline void AddaRTV(ID3D11RenderTargetView* _mainRTV)  { m_RTVs.push_back(_mainRTV); }



		CView(DirectX::XMFLOAT4X4 d3dViewMatrix, DirectX::XMFLOAT4X4 d3dProjMatrix);
		~CView();
		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
		inline DirectX::XMFLOAT4X4 ViewMatrix() const { return m_d3dViewMatrix; }
		inline DirectX::XMFLOAT4X4 ProjectionMatrix() const { return m_d3dProjMatrix; }
	};
}
