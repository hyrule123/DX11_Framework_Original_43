#include "pch.h"
#include "CCameraMoveScript.h"

#include "CTransform.h"

CCameraMoveScript::CCameraMoveScript()
	: m_fCamSpeed(1.f)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::tick()
{
	// Ű �Է¿� ���� ī�޶� �̵�
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * m_fCamSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * m_fCamSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * m_fCamSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * m_fCamSpeed;
	}

	Transform()->SetRelativePos(vPos);
}
