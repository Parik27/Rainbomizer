#include "TimeCycle.hh"
#include <cstdlib>
#include "logger.hh"
#include "base.hh"
#include "functions.hh"
#include "injector/calling.hpp"
#include "config.hh"
#include <chrono>
#include "fades.hh"
#include <algorithm>
#include <vector>
#include <random>
#include <time.h>

TimeCycleRandomizer *TimeCycleRandomizer::mInstance = nullptr;

static std::vector<int> weatherRegions = {0, 1, 2, 3, 4};
static int              lastForcedWeather;
static int              lastNewWeather = 0;

/*******************************************************/
void
ChangeForceWeather (short weather)
{
    if (weather == lastForcedWeather)
    {
        weather = lastNewWeather;
    }
    else
    {
        lastForcedWeather = weather;
        lastNewWeather = random (19);
        weather           = lastNewWeather;
    }
    injector::WriteMemory (0xC81318, weather); // ForcedWeatherType
    injector::WriteMemory (0xC81320, weather); // OldWeatherType
    injector::WriteMemory (0xC8131C, weather); // NewWeatherType
}

/*******************************************************/
void
ShuffleWeatherRegions (CVector *p1)
{
    CVector coors  = p1 ? *p1 : FindPlayerCoors ();
    short   region = 0;

    if (coors.x <= 1000.0f || coors.y <= 910.0f)
        {
            if (coors.x <= -850.0f || coors.x >= 1000.0f || coors.y <= 1280.0f)
                {
                    if (coors.x >= -1430.0f || coors.y <= -580.0f
                        || coors.y >= 1430.0f)
                        {
                            if (coors.x <= 250.0f || coors.x >= 3000.0f
                                || coors.y <= -3000.0f || coors.y >= -850.0f)
                                {
                                    region = 0;
                                }
                            else
                                {
                                    region = 1;
                                }
                        }
                    else
                        {
                            region = 2;
                        }
                }
            else
                {
                    region = 4;
                }
        }
    else
        {
            region = 3;
        }

    injector::WriteMemory<short> (0xC81314, weatherRegions[region]);
}

/*******************************************************/
void ChangeTimeCycleValues
(char *input, char *format, int *Amb_R, int *Amb_G, int *Amb_B, int *Amb_Obj_R,
    int *Amb_Obj_G, int *Amb_Obj_B, int *Dir_R, int *Dir_G, int *Dir_B,
    int *SkyTop_R, int *SkyTop_G, int *SkyTop_B, int *SkyBot_R, int *SkyBot_G,
    int *SkyBot_B, int *SunCore_R, int *SunCore_G, int *SunCore_B,
    int *SunCorona_R, int *SunCorona_G, int *SunCorona_B, float *SunSz,
    float *SprSz, float *SprBght, int *Shdw, int *LightShd, int *PoleShd,
    float *FarClp, float *FogSt, float *LightOnGround, int *LowCloudsR,
    int *LowCloudsG, int *LowCloudsB, int *BottomCloudR, int *BottomCloudG,
    int *BottomCloudB, float *WaterR, float *WaterG, float *WaterB,
    float *WaterA, float *Alpha1, float *RGB1R, float *RGB1G, float *RGB1B,
    float *Alpha2, float *RGB2R, float *RGB2G, float *RGB2B, float *CloudAlpha1,
    int *CloudAlpha2, int *CloudAlpha3,
    float *Illumination)
{
    *Amb_R = random (100);
    *Amb_G         = random (100);
    *Amb_B         = random (100);
    *Amb_Obj_R     = random (50, 255);
    *Amb_Obj_G     = random (50, 255);
    *Amb_Obj_B     = random (50, 255);
    *Dir_R         = 255;
    *Dir_G         = 255;
    *Dir_B         = 255;
    *SkyTop_R      = random (255);
    *SkyTop_G      = random (255);
    *SkyTop_B      = random (255);
    *SkyBot_R      = random (255);
    *SkyBot_G      = random (255);
    *SkyBot_B      = random (255);
    *SunCore_R     = random (255);
    *SunCore_G     = random (255);
    *SunCore_B     = random (255);
    *SunCorona_R   = random (255);
    *SunCorona_G   = random (255);
    *SunCorona_B   = random (255);
    *SunSz         = randomFloat (0.0f, 0.1f);
    *SprSz = randomFloat (0.0f, 0.1f);
    *SprBght       = randomFloat (0.0f, 0.1f);
    *Shdw          = random (255);
    *LightShd      = random (255);
    *PoleShd       = random (255);
    *FarClp        = random (100, 1500);
    *FogSt         = random (-22, 100);
    *LightOnGround = randomFloat (0.0f, 0.1f);
    *LowCloudsR    = random (255);
    *LowCloudsG    = random (255);
    *LowCloudsB    = random (255);
    *BottomCloudR  = random (255);
    *BottomCloudG  = random (255);
    *BottomCloudB  = random (255);
    *WaterR        = random (255);
    *WaterG        = random (255);
    *WaterB        = random (255);
    *WaterA        = random (30, 255);
    *Alpha1        = random (255);
    *RGB1R         = random (100);
    *RGB1G         = random (100);
    *RGB1B         = random (100);
    *Alpha2        = random (255);
    *RGB2R         = random (100);
    *RGB2G         = random (100);
    *RGB2B         = random (100);
    *CloudAlpha1   = random (255);
    *CloudAlpha2   = random (255);
    *CloudAlpha3   = random (255);
    *Illumination  = 0;
}

/*******************************************************/
void
TimeCycleRandomizer::Initialise ()
{
    if (!ConfigManager::ReadConfig ("TimeCycleRandomizer",
        std::pair("RandomizeTimeCycle", &m_Config.RandomizeTimeCycle),
        std::pair("ChangeOnFade", &m_Config.ChangeOnFade),
        std::pair("RandomizeWeather", &m_Config.RandomizeWeather)))
        return;

    if (m_Config.RandomizeWeather)
    {
        RegisterHooks ({{HOOK_JUMP, 0x72A4F0, (void *) &ChangeForceWeather},
                        {HOOK_JUMP, 0x72A640, (void *) &ShuffleWeatherRegions}});
        FadesManager::AddFadeCallback (Call<0x72A4F0>);
        
        FadesManager::AddFadeCallback ([] {
            std::shuffle (weatherRegions.begin (),
                          weatherRegions.end (), std::default_random_engine(time(NULL)));});
        FadesManager::AddFadeCallback (
            [] { lastNewWeather = random (19); });
    }

    if (m_Config.RandomizeTimeCycle)
    {
        RegisterHooks ({{HOOK_CALL, 0x5BBCE2, (void *) &ChangeTimeCycleValues}});
        if (m_Config.ChangeOnFade)
            FadesManager::AddFadeCallback (Call<0x5BBAC0>);
    }

    Logger::GetLogger ()->LogMessage ("Intialised TimeCycleRandomizer");
}

/*******************************************************/
void
TimeCycleRandomizer::DestroyInstance ()
{
    if (TimeCycleRandomizer::mInstance)
        delete TimeCycleRandomizer::mInstance;
}

/*******************************************************/
TimeCycleRandomizer *
TimeCycleRandomizer::GetInstance ()
{
    if (!TimeCycleRandomizer::mInstance)
        {
            TimeCycleRandomizer::mInstance = new TimeCycleRandomizer ();
            atexit (&TimeCycleRandomizer::DestroyInstance);
        }
    return TimeCycleRandomizer::mInstance;
}
