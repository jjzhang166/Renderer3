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
#include "..\Inc\InputLayoutManager.h"
#include "..\Inc\RendererController.h"


namespace Renderer
{
	CInputLayoutManager* CInputLayoutManager::instancePtr = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	 CInputLayoutManager::inputLayouts[eVetex_MAX];

	CInputLayoutManager& CInputLayoutManager::GetRef()
	{
		if (!instancePtr)
		{
			instancePtr = new CInputLayoutManager;
			
		}
		return *instancePtr;
	}

	 void CInputLayoutManager::DeleteInstance()
	 {
		 for (size_t i = 0; i < eVetex_MAX; i++)
		 {
			 inputLayouts[i].Reset();
		 }
		 delete instancePtr;
		 instancePtr = nullptr;
	 }

	 CInputLayoutManager::CInputLayoutManager()
	{
		
	}

	 void CInputLayoutManager::Initilize()
	 {
		 for (auto& i : inputLayouts)
		 {
			 i.Reset();
		 }

		 auto theDevicePtr = CRendererController::m_deviceResources->GetD3DDevice();
		 //eVertex_POSNORDIFF
		 std::ifstream fin;
		 fin.open("CSO\\Vertex_POSNORDIFF.cso", std::ios_base::binary);
		 fin.seekg(0, std::ios_base::end);
		 UINT VSbyteCodeSize = (UINT)fin.tellg();
		 char* VSbyteCode = new char[VSbyteCodeSize];
		 fin.seekg(0, std::ios_base::beg);
		 fin.read(VSbyteCode, VSbyteCodeSize);
		 const UINT Vertex_POSNORDIFF_numofElements = 4;
		 D3D11_INPUT_ELEMENT_DESC vertexPNDSDesc[Vertex_POSNORDIFF_numofElements] =
		 {
			 { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			 { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			 { "TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			 { "PADDING", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		 };
		 theDevicePtr->CreateInputLayout(vertexPNDSDesc, Vertex_POSNORDIFF_numofElements, VSbyteCode,
			 VSbyteCodeSize, inputLayouts[eVertex_POSNORDIFF].GetAddressOf());
		 fin.close();
		 delete VSbyteCode;


		 ////eVertex_PosNorDiffSpecUVTan
		 //fin.open("CSO\\Vertex_PosNorDiffUVTan.cso", std::ios_base::binary);
		 //fin.seekg(0, std::ios_base::end);
		 //VSbyteCodeSize = (UINT)fin.tellg();
		 //VSbyteCode = new char[VSbyteCodeSize];
		 //fin.seekg(0, std::ios_base::beg);
		 //fin.read(VSbyteCode, VSbyteCodeSize);
		 //const UINT Vertex_PosNorDiffUVTan_numofElements = 5;
		 //D3D11_INPUT_ELEMENT_DESC vertexPNDSUTDesc[Vertex_PosNorDiffUVTan_numofElements] =
		 //{
			// { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "TANGENT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		 //};
		 //theDevicePtr->CreateInputLayout(vertexPNDSUTDesc, Vertex_PosNorDiffUVTan_numofElements, VSbyteCode,
			// VSbyteCodeSize, &inputLayouts[eVertex_PosNorDiffUVTan]);
		 //fin.close();
		 //delete VSbyteCode;

		 ////eVertex_PosNorDiffSpecUVTanBoneWeight
		 //fin.open("CSO\\Vertex_PosNorDiffUVTanBoneWeight.cso", std::ios_base::binary);
		 //fin.seekg(0, std::ios_base::end);
		 //VSbyteCodeSize = (UINT)fin.tellg();
		 //VSbyteCode = new char[VSbyteCodeSize];
		 //fin.seekg(0, std::ios_base::beg);
		 //fin.read(VSbyteCode, VSbyteCodeSize);
		 //const UINT Vertex_PosNorDiffUVTanBoneWeight_numofElements = 7;
		 //D3D11_INPUT_ELEMENT_DESC vertexPNDSUTDBWDesc[Vertex_PosNorDiffUVTanBoneWeight_numofElements] =
		 //{
			// { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "BONEIDS", 0, DXGI_FORMAT_R32G32B32A32_SINT, 2, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			// { "BONEWEIGHTS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 2, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		 //};
		 //theDevicePtr->CreateInputLayout(vertexPNDSUTDBWDesc, Vertex_PosNorDiffUVTanBoneWeight_numofElements, VSbyteCode,
			// VSbyteCodeSize, &inputLayouts[eVertex_PosNorDiffUVTanBoneWeight]);
		 //fin.close();
		 //delete VSbyteCode;
	 }


}