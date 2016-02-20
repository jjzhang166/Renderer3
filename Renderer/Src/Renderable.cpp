/***********************************************
* Filename:
* Date:
* Mod. Date:
* Mod. Initials:
* Author:
* Purpose:
************************************************/
#include "stdafx.h"
#include "..\Inc\Renderable.h"

namespace Renderer
{
	CRenderable::CRenderable( CMaterial& material) :m_Material(material)
	{
	}


	CRenderable::~CRenderable()
	{
	}
}