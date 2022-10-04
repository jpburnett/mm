#ifndef Z_EN_PAMERA_H
#define Z_EN_PAMERA_H

#include "global.h"
#include "objects/object_pamera/object_pamera.h"

struct EnPamera;

typedef void (*EnPameraActionFunc)(struct EnPamera*, PlayState*);
typedef void (*EnPameraSetupFunc)(struct EnPamera*, PlayState*);

typedef enum {
    /* 0 */ MOUTH_CLOSED,
    /* 1 */ MOUTH_OPEN
} mouthTexState;

typedef struct EnPamera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnPameraActionFunc actionFunc;
    /* 0x1D8 */ EnPameraSetupFunc setupFunc;
    /* 0x1DC */ Vec3s* pathPoints;
    /* 0x1E0 */ s32 pathIndex;
    /* 0x1E4 */ s32 pathPointsCount;
    /* 0x1E8 */ s32 pathId; 
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ Vec3s jointTable[PAMELA_LIMB_MAX];
    /* 0x27A */ Vec3s morphTable[PAMELA_LIMB_MAX];
    /* 0x304 */ Vec3s headRot;
    /* 0x30A */ Vec3s torsoRot; // Set, but not used
    /* 0x310 */ s16 eyebrowTexIndex;
    /* 0x312 */ s16 eyeTexIndex;
    /* 0x314 */ s16 mouthTexIndex;
    /* 0x316 */ s16 blinkTimer;
    /* 0x318 */ s16 cutscenes[2];
    /* 0x31C */ s16 hideInisdeTimer;
    /* 0x31E */ s16 unk_31E;
    /* 0x320 */ UNK_TYPE1 unk_320[0x2];
    /* 0x322 */ s16 unk_322;
    /* 0x324 */ u16 unk_324;
    /* 0x326 */ u16 unk_326;
} EnPamera; // size = 0x328

extern const ActorInit En_Pamera_InitVars;

#endif // Z_EN_PAMERA_H
