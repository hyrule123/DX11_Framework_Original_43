#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer*     m_arrLayer[MAX_LAYER];

public:
    void tick();
    void finaltick(); 

public:
    void AddGameObject(CGameObject* _Object, int _iLayerIdx);
    CLayer* GetLayer(int _iLayerIdx) { assert(!(_iLayerIdx < 0)); return m_arrLayer[_iLayerIdx]; }


    CLONE(CLevel);
public:
    CLevel();
    ~CLevel();
};

