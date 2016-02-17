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

namespace Renderer
{
	template<typename Shadertype>
	class CShaderHandle
	{
	public:
		RENDERER_API  ~CShaderHandle();
		RENDERER_API explicit  CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile);

	private:
		Microsoft::WRL::ComPtr<Shadertype> m_shader;
		CShaderHandle(CShaderHandle const&) = delete;
		CShaderHandle& operator=(CShaderHandle const&) = delete;
	};


	template<typename Shadertype>
	CShaderHandle<Shadertype>::~CShaderHandle()
	{
		if (m_shader)
		{
			m_shader.Reset();
		}
	}

	template<>
	CShaderHandle<ID3D11VertexShader>::CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile)
	{
		std::ifstream fin;
		fin.open(shaderFile, std::ios_base::binary);
		if (fin.is_open())
		{
			fin.seekg(0, std::ios_base::end);
			UINT byteCodeSize = (UINT)fin.tellg();
			char* byteCode = new char[byteCodeSize];
			fin.seekg(0, std::ios_base::beg);
			fin.read(byteCode, byteCodeSize);
			d3dDevice->CreateVertexShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
			fin.close();
			delete[] byteCode;
		}
	}

	template<>
	CShaderHandle<ID3D11PixelShader>::CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile)
	{
		std::ifstream fin;
		fin.open(shaderFile, std::ios_base::binary);
		if (fin.is_open())
		{
			fin.seekg(0, std::ios_base::end);
			UINT byteCodeSize = (UINT)fin.tellg();
			char* byteCode = new char[byteCodeSize];
			fin.seekg(0, std::ios_base::beg);
			fin.read(byteCode, byteCodeSize);
			d3dDevice->CreatePixelShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
			fin.close();
			delete[] byteCode;
		}
	}

	template<>
	CShaderHandle<ID3D11HullShader>::CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile)
	{
		std::ifstream fin;
		fin.open(shaderFile, std::ios_base::binary);
		if (fin.is_open())
		{
			fin.seekg(0, std::ios_base::end);
			UINT byteCodeSize = (UINT)fin.tellg();
			char* byteCode = new char[byteCodeSize];
			fin.seekg(0, std::ios_base::beg);
			fin.read(byteCode, byteCodeSize);
			d3dDevice->CreateHullShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
			fin.close();
			delete[] byteCode;
		}
	}


	template<>
	CShaderHandle<ID3D11DomainShader>::CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile)
	{
		std::ifstream fin;
		fin.open(shaderFile, std::ios_base::binary);
		if (fin.is_open())
		{
			fin.seekg(0, std::ios_base::end);
			UINT byteCodeSize = (UINT)fin.tellg();
			char* byteCode = new char[byteCodeSize];
			fin.seekg(0, std::ios_base::beg);
			fin.read(byteCode, byteCodeSize);
			d3dDevice->CreateDomainShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
			fin.close();
			delete[] byteCode;
		}
	}


	template<>
	CShaderHandle<ID3D11GeometryShader>::CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile)
	{
		std::ifstream fin;
		fin.open(shaderFile, std::ios_base::binary);
		if (fin.is_open())
		{
			fin.seekg(0, std::ios_base::end);
			UINT byteCodeSize = (UINT)fin.tellg();
			char* byteCode = new char[byteCodeSize];
			fin.seekg(0, std::ios_base::beg);
			fin.read(byteCode, byteCodeSize);
			d3dDevice->CreateGeometryShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
			fin.close();
			delete[] byteCode;
		}
	}


	template<>
	CShaderHandle<ID3D11ComputeShader>::CShaderHandle(ID3D11Device* d3dDevice, std::string shaderFile)
	{
		std::ifstream fin;
		fin.open(shaderFile, std::ios_base::binary);
		if (fin.is_open())
		{
			fin.seekg(0, std::ios_base::end);
			UINT byteCodeSize = (UINT)fin.tellg();
			char* byteCode = new char[byteCodeSize];
			fin.seekg(0, std::ios_base::beg);
			fin.read(byteCode, byteCodeSize);
			d3dDevice->CreateComputeShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
			fin.close();
			delete[] byteCode;
		}
	}



}

