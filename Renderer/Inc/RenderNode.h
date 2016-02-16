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
	enum eRenderState : unsigned int
	{
		APPLYVIEW = 0, APPLYSHADEREFFECT,APPLYMATERIAL,RENDERING

	};

	class IRenderNode
	{
	public:
		virtual void Begin(IRenderNode* pCurrentView) = 0;
		virtual void End(IRenderNode* pCurrentView) = 0;
		IRenderNode() {};
		virtual ~IRenderNode() {};
	};
}
