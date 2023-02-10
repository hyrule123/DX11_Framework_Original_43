#ifndef _STRUCT
#define _STRUCT


struct tLightColor
{
    float4 vDiffuse; // ���� ����
    float4 vAmbient; // �ֺ� ��(ȯ�� ��)
};

// LightInfo
struct tLightInfo
{
    tLightColor Color; // ���� ����
    
    float4      vWorldPos; // ������ ���� �����̽� ��ġ
    float4      vWorldDir; // ���� ������ ����
    
    uint        LightType; // ���� Ÿ��(���⼺, ��, ����Ʈ)
    float       Radius; // ���� �ݰ�(��Ÿ�)
    float       Angle; // ���� ����    
    int         Padding;
};


// Particle
struct tParticle
{
    float4  vLocalPos;
    float4  vWorldPos; // ��ƼŬ ��ġ
    float4  vWorldScale; // ��ƼŬ ũ��
    float4  vColor; // ��ƼŬ ����
    float4  vVelocity; // ��ƼŬ ���� �ӵ�
    float4  vForce; // ��ƼŬ�� �־��� ��

    float   Age; // ���� �ð�
    float   NomalizedAge; // ������ �����ð��� 0~1�� ����ȭ �� ��
    float   LifeTime; // ����
    float   Mass; // ����
    
    int     Active;
    int3    pad;
};


struct tParticleModule
{
	// ���� ���
    float4  vSpawnColor;
    float4  vSpawnScale;
    float3  vBoxShapeScale;    
    float   fSphereShapeRadius;
    int     SpawnShapeType; // Sphere , Box
    int     SpawnRate;
    int     Space;          // 0 World, 1 Local
    int     spawnpad;

	// Color Change ���
    float4  vStartColor; // �ʱ� ����
    float4  vEndColor; // ���� ����

	// Scale Change ���
    float4  vStartScale; // �ʱ� ũ��
    float4  vEndScale; // ���� ũ��	

	// Module Check
    int     Spawn;
    int     ColorChange;
    int     ScaleChange;
    int     dummy;
    
    int     iMaxParticleCount;
    int3    ipad;
};

#endif
