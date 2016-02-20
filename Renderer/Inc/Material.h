/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#pragma once



#include "..\stdafx.h"
#include "RenderNode.h"

namespace Renderer
{
	class CRenderSet;
	class CShaderEffect;

	

	class CMaterial : IRenderNode
	{
		struct CMaterialInput
		{
			enum eTextureType : unsigned int
			{
				DIFFUSE = 0, SPECULAR, EMISSIVE, NORMAL, HEIGHT
			};
			std::unordered_map<unsigned int, ID3D11ShaderResourceView*> m_textureMap;
			std::unordered_map<std::string, DirectX::XMFLOAT3> m_vector3Map;
			std::unordered_map<std::string, float> m_floatMap;
		};

		std::unique_ptr<CRenderSet> m_shaderEffects;
		std::unique_ptr<CRenderSet> m_renderables;
	public:
		CMaterialInput m_materialInput;
		CMaterial();
		~CMaterial();
		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
		void AddtoShaderEffect(CShaderEffect* pShaderEffect);
	};
}
