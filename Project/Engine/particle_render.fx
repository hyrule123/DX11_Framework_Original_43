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
    uint iInstID : SV_InstanceID;
};

struct VS_OUT
{
    float3 vPos : POSITION;
    uint iInstID : SV_InstanceID;
};

VS_OUT VS_ParticleRender(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;      
     
    output.vPos = _in.vPos;
    output.iInstID = _in.iInstID;
    
    return output;
}

// GeometryShader ���
// 1. ���������� ����
// 2. ������ ó�� (ī�޶� �ٶ󺸴�..)
struct GS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
};

[maxvertexcount(6)]
void GS_ParticleRender (point VS_OUT _in[1], inout TriangleStream<GS_OUT> _outstream)
{    
    uint id = _in[0].iInstID;
    
    if (ParticleBuffer[id].Age < 0.f)
        return;

    float3 vParticleViewPos = mul(float4(ParticleBuffer[id].vWorldPos.xyz, 1.f), g_matView).xyz;
    float2 vParticleScale = ParticleBuffer[id].vWorldScale.xy;
    
    // 0 -- 1
    // |    |
    // 3 -- 2
    float3 NewPos[4] =
    {
        float3(vParticleViewPos.x - vParticleScale.x / 2.f, vParticleViewPos.y + vParticleScale.y / 2.f, vParticleViewPos.z),
        float3(vParticleViewPos.x + vParticleScale.x / 2.f, vParticleViewPos.y + vParticleScale.y / 2.f, vParticleViewPos.z),
        float3(vParticleViewPos.x + vParticleScale.x / 2.f, vParticleViewPos.y - vParticleScale.y / 2.f, vParticleViewPos.z),
        float3(vParticleViewPos.x - vParticleScale.x / 2.f, vParticleViewPos.y - vParticleScale.y / 2.f, vParticleViewPos.z)
    };
    
    GS_OUT output[4] = { (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT)0.f };
    
    output[0].vPosition = mul(float4(NewPos[0], 1.f), g_matProj);
    output[0].vUV = float2(0.f, 0.f);
    
    output[1].vPosition = mul(float4(NewPos[1], 1.f), g_matProj);
    output[1].vUV = float2(1.f, 0.f);
    
    output[2].vPosition = mul(float4(NewPos[2], 1.f), g_matProj);
    output[2].vUV = float2(1.f, 1.f);
    
    output[3].vPosition = mul(float4(NewPos[3], 1.f), g_matProj);
    output[3].vUV = float2(0.f, 1.f);
    
    
    // ���� ����
    _outstream.Append(output[0]);
    _outstream.Append(output[1]);
    _outstream.Append(output[2]);
    _outstream.RestartStrip();
    
    _outstream.Append(output[0]);
    _outstream.Append(output[2]);
    _outstream.Append(output[3]);
    _outstream.RestartStrip();
}


float4 PS_ParticleRender(GS_OUT _in) : SV_Target
{    
    return float4(1.f, 0.f, 0.f, 1.f);
}


#endif
