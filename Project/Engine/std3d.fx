#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "struct.fx"
#include "func.fx"


// Light3DInfo
static float3 g_LightDir = float3(1.f, -1.f, 0.f);
static float4 g_LightColor = float4(1.f, 1., 1.f, 1.f);
static float4 g_LightAmb = float4(0.15f, 0.15f, 0.15f, 1.f);



struct VS_IN
{
    float3 vPos : POSITION;
    float3 vNormal : NORMAL;    
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float fLightPow : FOG;
};

VS_OUT VS_Std3D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;    
    
    // ����Ʈ �ڻ��ι�Ģ
    float3 vWorldNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));
    float3 vLightDir = -normalize(g_LightDir);
    float fLightPow = saturate(dot(vWorldNormal, vLightDir)); // ���� ���Ⱑ ������ �������� �� ����
        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);    
    output.fLightPow = fLightPow;    
        
    return output;    
}

// Rasterizer

float4 PS_Std3D(VS_OUT _in) : SV_Target
{    
    
    float4 vObjectColor = float4(1.f, 0.f, 1.f, 1.f);
    
    // ��ü ���� x ���� ����
    float4 vOutColor = float4(_in.fLightPow * vObjectColor.xyz, 1.f);    
    
    // ��ü ���� x ȯ�汤
    vOutColor.xyz += g_LightAmb.xyz * vObjectColor.xyz;
        
    return vOutColor;

}

#endif
