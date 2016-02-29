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
	class CView;

	class CMaterial : public IRenderNode
	{
		friend class CView;
	private:
		struct CMaterialInput
		{
			enum eTextureType : unsigned int
			{
				DIFFUSE = 0, SPECULAR, EMISSIVE, NORMAL, HEIGHT,MAP_COUNT
			};
			std::unordered_map<unsigned int, ID3D11ShaderResourceView*> m_TextureMap;
			std::unordered_map<std::string, DirectX::XMFLOAT3> m_Vector3Map;
			std::unordered_map<std::string, float> m_FloatMap;
		} m_MaterialInput;

	public:
		std::unique_ptr<CRenderSet> m_Renderables;


		//Accessors
		inline ID3D11ShaderResourceView* GetMapSRV(unsigned int _mapType) { return m_MaterialInput.m_TextureMap[_mapType]; } // DIFFUSE = 0, SPECULAR, EMISSIVE, NORMAL, HEIGHT
		inline DirectX::XMFLOAT3& GetVector3(std::string _name) { return m_MaterialInput.m_Vector3Map[_name]; }
		inline float& GetFloat(std::string _name) { return m_MaterialInput.m_FloatMap[_name]; }
	//Mutators
	//DIFFUSE = 0, SPECULAR, EMISSIVE, NORMAL, HEIGHT
		void AddMap(unsigned int _mapType, ID3D11ShaderResourceView* _mapView); 
		void AddVector3(std::string _name, DirectX::XMFLOAT3 _value);
		void AddFloat(std::string _name, float _value);


		CMaterial();
		~CMaterial();
		virtual void Begin(IRenderNode* pCurrentView) final;
		virtual void End(IRenderNode* pCurrentView) final;
	};
}
