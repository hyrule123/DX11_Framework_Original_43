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
    
    // 램버트 코사인법칙
    float3 vWorldNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));
    float3 vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    float3 vLightDir = -normalize(g_LightDir);    
    float fLightPow = saturate(dot(vWorldNormal, vLightDir)); // 빛의 세기가 음수로 내려가는 것 방지
        
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
    
    // 물체 색상 x 빛의 세기
    if(1 == g_int_0)
    {
        vOutColor = float4(_in.fLightPow * vObjectColor.xyz, 1.f);
    }
    else
    {       
        // Light 의 ViewSpace 에서의 방향
        float3 vLightDir = mul(float4(g_LightDir, 0.f), g_matView);
        
        // Diffuse Power
        float fPow = saturate(dot(-vLightDir, _in.vViewNormal));
                
        // Specular 계산
        float3 vViewReflect = normalize(vLightDir + 2.f * (dot(-vLightDir, _in.vViewNormal)) * _in.vViewNormal);
        
        // 카메라에서 픽셀 지점을 바라보는 시선 벡터
        float3 vEye = -normalize(_in.vViewPos);        
        
        // 반사광 세기        
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
    
    
    // 물체 색상 x 환경광
    vOutColor.xyz += g_LightAmb.xyz * vObjectColor.xyz;
        
    return vOutColor;
}

#endif
