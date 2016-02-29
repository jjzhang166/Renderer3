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
#include "..\Inc\View.h"


using namespace std;
using namespace DirectX;

namespace Renderer
{

	CInputLayoutManager& CRenderable::m_pInputLayoutManager = CInputLayoutManager::GetRef();

	CRenderable::CRenderable(CMaterial& material, XMFLOAT4X4 d3dWorldMatrix, string fileName) : m_Material(material),
		m_d3dWorldMatrix(d3dWorldMatrix),
		m_Depth(0.0f),
		m_uNumofIndices(0),
		m_uNumofVertices(0),
		m_uStartIndex(0),
		m_uStartVertex(0)
	{
		LoadModel(fileName);


		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(XMFLOAT4X4);
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		CRendererController::m_deviceResources->GetD3DDevice()->CreateBuffer(&bd, nullptr, m_d3dPerbjectConstantBuffer.GetAddressOf());
	}


	CRenderable::~CRenderable()
	{
		m_d3dVertexBuffer.Reset();
		m_d3dIndexBuffer.Reset();
		m_d3dPerbjectConstantBuffer.Reset();
		m_pInputLayoutManager.DeleteInstance();
	}

	void CRenderable::LoadModel(string& fileName)
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

					m_uNumofVertices = numOfVertices;

					m_d3dVertexBuffer.Reset();
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

					m_uNumofIndices = numOfIndices;
					m_d3dIndexBuffer.Reset();
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
		CView& view = (CView&)(*pCurrentView);
		view.m_CurrentRenderable = this;
		static auto deviceContextPtr = CRendererController::m_deviceResources->GetD3DDeviceContext();
		deviceContextPtr->IASetInputLayout(m_pInputLayoutManager.inputLayouts[CInputLayoutManager::eVertex_POSNORDIFF].Get());
		unsigned int strid = sizeof(Vertex);
		unsigned int offset = 0;
		deviceContextPtr->IASetVertexBuffers(0, 1, m_d3dVertexBuffer.GetAddressOf(), &strid, &offset);
		deviceContextPtr->IASetIndexBuffer(m_d3dIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		deviceContextPtr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		SetPerObjectData(view.ViewMatrix(), view.ProjectionMatrix());
		deviceContextPtr->DrawIndexed(m_uNumofIndices, 0, 0);

	}
	/*virtual*/ void CRenderable::End(IRenderNode* pCurrentView) /*final*/
	{


		static auto deviceContextPtr = CRendererController::m_deviceResources->GetD3DDeviceContext();
		deviceContextPtr->IASetInputLayout(nullptr);
		unsigned int strid = 0;
		unsigned int offset = 0;
		deviceContextPtr->IASetVertexBuffers(0, 0, nullptr, &strid, &offset);
		deviceContextPtr->IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);

		CView& view = (CView&)(*pCurrentView);
		view.m_CurrentRenderable = nullptr;

	}

	float Randomfloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}


	static float rotation = 180.0f;
	static float scale = 1.0f;


	void CRenderable::SetPerObjectData(DirectX::XMFLOAT4X4& view, DirectX::XMFLOAT4X4& proj)
	{
		auto vp = XMMatrixMultiply(XMLoadFloat4x4(&view), XMLoadFloat4x4(&proj));
		XMFLOAT3 up(0.0f, 1.0f, 0.0f);



#ifdef _DEBUG
		static bool callOnce = true;
		if (callOnce)
		{
			TwAddVarRW(CRendererController::m_TweakBar, "Rotation", TW_TYPE_FLOAT, &rotation, " min=0 max=360 step=0.5 group=Engine label='Rotation Angle' ");
			TwAddVarRW(CRendererController::m_TweakBar, "Scale", TW_TYPE_FLOAT, &scale, " min=0.1 max=10.0 step=0.05 group=Engine label='Scale' ");
			callOnce = false;
		}
#endif // _DEBUG

		XMStoreFloat4x4(&m_d3dWorldMatrix, XMMatrixScaling(scale, scale, scale) *  XMMatrixRotationAxis(XMLoadFloat3(&up), XMConvertToRadians(rotation)));

		auto mvp = XMMatrixMultiply(XMLoadFloat4x4(&m_d3dWorldMatrix), vp);
		XMFLOAT4X4 mvp4x4;
		XMStoreFloat4x4(&mvp4x4, mvp);


		auto deviceContextPtr = CRendererController::m_deviceResources->GetD3DDeviceContext();

		D3D11_MAPPED_SUBRESOURCE edit;
		deviceContextPtr->Map(m_d3dPerbjectConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &edit);
		memcpy(edit.pData, &mvp4x4, sizeof(mvp4x4));
		deviceContextPtr->Unmap(m_d3dPerbjectConstantBuffer.Get(), 0);


		deviceContextPtr->VSSetConstantBuffers(0, 1, m_d3dPerbjectConstantBuffer.GetAddressOf());
	}
}