/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#pragma once
#include "RenderNode.h"

namespace Renderer
{
	class CMaterial;
	class CInputLayoutManager;
	class CRenderable : public IRenderNode
	{
		friend class CView;
		struct _regAlign Vertex
		{
			float3 pos;
			float3 nor;
			float3 uvw;
		};

		CMaterial&			m_Material;
		DirectX::XMFLOAT4X4 m_d3dWorldMatrix;
		float				m_Depth;
		unsigned int		m_uStartVertex;
		unsigned int		m_uStartIndex;
		unsigned int		m_uNumofVertices;
		unsigned int		m_uNumofIndices;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_d3dVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_d3dIndexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_d3dPerbjectConstantBuffer;

		static CInputLayoutManager& m_pInputLayoutManager;
	public:
		CRenderable(CMaterial& material, DirectX::XMFLOAT4X4 d3dWorldMatrix, std::string fileName);
		~CRenderable();
		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
		void LoadModel(std::string& fileName);
		void SetPerObjectData(DirectX::XMFLOAT4X4& view, DirectX::XMFLOAT4X4& proj);
	};
}
