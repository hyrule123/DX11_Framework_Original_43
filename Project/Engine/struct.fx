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
    float4  vWorldPos; // ��ƼŬ ��ġ
    float4  vWorldScale; // ��ƼŬ ũ��
    float4  vColor; // ��ƼŬ ����
    float4  vVelocity; // ��ƼŬ ���� �ӵ�
    float4  vForce; // ��ƼŬ�� �־��� ��

    float   Age; // ���� �ð�
    float   NomalizedAge; // ������ �����ð��� 0~1�� ����ȭ �� ��
    float   LifeTime; // ����
    float   Mass; // ����
};


struct tParticleModule
{
	// ���� ���
    float4 vSpawnColor;
    float4 vSpawnScale;
    float3 vBoxShapeScale;
    int iMaxParticleCount;
    float fSphereShapeRadius;
    int SpawnShapeType; // Sphere , Box

	// Color Change ���
    float4 vStartColor; // �ʱ� ����
    float4 vEndColor; // ���� ����

	// Scale Change ���
    float4 vStartScale; // �ʱ� ũ��
    float4 vEndScale; // ���� ũ��	

	// Module Check
    int ModuleCheck[3];
};

#endif
