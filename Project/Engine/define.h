#pragma once


#define DEVICE  CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetDeviceContext()

#define CLONE(type) public: virtual type* Clone() { return new type(*this); }
#define CLONE_DISABLE(type) public: virtual type* Clone() { return nullptr; assert(nullptr); }

#define KEY_TAP	(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::TAP		
#define KEY_RELEASE(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::RELEASE
#define KEY_PRESSED(Key) CKeyMgr::GetInst()->GetKeyState(Key) == KEY_STATE::PRESSED

#define DT CTimeMgr::GetInst()->GetDeltaTime()



enum class COMPONENT_TYPE
{
	// update
	TRANSFORM,		// ��ġ, ũ��, ȸ��
	COLLIDER2D,		// 2���� �浹
	COLLIDER3D,		// 3���� �浹
	ANIMATOR2D,		// Sprite Animation
	ANIMATOR3D,		// Bone Sknning Animation
	LIGHT2D,		// 2���� ����
	LIGHT3D,		// 3���� ����
	CAMERA,			// Camera

	// render
	MESHRENDER,		// �⺻���� ������
	PARTICLESYSTEM, // ���� ������
	TILEMAP,		// 2���� Ÿ��
	LANDSCAPE,		// 3���� ����
	DECAL,			// ���� ������

	// custom
	SCRIPT,			

	END,
};


enum class RES_TYPE
{
	MESHDATA,
	MATERIAL,
	PREFAB,

	MESH,			// ����
	TEXTURE,		// �̹���
	SOUND,

	GRAPHICS_SHADER,
	COMPUTE_SHADER,

	END,
};

enum class CB_TYPE
{
	TRANSFORM, // b0


	END,
};