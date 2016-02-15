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

class CRenderSet;
class RENDERER_API IRenderable
{
public:
	IRenderable();
	~IRenderable();
	virtual void Begin() = 0;
	virtual void End() = 0;
	
private:

};

