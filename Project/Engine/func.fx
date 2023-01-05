#ifndef _FUNC
#define _FUNC

#include "value.fx"

//노말맵이 존재하지 않는 이미지에 대한 빛 처리
void CalcLight2D(float3 _vWorldPos, inout tLightColor _Light)
{
    for (uint i = 0; i < g_buffer_count; ++i)
    {
        if (g_buffer_0[i].LightType == 0)
        {
            _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb;
            _Light.vAmbient.rgb += g_buffer_0[i].Color.vAmbient.rgb;
        }
        else if (g_buffer_0[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(g_buffer_0[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fPow = saturate(1.f - (fDistance / g_buffer_0[i].Radius));
        
            _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fPow;
        }
        else if (g_buffer_0[i].LightType == 2)
        {
            //1. 스포트라이트가 비추는 구역 구하기
            //광원이 향하는 방향의 위아래로 반반 각도씩
            float2 vLightPos = float2(g_buffer_0[i].vWorldPos.xy); //광원의 위치
            float2 vPixelPos = float2(_vWorldPos.xy); //픽셀의 위치
            
            float2 vDirFromLight = normalize(vPixelPos - vLightPos); //광원에서 픽셀로의 방향 벡터를 구한다.

            float2 vLightDir = float2(g_buffer_0[i].vWorldDir.xy); //광원이 바라보는 방향의 xy값을 가져온다.
            
            //내 위치와 스포트라이트 방향의 각도를 구하고, 빛을 비출 각도에서 빼준다.
            float AngleCos = dot(vLightDir, vDirFromLight);
            
            //1. 각이 바라보는 방향 90도 이내인지 확인.
            if (AngleCos > 0.f)
            {
                //2. acos를 통해 각도를 구한다.
                float Angle = acos(AngleCos);
                
                //3. 각도가 빛을 비추기로 설정한 범위 안인지 확인한다.
                if (Angle < g_buffer_0[i].Angle)
                {
                    //4. 각도에 따른 빛의 세기를 계산한다. 각도가 멀어질수록 빛의 세기가 약해지도록 계산해준다.
                    float fAnglePow = saturate(1.f - (Angle / g_buffer_0[i].Angle));
                    
                    //5. 거리에 따른 빛의 세기를 계산한다.
                    float fDistancePow = saturate(1.f - (distance(vLightPos, vPixelPos) / g_buffer_0[i].Radius));

                    _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fAnglePow * fDistancePow;
                }
            }
        }
    }
}

//노말맵이 존재하는 이미지에 대한 빛 처리
//픽셀의 위치, 픽셀의 방향(법선벡터), (출력용) 계산된 빛의 양
void CalcLight2DNormalMap(float3 _vWorldPos, float3 _vWorldDir, inout tLightColor _Light)
{
    for (uint i = 0; i < g_buffer_count; ++i)
    {
        if (g_buffer_0[i].LightType == 0)
        {
            float fDiffusePow = saturate(dot(-g_buffer_0[i].vWorldDir.xyz, _vWorldDir));
            _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fDiffusePow;                        
            _Light.vAmbient.rgb += g_buffer_0[i].Color.vAmbient.rgb;
        }
        else if (g_buffer_0[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(g_buffer_0[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            // 광원 중심에서 물체를 향하는 방향
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            float fDiffusePow = saturate(dot(-vLight, _vWorldDir));
            
            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fDistPow = saturate(1.f - (fDistance / g_buffer_0[i].Radius));
        
            _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fDiffusePow * fDistPow;
        }
        else if (g_buffer_0[i].LightType == 2)
        {

            float2 vLightPos = float2(g_buffer_0[i].vWorldPos.xy);      //광원의 위치
            float2 vPixelPos = float2(_vWorldPos.xy);                   //픽셀의 위치
            
            //1. 픽셀 위치와 광원 위치 사이의 방향 벡터를 구한다. 
            float2 vDirFromLight = normalize(vPixelPos - vLightPos); //광원에서 픽셀로의 방향 벡터를 구한다.

            float2 vLightDir = float2(g_buffer_0[i].vWorldDir.xy);      //광원이 바라보는 방향의 xy값을 가져온다.
            
            //2. 광원 → 픽셀 방향 벡터와 스포트라이트가 바라보는 방향 사이를 내적하여 사잇각의 코사인값을 구한다.
            float AngleCos = dot(vLightDir, vDirFromLight);
            
            //3. 코사인값이 0 이상일 떄(스포트라이트와의 각도가 90도 이내일 때)만 처리한다.
            if (AngleCos > 0.f)
            {         
                //4. 위 코사인값을 acos()를 통해서 각도로 환산한다.
                float Angle = acos(AngleCos);
                
                //5. 각도가 빛을 비추기로 설정한 범위 안인지 확인한다.
                if (Angle < g_buffer_0[i].Angle)
                {
                    //6. 각도에 따른 빛의 세기를 계산한다. 각도가 멀어질 수록 빛의 강도가 약해지도록 계산한다.
                    float fAnglePow = saturate(1.f - (Angle / g_buffer_0[i].Angle));
                    
                    //7. 거리에 따른 빛의 세기를 계산한다.
                    float fDistancePow = saturate(1.f - (distance(vLightPos, vPixelPos) / g_buffer_0[i].Radius));
                    
                    //8. 노말에 따른 빛의 세기를 계산한다.
                    //이 값은 각도가 아닌 '코사인값'을 그대로 사용하면 자연스럽게 빛의 강도가 계산이 된다.
                    float2 vNormalDir = float2(_vWorldDir.xy);
                    
                    //9. 7, 8, 9에서 계산된 빛의 세기를 광원의 빛의 세기에 곱해서 해당 픽셀에 비추는 빛의 양을 계산한다.
                    float fDiffusePow = saturate(dot(-vLightDir, vNormalDir));
                    
                    //10. 이 값을 누적시킨다( +=)
                    _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fAnglePow * fDistancePow * fDiffusePow;
                }
            }
        }
    }
}

#endif
