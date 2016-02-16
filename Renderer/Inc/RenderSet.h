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

#include "..\stdafx.h"

namespace Renderer
{
	class IRenderNode;
	class CRenderSet
	{
		typedef  bool(*CompareFunc)(const IRenderNode* const lhs, const IRenderNode* const rhs);
		std::list<IRenderNode*> m_set;
	public:
		CRenderSet();
		~CRenderSet();
		void AddtoHead(IRenderNode* node);
		void AddtoTail(IRenderNode* node);
		void Sort(CompareFunc sortMethod);
	};
}
