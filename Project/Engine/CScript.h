#pragma once
#include "CComponent.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CGameObject.h"
#include "components.h"


class CScript :
    public CComponent
{
private:


public:
    virtual void finaltick() final {};

public:
    CScript();
    ~CScript();
};

