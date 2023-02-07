#ifndef _PARTICLE_UPDATE
#define _PARTICLE_UPDATE

#include "value.fx"
#include "struct.fx"

RWStructuredBuffer<tParticle>       ParticleBuffer : register(u0);
RWStructuredBuffer<int4>            ParticleSpawnCount : register(u1);
StructuredBuffer<tParticleModule>   ParticleModuleData : register(t20);

#define ParticleMaxCount g_int_0
#define SpawnCount ParticleSpawnCount[0].x
#define ModuleData ParticleModuleData[0]


[numthreads(128, 1, 1)]
void CS_ParticleUpdate(int3 _ID : SV_DispatchThreadID)
{
    // ������ ID �� ��ƼŬ���� �ִ� ���� �ѱ��� or ������ ��� ��ƼŬ�� ��Ȱ��ȭ ������ ���
    if (ParticleMaxCount <= _ID.x)
        return;
        
    tParticle particle = ParticleBuffer[_ID.x];
        
    // ��ƼŬ�� ��Ȱ��ȭ ������ ���
    if (particle.Age < 0.f)
    {
        // SpawnCount �� Ȯ��
        // ���� SpawnCount �� 0 �̻��̶��, ��ƼŬ�� Ȱ��ȭ��Ŵ      
        while (0 < SpawnCount)
        {
            int orgvalue = SpawnCount;
            int outvalue = 0;
            InterlockedCompareExchange(SpawnCount, orgvalue, SpawnCount - 1, outvalue);
            
            if(orgvalue == outvalue)
            {
                particle.Age = 0.f;
                particle.LifeTime = 10.f;
                break;
            }
        }
    }
    
    // ��ƼŬ�� Ȱ��ȭ�� ���
    else
    {
        // �ӵ��� ���� ��ƼŬ��ġ �̵�
        particle.vWorldPos += particle.vVelocity * g_DT;   
        
        // ��ƼŬ�� Age �� �ð��� ������Ŵ
        particle.Age += g_DT;
        
        // ��ƼŬ�� ������ ������, �ٽ� ��Ȱ��ȭ ���·� �ǵ���
        if(particle.LifeTime <= particle.Age)
        {
            particle.Age = -1.f;
        }
    }           
    
    
    // ������ ����
    ParticleBuffer[_ID.x] = particle;
}

#endif


