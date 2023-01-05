#ifndef _FUNC
#define _FUNC

#include "value.fx"

//�븻���� �������� �ʴ� �̹����� ���� �� ó��
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
            //1. ����Ʈ����Ʈ�� ���ߴ� ���� ���ϱ�
            //������ ���ϴ� ������ ���Ʒ��� �ݹ� ������
            float2 vLightPos = float2(g_buffer_0[i].vWorldPos.xy); //������ ��ġ
            float2 vPixelPos = float2(_vWorldPos.xy); //�ȼ��� ��ġ
            
            float2 vDirFromLight = normalize(vPixelPos - vLightPos); //�������� �ȼ����� ���� ���͸� ���Ѵ�.

            float2 vLightDir = float2(g_buffer_0[i].vWorldDir.xy); //������ �ٶ󺸴� ������ xy���� �����´�.
            
            //�� ��ġ�� ����Ʈ����Ʈ ������ ������ ���ϰ�, ���� ���� �������� ���ش�.
            float AngleCos = dot(vLightDir, vDirFromLight);
            
            //1. ���� �ٶ󺸴� ���� 90�� �̳����� Ȯ��.
            if (AngleCos > 0.f)
            {
                //2. acos�� ���� ������ ���Ѵ�.
                float Angle = acos(AngleCos);
                
                //3. ������ ���� ���߱�� ������ ���� ������ Ȯ���Ѵ�.
                if (Angle < g_buffer_0[i].Angle)
                {
                    //4. ������ ���� ���� ���⸦ ����Ѵ�. ������ �־������� ���� ���Ⱑ ���������� ������ش�.
                    float fAnglePow = saturate(1.f - (Angle / g_buffer_0[i].Angle));
                    
                    //5. �Ÿ��� ���� ���� ���⸦ ����Ѵ�.
                    float fDistancePow = saturate(1.f - (distance(vLightPos, vPixelPos) / g_buffer_0[i].Radius));

                    _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fAnglePow * fDistancePow;
                }
            }
        }
    }
}

//�븻���� �����ϴ� �̹����� ���� �� ó��
//�ȼ��� ��ġ, �ȼ��� ����(��������), (��¿�) ���� ���� ��
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

            // ���� �߽ɿ��� ��ü�� ���ϴ� ����
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            float fDiffusePow = saturate(dot(-vLight, _vWorldDir));
            
            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fDistPow = saturate(1.f - (fDistance / g_buffer_0[i].Radius));
        
            _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fDiffusePow * fDistPow;
        }
        else if (g_buffer_0[i].LightType == 2)
        {

            float2 vLightPos = float2(g_buffer_0[i].vWorldPos.xy);      //������ ��ġ
            float2 vPixelPos = float2(_vWorldPos.xy);                   //�ȼ��� ��ġ
            
            //1. �ȼ� ��ġ�� ���� ��ġ ������ ���� ���͸� ���Ѵ�. 
            float2 vDirFromLight = normalize(vPixelPos - vLightPos); //�������� �ȼ����� ���� ���͸� ���Ѵ�.

            float2 vLightDir = float2(g_buffer_0[i].vWorldDir.xy);      //������ �ٶ󺸴� ������ xy���� �����´�.
            
            //2. ���� �� �ȼ� ���� ���Ϳ� ����Ʈ����Ʈ�� �ٶ󺸴� ���� ���̸� �����Ͽ� ���հ��� �ڻ��ΰ��� ���Ѵ�.
            float AngleCos = dot(vLightDir, vDirFromLight);
            
            //3. �ڻ��ΰ��� 0 �̻��� ��(����Ʈ����Ʈ���� ������ 90�� �̳��� ��)�� ó���Ѵ�.
            if (AngleCos > 0.f)
            {         
                //4. �� �ڻ��ΰ��� acos()�� ���ؼ� ������ ȯ���Ѵ�.
                float Angle = acos(AngleCos);
                
                //5. ������ ���� ���߱�� ������ ���� ������ Ȯ���Ѵ�.
                if (Angle < g_buffer_0[i].Angle)
                {
                    //6. ������ ���� ���� ���⸦ ����Ѵ�. ������ �־��� ���� ���� ������ ���������� ����Ѵ�.
                    float fAnglePow = saturate(1.f - (Angle / g_buffer_0[i].Angle));
                    
                    //7. �Ÿ��� ���� ���� ���⸦ ����Ѵ�.
                    float fDistancePow = saturate(1.f - (distance(vLightPos, vPixelPos) / g_buffer_0[i].Radius));
                    
                    //8. �븻�� ���� ���� ���⸦ ����Ѵ�.
                    //�� ���� ������ �ƴ� '�ڻ��ΰ�'�� �״�� ����ϸ� �ڿ������� ���� ������ ����� �ȴ�.
                    float2 vNormalDir = float2(_vWorldDir.xy);
                    
                    //9. 7, 8, 9���� ���� ���� ���⸦ ������ ���� ���⿡ ���ؼ� �ش� �ȼ��� ���ߴ� ���� ���� ����Ѵ�.
                    float fDiffusePow = saturate(dot(-vLightDir, vNormalDir));
                    
                    //10. �� ���� ������Ų��( +=)
                    _Light.vDiffuse.rgb += g_buffer_0[i].Color.vDiffuse.rgb * fAnglePow * fDistancePow * fDiffusePow;
                }
            }
        }
    }
}

#endif
