#pragma once

class CGameObjectEx;

class CEditorObjMgr
	: public CSingleton<CEditorObjMgr>
{
	SINGLE(CEditorObjMgr);
private:
	vector<CGameObjectEx*> m_vecDebugShape;

public:
	void init();
	void progress();

private:
	void tick();
	void render();
};

