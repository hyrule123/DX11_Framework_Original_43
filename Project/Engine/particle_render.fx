#ifndef _PARTICLE_RENDER
#define _PARTICLE_RENDER

#include "value.fx"
#include "struct.fx"


// ========================
// Particle Render Shader
// mesh : RectMesh

// Parameter
// g_int_0 : Particle Index
// =========================

StructuredBuffer<tParticle> ParticleBuffer : register(t20);


struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

VS_OUT VS_ParticleRender(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;      
    
    // Local Mesh �� ������ ��ƼŬ ������ ���ϰ� ���� ��ġ�� �̵���Ų��.
    float3 vWorldPos = _in.vPos * ParticleBuffer[g_int_0].vWorldScale.xyz + ParticleBuffer[g_int_0].vWorldPos.xyz;
    
    // View, Proj ����� ���ؼ� NDC ��ǥ��� �̵���Ų��.
    float4 vViewPos = mul(float4(vWorldPos, 1.f), g_matView);    
    output.vPosition = mul(vViewPos, g_matProj);
    
    // UV ����
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_ParticleRender(VS_OUT _in) : SV_Target
{
    return float4(1.f, 0.f, 0.f, 1.f);
}


#endif
