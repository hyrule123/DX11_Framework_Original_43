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
    
    float3      vWorldPos; // ������ ���� �����̽� ��ġ
    uint        LightType; // ���� Ÿ��(���⼺, ��, ����Ʈ)
    
    float3      vWorldDir; // ���� ������ ����
    float       Radius; // ���� �ݰ�(��Ÿ�)
    
    float       Angle; // ���� ����    
    int3         Padding;
};





#endif
