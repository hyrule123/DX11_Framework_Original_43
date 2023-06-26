#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "struct.fx"
#include "func.fx"


struct VS_IN
{
    float3 vPos : POSITION;
    float3 vNormal : NORMAL;    
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
};

VS_OUT VS_Std3D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;    
        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);            
    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
        
    return output;
}



// Rasterizer



float4 PS_Std3D(VS_OUT _in) : SV_Target
{        
    float4 vObjectColor = float4(0.4f, 0.4f, 0.4f, 1.f);    
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
       
    // Light �� ViewSpace ������ ����
    float3 vLightDir = mul(float4(g_Light3DBuffer[0].vWorldDir.xyz, 0.f), g_matView);
    
    // Diffuse Power
    float fPow = saturate(dot(-vLightDir, _in.vViewNormal));
            
    // Specular ���
    float3 vViewReflect = normalize(vLightDir + 2.f * (dot(-vLightDir, _in.vViewNormal)) * _in.vViewNormal);
    
    // ī�޶󿡼� �ȼ� ������ �ٶ󺸴� �ü� ����
    float3 vEye = -normalize(_in.vViewPos);
    
    // �ݻ籤 ����          
    float fRelfectPow = pow(saturate(dot(vViewReflect, vEye)), 10);        
    
    
    // ���� ����
    vOutColor.xyz = vObjectColor.xyz * g_Light3DBuffer[0].Color.vDiffuse.xyz * fPow 
                    + g_Light3DBuffer[0].Color.vSpecular.xyz * fRelfectPow
                    + g_Light3DBuffer[0].Color.vAmbient.xyz * vObjectColor.xyz;
    
    return vOutColor;
}

#endif
