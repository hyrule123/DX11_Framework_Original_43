#ifndef _FUNC
#define _FUNC

#include "value.fx"

void CalcLight2D(float3 _vWorldPos, inout tLightColor _Light)
{       
    for (int i = 0; i < iLightCount; ++i)
    {
        if (arrInfo[i].LightType == 0)
        {
            _Light.vDiffuse.rgb += arrInfo[i].Color.vDiffuse.rgb;
            _Light.vAmbient.rgb += arrInfo[i].Color.vAmbient.rgb;
        }
        else if (arrInfo[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(arrInfo[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fPow = saturate(1.f - (fDistance / arrInfo[i].Radius));
        
            _Light.vDiffuse.rgb += arrInfo[i].Color.vDiffuse.rgb * fPow;
        }
        else if (arrInfo[i].LightType == 2)
        {
            
        }
    }
}

void CalcLight2D(float3 _vWorldPos, float3 _vWorldDir, inout tLightColor _Light)
{
    for (int i = 0; i < iLightCount; ++i)
    {
        if (arrInfo[i].LightType == 0)
        {
            float fDiffusePow = saturate(dot(-arrInfo[i].vWorldDir.xyz, _vWorldDir));
            _Light.vDiffuse.rgb += arrInfo[i].Color.vDiffuse.rgb * fDiffusePow;                        
            _Light.vAmbient.rgb += arrInfo[i].Color.vAmbient.rgb;
        }
        else if (arrInfo[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(arrInfo[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            // 광원 중심에서 물체를 향하는 방향
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            float fDiffusePow = saturate(dot(-vLight, _vWorldDir));
            
            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fDistPow = saturate(1.f - (fDistance / arrInfo[i].Radius));
        
            _Light.vDiffuse.rgb += arrInfo[i].Color.vDiffuse.rgb * fDiffusePow * fDistPow;
        }
        else if (arrInfo[i].LightType == 2)
        {
            
        }
    }
}




#endif
