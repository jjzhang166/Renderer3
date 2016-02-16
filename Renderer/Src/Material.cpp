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
#include "..\Inc\Material.h"
#include "..\Inc\RenderSet.h"


namespace Renderer
{
	CMaterial::CMaterial()
	{
	}


	CMaterial::~CMaterial()
	{
	}

	/*virtual*/ void CMaterial::Begin(IRenderNode* pCurrentView) /*final*/
	{

	}


	/*virtual*/ void CMaterial::End(IRenderNode* pCurrentView) /*final*/
	{

	}
	
	void CMaterial::AddtoShaderEffect(CShaderEffect* pShaderEffect)
	{

	}
}