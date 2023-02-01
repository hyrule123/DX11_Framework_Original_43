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



#endif
