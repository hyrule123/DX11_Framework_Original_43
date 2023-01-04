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





#endif
