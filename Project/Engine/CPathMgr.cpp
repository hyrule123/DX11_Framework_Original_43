#include "pch.h"
#include "CPathMgr.h"

#include "CEngine.h"

CPathMgr::CPathMgr()
	: m_szContentPath{}
{
}

CPathMgr::~CPathMgr()
{
}


void CPathMgr::init()
{
	GetCurrentDirectory(256, m_szContentPath);

	// ���������� ��
	int iLen = (int)wcslen(m_szContentPath);
	int SlashCount = 0;

	for (int i = iLen - 1; i >= 0; --i)
	{
		if (L'\\' == m_szContentPath[i])
		{
			++SlashCount;

			if (2 == SlashCount)
			{
				m_szContentPath[i] = 0;
				break;
			}
		}
	}

	// + bin\\content
	wcscat_s(m_szContentPath, L"\\OutputFile\\bin\\content\\");
}

