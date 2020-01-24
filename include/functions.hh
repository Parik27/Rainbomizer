/*
    Rainbomizer - A (probably fun) Grand Theft Auto San Andreas Mod that
                  randomizes stuff
    Copyright (C) 2019 - Parik

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

 */

#include <cstdint>

#pragma once

/* These contain game functions that might be called by other modules */

struct cVehicleParams;
struct CBaseModelInfo;
struct CClumpModelInfo;
struct CVector;
struct CBox;
struct CColModel;
struct CPed;

enum eVehicleClass
{
    VEHICLE_AUTOMOBILE = 0,
    VEHICLE_MTRUCK,
    VEHICLE_QUAD,
    VEHICLE_HELI,
    VEHICLE_PLANE,
    VEHICLE_BOAT,
    VEHICLE_TRAIN,
    VEHICLE_FHELI,
    VEHICLE_FPLANE,
    VEHICLE_BIKE,
    VEHICLE_BMX,
    VEHICLE_TRAILER,
};

struct cVehicleParams
{
public:
    unsigned int   m_nVehicleSubclass;
    unsigned int   m_nVehicleClass;
    char           field_8;
    char           pad1[3];
    int            field_C;
    void *         m_pVehicle;
    void *         m_pTransmission;
    unsigned int   m_nModelType;
    float          m_fVelocity;
    short          m_nGasState;
    short          m_nBreakState;
    float          m_fVelocityAbsolute;
    float          m_fZVelocity;
    float          m_fVelocityPercentage;
    int            field_30;
    float          field_34;
    char           m_nCurrentGear;
    bool           m_bHandbrakeOn;
    char           pad2[2];
    float          m_fVelocityChangingPercentage;
    float          m_fWheelSpinForAudio;
    unsigned short m_nNumberOfGears;
    unsigned char  m_nWheelsOnGround;
    char           field_47;
    int            field_48;
};

struct CCarGenerator
{
    int16_t m_nModelId;
    void    DoInternalProcessing ();
    void    CheckForBlockage (int model_id);
};

struct Message
{
    int     m_pText;
    int16_t m_dwFlag;
    char    _pad1[2];
    int     m_dwTime;
    int     m_dwStartTime;
    int     m_dwNumber[6];
    char *  m_pString;
    char    m_bPreviousBrief;
    char    _pad2[3];
};

struct CHud
{
    static void SetMessage (char *str);
};

struct CMessages
{
    static char *AddMessage (char *string, int time, int16_t flags,
                             int8_t bAddToPreviousBrief);
};

struct CCarCtrl
{
    static void *CreateCarForScript (int modelId, float X, float Y, float Z,
                                     char a5);
    static int   ChooseModel (int *type);
};

struct CRunningScript
{
public:
    CRunningScript *m_pNext;
    CRunningScript *m_pPrev;
    char            m_szName[8];
    unsigned char * m_pBaseIP;
    unsigned char * m_pCurrentIP;
    unsigned char * m_apStack[8];
    unsigned short  m_nSP;

private:
    char _pad3A[2];

public:
    int  m_aLocalVars[32];
    int  m_anTimers[2];
    bool m_bIsActive;
    bool m_bCondResult;
    bool m_bUseMissionCleanup;
    bool m_bIsExternal;
    bool m_bTextBlockOverride;

private:
    char _padC9[3];

public:
    int            m_nWakeTime;
    unsigned short m_nLogicalOp;
    bool           m_bNotFlag;
    bool           m_bWastedBustedCheck;
    bool           m_bWastedOrBusted;

private:
    char _padD5[3];

public:
    unsigned char *m_pSceneSkipIP;
    bool           m_bIsMission;

private:
    char _padDD[3];

public:
    char *GetPointerToScriptVariable (int a2);
    void  CollectParameters (short num);
    bool  CheckName (const char *name);
    void  ProcessCommands1526to1537 (int opcode);
    char  ProcessCommands0to99 (int opcode);
    void  UpdateCompareFlag (char flag);
    int   EndThread ();

    static void SetCharCoordinates (CPed *ped, CVector pos, bool bWarpGang,
                                    bool bOffset);
};

struct CRunningScripts
{
    static CRunningScript *&pActiveScript;
    static bool             CheckForRunningScript (const char *thread);
};

struct CAudioEngine
{
    void PreloadMissionAudio (unsigned char slot, int id);
    bool GetMissionAudioLoadingStatus (unsigned char id);
    bool IsMissionAudioSampleFinished (unsigned char slot);
};

struct CKeyGen
{
    static int GetUppercaseKey (const char *string);
};

struct TKey
{
    char *pos;
    int   hash;
};

struct CKeyArray
{
    TKey *data;
    short size;
};

struct CData
{
    char *data;
    int   size;
};

struct CText
{
    CKeyArray tKeyMain;
    CData     tDataMain;
    CKeyArray tKeyMission;
    CData     tDataMission;

    void  Load (char a2);
    char *Get (char *key);
    char  LoadMissionText (const char *table);
};

struct CPool
{
    void **m_pObjects;
    void * GetAt (signed int handle, int size);
};

struct CPad
{
    static void DoCheats ();
};

struct CVehicleRecording
{
    static void SetPlaybackSpeed (void *a1, float a2);
};

struct CPopulation
{
    static void *AddPed (int type, int model, float *posn, bool unk);
};

struct CCarAI
{
    static void AddPoliceCarOccupants (void *vehicle, char a3);
};

struct CModelInfo
{
    static bool IsBoatModel (int modelId);
    static bool IsCarModel (int modelId);
    static bool IsTrainModel (int modelId);
    static bool IsHeliModel (int modelId);
    static bool IsPlaneModel (int modelId);
    static bool IsBikeModel (int modelId);
    static bool IsFakePlaneModel (int modelId);
    static bool IsMonsterTruckModel (int modelId);
    static bool IsQuadBikeModel (int modelId);
    static bool IsBmxModel (int modelId);
    static bool IsTrailerModel (int modelId);
    static bool IsPoliceModel (int modelId);
    static bool IsRCModel (int modelId);
    static int  LoadVehicleColours ();
    static int  GetMaximumNumberOfPassengersFromNumberOfDoors (int modelIndex);
};

struct CAEVehicleAudioEntity
{
    void ProcessTrainTrackSound (void *vehicle_info);
};

struct CAEAudioUtility
{
    static char GetBankAndSoundFromScriptSlotAudioEvent (int *      wavId,
                                                         int *      out_sfx,
                                                         int *      out_bank,
                                                         signed int slot);
};

struct BankLkup
{
    uint8_t  sfxIndex;
    char     pad[3];
    uint32_t m_dwOffset;
    uint32_t m_dwLength;
};

struct PakFile
{
    uint32_t soundBufferOffset;
    int32_t  sampleRate;
    int16_t  loopOffset;
    uint16_t soundHeadroom;
};

struct CAEMp3BankLoader
{
    void *    m_pBankSlotsInfo;
    BankLkup *m_pBankLkups;
    char *    m_pPakFileNames;
    uint16_t  m_nNumBankSlotInfos;
    uint16_t  m_nNumBankLkups;
    uint16_t  m_nNumPakFiles;

    int  GetLoopOffset (unsigned short sfxId, short bankSlotInfoId);
    char Initialise ();
};

struct CVector
{
    float x;
    float y;
    float z;
};

struct CGenericGameStorage
{
    static char *MakeValidSaveFileName (int saveNum);
    static char  GenericSave ();
};

struct CStats
{
    static void IncrementStat (short id, float val);
};

struct CBox
{
public:
    CVector m_vecMin;
    CVector m_vecMax;
};

struct CColData
{
    uint8_t   pad[0x10];
    uintptr_t m_pLines;
};

struct CColModel
{
    CBox      m_boundBox;
    uint8_t   m_Sphere[0x14];
    CColData *m_pColData;
};

struct CVehicle
{
    uint8_t  pad[0x22];
    uint16_t m_nModelIndex;
    int      GetVehicleAppearence ();
    void     AutomobilePlaceOnRoadProperly ();
    void     BikePlaceOnRoadProperly ();
    char     SetGearUp ();
};

struct CPed
{
    int   GiveWeapon (int weapon, int ammo, int slot);
    void *CCopPed__CCopPed (int type);
};

struct CPickups
{
    static int GenerateNewOne (float x, float y, float z, unsigned int modelId,
                               char pickupType, int ammo,
                               unsigned int moneyPerDay, char isEmpty,
                               char *message);
};

struct CBaseModelInfo
{
public:
    char             pad[0x14];
    CColModel *      m_pColModel;
    float            m_fDrawDistance;
    struct RwObject *m_pRwObject;
};

struct CClumpModelInfo : public CBaseModelInfo
{
public:
    CBox *GetBoundingBox ();
};

struct CLoadedCarGroup
{
public:
    unsigned short m_members[20];

private:
    unsigned short unk_2c;

public:
    int CountMembers ();
    int PickRandomCar (bool checkUsage, bool arg2);
};

struct CStreaming
{
    static CLoadedCarGroup *ms_nVehiclesLoaded;

    static int  GetDefaultCopCarModel (int a1);
    static void RequestModel (int model, int flags);
    static void LoadAllRequestedModels (bool bOnlyPriority);
    static void RemoveModel (int model);
    static void SetMissionDoesntRequireModel (int index);
    static void SetIsDeletable (int model);
    static void RemoveLeastUsedModel (int flags);
};

struct CStreamingInfo
{
public:
    short         m_nNextIndex; // ms_pArrayBase array index
    short         m_nPrevIndex; // ms_pArrayBase array index
    short         m_nNextIndexOnCd;
    unsigned char m_nFlags; // see eStreamingFlags
    unsigned char m_nImgId;
    unsigned int  m_nCdPosn;
    unsigned int  m_nCdSize;
    unsigned char m_nLoadState; // see eStreamingLoadState
private:
    char __pad[3];
};

struct RwRGBA
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct CMatrix
{
    CVector      right;
    unsigned int flags;
    CVector      up;
    unsigned int pad1;
    CVector      at;
    unsigned int pad2;
    CVector      pos;
    unsigned int pad3;

    void Attach (CMatrix *attach, char link);
    void SetRotateZOnly (float angle);
};

struct tTransmissionGear
{
    float m_fMaxVelocity;
    float m_fChangeUpVelocity;
    float m_fChangeDownVelocity;
};

class cTransmission
{
public:
    tTransmissionGear m_aGears[6];
    unsigned char     m_nDriveType;
    unsigned char     m_nEngineType;
    unsigned char     m_nNumberOfGears;
    char              field_4B;
    unsigned int      m_nHandlingFlags;
    float             m_fEngineAcceleration;
    float             m_fEngineInertia;
    float             m_fMaxGearVelocity;
    int               field_5C;
    float             m_fMinGearVelocity;
    float             m_fCurrentSpeed;
};

struct CWeaponInfo
{
public:
    unsigned int m_eWeaponFire;
    float        m_fTargetingRange;
    float        m_fFiringRange;
    long         m_nModel1;
    long         m_nModel2;
    unsigned int m_nWeaponSlot;
    unsigned int m_nFlags;
    unsigned int m_nAssocGroupId;
    short        m_nAmmoClipSize;
    short        m_nDamage;
    CVector      m_vecFireOffset;
    unsigned int m_nSkillLevel;
    unsigned int m_nRequiredStatValue;
    float        m_fAccuracy;
    float        m_fMoveSpeed;
    float        m_fAnimLoopStart;
    float        m_fAnimLoopEnd;
    float        m_fAnimFrameFire;
    float        m_fAnim2LoopStart;
    float        m_fAnim2LoopEnd;
    float        m_fAnim2FrameFire;
    float        m_fAnimBreakout;
    float        m_fSpeed;
    float        m_fRadius;
    float        m_fLifeSpan;
    float        m_fSpread;
    int          m_nUndefined;
};

struct tHandlingData
{
    int           m_nVehicleId;
    float         m_fMass;
    float         field_8;
    float         m_fTurnMass;
    float         m_fDragMult;
    CVector       m_vecCentreOfMass;
    unsigned char m_nPercentSubmerged;
    float         m_fBuoyancyConstant;
    float         m_fTractionMultiplier;
    cTransmission m_transmissionData;
    float         m_fBrakeDeceleration;
    float         m_fBrakeBias;
    char          m_bABS;
    char          field_9D;
    char          field_9E;
    char          field_9F;
    float         m_fSteeringLock;
    float         m_fTractionLoss;
    float         m_fTractionBias;
    float         m_fSuspensionForceLevel;
    float         m_fSuspensionDampingLevel;
    float         m_fSuspensionHighSpdComDamp;
    float         m_fSuspensionUpperLimit;
    float         m_fSuspensionLowerLimit;
    float         m_fSuspensionBiasBetweenFrontAndRear;
    float         m_fSuspensionAntiDiveMultiplier;
    float         m_fCollisionDamageMultiplier;
    int           m_nModelFlags;
    int           m_nHandlingFlags;
    float         m_fSeatOffsetDistance;
    unsigned int  m_nMonetaryValue;
    unsigned char m_nFrontLights;
    unsigned char m_nRearLights;
    unsigned char m_nAnimGroup;

    tHandlingData &
    operator= (const tHandlingData &rhs)
    {
        // Check for self-assignment!
        if (this == &rhs)
            return *this;

        this->m_fMass                     = rhs.m_fMass;
        this->m_fTurnMass                 = rhs.m_fTurnMass;
        this->m_fDragMult                 = rhs.m_fDragMult;
        this->m_vecCentreOfMass           = rhs.m_vecCentreOfMass;
        this->m_nPercentSubmerged         = rhs.m_nPercentSubmerged;
        this->m_fBuoyancyConstant         = rhs.m_fBuoyancyConstant;
        this->m_fTractionMultiplier       = rhs.m_fTractionMultiplier;
        this->m_transmissionData          = rhs.m_transmissionData;
        this->m_fBrakeDeceleration        = rhs.m_fBrakeDeceleration;
        this->m_fBrakeBias                = rhs.m_fBrakeBias;
        this->m_bABS                      = rhs.m_bABS;
        this->m_fSteeringLock             = rhs.m_fSteeringLock;
        this->m_fTractionLoss             = rhs.m_fTractionLoss;
        this->m_fTractionBias             = rhs.m_fTractionBias;
        this->m_fSuspensionForceLevel     = rhs.m_fSuspensionForceLevel;
        this->m_fSuspensionDampingLevel   = rhs.m_fSuspensionDampingLevel;
        this->m_fSuspensionHighSpdComDamp = rhs.m_fSuspensionHighSpdComDamp;
        this->m_fSuspensionUpperLimit     = rhs.m_fSuspensionUpperLimit;
        this->m_fSuspensionLowerLimit     = rhs.m_fSuspensionLowerLimit;
        this->m_fSuspensionBiasBetweenFrontAndRear
            = rhs.m_fSuspensionBiasBetweenFrontAndRear;
        this->m_fSuspensionAntiDiveMultiplier
            = rhs.m_fSuspensionAntiDiveMultiplier;
        this->m_fCollisionDamageMultiplier = rhs.m_fCollisionDamageMultiplier;
        this->m_nMonetaryValue             = rhs.m_nMonetaryValue;
        return *this;
    }
};

struct tBikeHandlingData
{
    unsigned char data[0x40];
};

struct tPlaneHandlingData
{
    unsigned char data[0x58];
};

struct tBoatHandlingData
{
    unsigned char data[0x3C];
};

struct cHandlingDataMgr
{
    int                unkFields[5];
    tHandlingData      vehicleHandling[210];
    tBikeHandlingData  bikeHandling[13];
    tPlaneHandlingData planeHandling[24];
    tBoatHandlingData  boatHandling[12];

    int LoadHandlingData ();
};

struct cSimpleTransform
{
    CVector m_vPosn;
    float   m_fAngle;
};

struct CMatrixLink
{
    CMatrix matrix;
};

struct CEntity
{
    int              vtable;
    cSimpleTransform m_SimpleTransform;
    CMatrixLink *    m_pMatrix;

    cSimpleTransform *GetPosition ();
    int               SetHeading (float heading);
};

template <typename T> struct ListItem_c
{
    T *next;
    T *prev;
};

struct FxSystemBP_c
{
    ListItem_c<FxSystemBP_c> m_link;
    uint32_t                 m_nKey;
    float                    m_fLength;
    float                    m_fLoop;
};

template <typename T> struct List_c
{
    T *      last;
    T *      first;
    uint32_t count;
};

struct FxManager_c
{
    List_c<FxSystemBP_c> SystemBlueprints;
};

CVector  FindPlayerCoors (int playerId = -1);
CPed *   FindPlayerPed (int playerId = -1);
CEntity *FindPlayerEntity (int playerId = -1);
float    Dist (CVector a, CVector b);

struct CGame
{
    static int Init3 (void *fileName);
};

CMatrix *RwFrameGetLTM (void *frame);

int   random (int max);
int   random (int min, int max);
float randomFloat (float min, float max);

extern CStreamingInfo * ms_aInfoForModel;
extern CBaseModelInfo **ms_modelInfoPtrs;
extern RwRGBA *         ms_vehicleColourTable;
extern int *            ScriptParams;
extern int *            ScriptSpace;
extern CPool *          ms_pPedPool;
extern CWeaponInfo *    aWeaponInfos;
