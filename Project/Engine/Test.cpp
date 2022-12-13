#include "pch.h"
#include "Test.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CResMgr.h"



CGameObject* g_Obj = nullptr;


void Init()
{
	
}

void Tick()
{
	g_Obj->tick();
	g_Obj->finaltick();
}

void Render()
{
	g_Obj->render();
}

void Release()
{
	delete g_Obj;
}
