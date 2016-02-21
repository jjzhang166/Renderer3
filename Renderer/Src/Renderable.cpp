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
#include "..\Inc\Renderable.h"
#include "..\Inc\InputLayoutManager.h"
#include "..\Inc\RendererController.h"


using namespace std;
using namespace DirectX;

namespace Renderer
{

	CInputLayoutManager& CRenderable::m_pInputLayoutManager = CInputLayoutManager::GetRef();

	CRenderable::CRenderable(CMaterial& material, XMFLOAT4X4 d3dWorldMatrix) :m_Material(material),
		m_d3dWorldMatrix(d3dWorldMatrix),
		m_Depth(0.0f),
		m_uNumofIndices(0),
		m_uNumofVertices(0),
		m_uStartIndex(0),
		m_uStartVertex(0)
	{
		m_pInputLayoutManager.Initilize();
	}


	CRenderable::~CRenderable()
	{
		m_pInputLayoutManager.DeleteInstance();
	}

	void CRenderable::LoadModel(std::string fileName)
	{
		ifstream bin(fileName, ios_base::binary);
		if (bin.is_open())
		{
			char header[8];
			bin.read(header, 8);
			if (strcmp(header, "FULLSAIL"))
			{
				uint8_t modelNameLength = 0;
				bin.read(reinterpret_cast<char*>(&modelNameLength), sizeof modelNameLength);


				string modelName;
				modelName.resize(modelNameLength);
				bin.read(&modelName[0], modelNameLength * sizeof(char));


				uint8_t numOfMeshes = 0;
				bin.read(reinterpret_cast<char*>(&numOfMeshes), sizeof numOfMeshes);



				for (size_t eachMesh = 0; eachMesh < numOfMeshes; eachMesh++)
				{
					uint32_t numOfVertices = 0;
					bin.read(reinterpret_cast<char*>(&numOfVertices), sizeof numOfVertices);

					vector<XMFLOAT3> pos;
					vector<XMFLOAT3> nor;
					vector<XMFLOAT3> uvs;
					pos.resize(numOfVertices);
					nor.resize(numOfVertices);
					uvs.resize(numOfVertices);

					bin.read(reinterpret_cast<char*>(pos.data()), sizeof(XMFLOAT3) *  numOfVertices);
					bin.read(reinterpret_cast<char*>(nor.data()), sizeof(XMFLOAT3) *  numOfVertices);
					bin.read(reinterpret_cast<char*>(uvs.data()), sizeof(XMFLOAT3) *  numOfVertices);

					vector<Vertex> verts;
					verts.resize(numOfVertices);
					for (size_t eachVert = 0; eachVert < numOfVertices; eachVert++)
					{
						verts[eachVert].pos = pos[eachVert];
						verts[eachVert].nor = nor[eachVert];
						verts[eachVert].uvw = uvs[eachVert];
					}


					auto d3dDevicePtr = CRendererController::m_deviceResources->GetD3DDevice();
					//Create Vertex Buffer
					UINT startVertex = 0;
					D3D11_BUFFER_DESC vertexBuffer_DESC;
					ZeroMemory(&vertexBuffer_DESC, sizeof(D3D11_BUFFER_DESC));
					D3D11_SUBRESOURCE_DATA vertexBufferData;
					ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));

					vertexBuffer_DESC.Usage = D3D11_USAGE_IMMUTABLE;
					vertexBuffer_DESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					vertexBuffer_DESC.ByteWidth = (unsigned int)verts.size()* sizeof(Vertex);
					vertexBufferData.pSysMem = verts.data();
					d3dDevicePtr->CreateBuffer(&vertexBuffer_DESC, &vertexBufferData, m_d3dVertexBuffer.GetAddressOf());


					vector<unsigned int> indices;
					uint32_t numOfIndices = 0;
					bin.read(reinterpret_cast<char*>(&numOfIndices), sizeof numOfIndices);

					indices.resize(numOfIndices);
					bin.read(reinterpret_cast<char*>(indices.data()), sizeof(unsigned int) *  numOfIndices);



					//Create Index Buffer
					D3D11_BUFFER_DESC inputBuffer_DESC;
					ZeroMemory(&inputBuffer_DESC, sizeof(D3D11_BUFFER_DESC));
					D3D11_SUBRESOURCE_DATA indexBufferData;
					ZeroMemory(&indexBufferData, sizeof(indexBufferData));
					inputBuffer_DESC.Usage = D3D11_USAGE_IMMUTABLE;
					inputBuffer_DESC.BindFlags = D3D11_BIND_INDEX_BUFFER;
					inputBuffer_DESC.ByteWidth = (unsigned int)indices.size()* sizeof(unsigned int);
					indexBufferData.pSysMem = indices.data();
					d3dDevicePtr->CreateBuffer(&inputBuffer_DESC, &indexBufferData, m_d3dIndexBuffer.GetAddressOf());




				}
			}
		}
	}


	/*virtual*/ void CRenderable::Begin(IRenderNode* pCurrentView) /*final*/
	{
		auto deviceContextPtr = CRendererController::m_deviceResources->GetD3DDeviceContext();
		deviceContextPtr->IASetInputLayout(m_pInputLayoutManager.inputLayouts[CInputLayoutManager::eVertex_POSNORDIFF].Get());

	}
	/*virtual*/ void CRenderable::End(IRenderNode* pCurrentView) /*final*/
	{
		auto deviceContextPtr = CRendererController::m_deviceResources->GetD3DDeviceContext();
		deviceContextPtr->IASetInputLayout(nullptr);
	}

}