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
    
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};

VS_OUT VS_Std3D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;    
    
    // ����Ʈ �ڻ��ι�Ģ
    float3 vWorldNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));
    float3 vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    float3 vLightDir = -normalize(g_LightDir);    
    float fLightPow = saturate(dot(vWorldNormal, vLightDir)); // ���� ���Ⱑ ������ �������� �� ����
        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);    
    output.fLightPow = fLightPow;  
    
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = vViewNormal;
        
    return output;
}



// Rasterizer



float4 PS_Std3D(VS_OUT _in) : SV_Target
{        
    float4 vObjectColor = float4(0.4f, 0.4f, 0.4f, 1.f);    
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    // ��ü ���� x ���� ����
    if(1 == g_int_0)
    {
        vOutColor = float4(_in.fLightPow * vObjectColor.xyz, 1.f);
    }
    else
    {       
        // Light �� ViewSpace ������ ����
        float3 vLightDir = mul(float4(g_LightDir, 0.f), g_matView);
        
        // Diffuse Power
        float fPow = saturate(dot(-vLightDir, _in.vViewNormal));
                
        // Specular ���
        float3 vViewReflect = normalize(vLightDir + 2.f * (dot(-vLightDir, _in.vViewNormal)) * _in.vViewNormal);
        
        // ī�޶󿡼� �ȼ� ������ �ٶ󺸴� �ü� ����
        float3 vEye = -normalize(_in.vViewPos);        
        
        // �ݻ籤 ����        
        if(2 == g_int_0)
        {
            float fRelfectPow = pow(saturate(dot(vViewReflect, vEye)), 10);        
            vOutColor.xyz = vObjectColor.xyz * fPow + float3(0.3f, 0.3f, 0.3f) * fRelfectPow;
        }
        else
        {
            vOutColor.xyz = vObjectColor.xyz * fPow ;
        }        
    }
    
    
    // ��ü ���� x ȯ�汤
    vOutColor.xyz += g_LightAmb.xyz * vObjectColor.xyz;
        
    return vOutColor;
}

#endif
