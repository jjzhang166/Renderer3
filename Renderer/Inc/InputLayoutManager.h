#pragma once
/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/

namespace Renderer
{
	
	class CInputLayoutManager
	{

		
	private:
		static CInputLayoutManager* instancePtr;
		CInputLayoutManager();
	public:
		enum VertexFormat {
			eVertex_POSNORDIFF = 0,
			eVertex_PosNorDiffUVTan,
			eVertex_PosNorDiffUVTanBoneWeight,
			eVetex_MAX,
		};
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	 inputLayouts[eVetex_MAX];
		
		static CInputLayoutManager& GetRef();
		void Initilize();
		static void DeleteInstance();
	};
}
