#include "z_en_hgo.h"

#define FLAGS 0x02000019

#define THIS ((EnHgo*)thisx)

void EnHgo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHgo_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD03EC(EnHgo* this);
void func_80BD0410(EnHgo* this, GlobalContext* globalCtx);
void func_80BD0434(EnHgo* this, GlobalContext* globalCtx);
void func_80BD049C(EnHgo* this);
void func_80BD04E0(EnHgo* this, GlobalContext* globalCtx);
void func_80BD064C(EnHgo* this);
void func_80BD0660(EnHgo* this, GlobalContext* globalCtx);
void func_80BD06FC(EnHgo* this, GlobalContext* globalCtx);
s32 func_80BD0898(EnHgo* this, GlobalContext* globalCtx);
s32 func_80BD0CF0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
s32 func_80BD0D38(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Actor* thisx);

extern FlexSkeletonHeader D_06012A58;
extern AnimationHeader D_0600B644;
extern Gfx D_0600F248[];
extern UNK_TYPE4 D_06011138;
extern UNK_TYPE4 D_06011938;
extern UNK_TYPE4 D_06012138;

/*
const ActorInit En_Hgo_InitVars = {
    ACTOR_EN_HGO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHgo),
    (ActorFunc)EnHgo_Init,
    (ActorFunc)EnHgo_Destroy,
    (ActorFunc)EnHgo_Update,
    (ActorFunc)EnHgo_Draw,
};
*/

ActorAnimationEntry D_80BD0EA0[] = {
    0x0600B644, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0xC0800000, 0x06013684, 0x3F800000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x060152EC, 0x3F800000, 0x00000000, 0x00000000, 0x02000000, 0x00000000,
    0x06015C70, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x060165F0, 0x3F800000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x06014220, 0x3F800000, 0x00000000, 0x00000000, 0x02000000, 0x00000000,
    0x06014A9C, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

static ColliderCylinderInit D_80BD0F48 = {
    0x0A000039, 0x20010000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000100, 0x0012002E, 0x00000000, 0x00000000,
};

static CollisionCheckInfoInit2 D_80BD0F74 = {
    0x00000000,
    0x00000000,
    0xFF000000,
};

static UNK_TYPE4* D_80BD0F80[] = {
    &D_06011138,
    &D_06011938,
    &D_06012138,
};

void EnHgo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;
    s32 pad;

    ActorShape_Init(&thisx->shape, 0.0f, func_800B3FC0, 36.0f);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06012A58, &D_0600B644, this->limbDrawTbl, this->transitionDrawTbl,
                     19);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80BD0F48);
    CollisionCheck_SetInfo2(&thisx->colChkInfo, NULL, &D_80BD0F74);
    thisx->targetMode = 6;
    this->unk_30C = 0;
    this->unk_30E = 0;
    this->unk_314 = 0;
    this->unk_310 = 0;
    this->unk_312 = 0;
    if (gSaveContext.weekEventReg[75] & 0x20 || gSaveContext.weekEventReg[52] & 0x20) {
        func_80BD049C(thisx);
    } else {
        thisx->draw = NULL;
        func_80BD03EC(this);
    }
}

void EnHgo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80BD03EC(EnHgo* this) {
    this->actor.flags &= -2;
    this->actionFunc = &func_80BD0410;
}

void func_80BD0410(EnHgo* this, GlobalContext* globalCtx) {
}

void func_80BD0420(EnHgo* this) {
    this->actionFunc = func_80BD0434;
}

void func_80BD0434(EnHgo* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.focus.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.focus.pos.z;
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider);
}

void func_80BD049C(EnHgo* this) {
    func_800BDC5C(&this->skelAnime, &D_80BD0EA0, 0);
    this->actionFunc = func_80BD04E0;
}

void func_80BD04E0(EnHgo* this, GlobalContext* globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        if (func_8012403C(globalCtx) == 0xC) {
            if (!(this->unk_310 & 4)) {
                this->unk_310 |= 4;
                func_801518B0(globalCtx, 0x15A5, &this->actor);
                this->unk_314 = 0x15A5;

            } else {
                func_801518B0(globalCtx, 0x15A7, &this->actor);
                this->unk_314 = 0x15A7;
            }
        } else if (gSaveContext.playerForm == 4) {
            if (!(this->unk_310 & 1)) {
                this->unk_310 |= 1;
                func_801518B0(globalCtx, 0x158F, &this->actor);
                this->unk_314 = 0x158F;
            } else {
                func_801518B0(globalCtx, 0x1593, &this->actor);
                this->unk_314 = 0x1593;
            }
        } else {
            if (!(this->unk_310 & 2)) {
                this->unk_310 |= 2;
                func_801518B0(globalCtx, 0x1595, &this->actor);
                this->unk_314 = 0x1595;
            } else {
                func_801518B0(globalCtx, 0x1598, &this->actor);
                this->unk_314 = 0x1598;
            }
        }
        func_80BD064C(this);
    } else {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void func_80BD064C(EnHgo* this) {
    this->actionFunc = func_80BD0660;
}

void func_80BD0660(EnHgo* this, GlobalContext* globalCtx) {

    switch (func_80152498(&globalCtx->msgCtx)) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            func_80BD06FC(this, globalCtx);
            break;
        case 6:
            if (func_80147624(globalCtx)) {
                func_80BD049C(this);
            }
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0xA, 0x71C, 0xB6);
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void func_80BD06FC(EnHgo* this, GlobalContext* globalCtx) {
    if (func_80147624(globalCtx)) {
        switch (this->unk_314) {
            case 0x1590:
                func_801518B0(globalCtx, 0x1590, &this->actor);
                this->unk_314 = 0x1590;
                break;
            case 0x1591:
                if ((gSaveContext.weekEventReg[14]) & 4) {
                    func_801518B0(globalCtx, 0x1591, &this->actor);
                    this->unk_314 = 0x1591;
                    break;
                }
                func_801518B0(globalCtx, 0x1592, &this->actor);
                this->unk_314 = 0x1592;
                break;
            case 0x1592:
                func_801518B0(globalCtx, 0x1592, &this->actor);
                this->unk_314 = 0x1592;
                break;
            case 0x1594:
                func_801518B0(globalCtx, 0x1594U, &this->actor);
                this->unk_314 = 0x1594;
                break;
            case 0x1596:
                func_801518B0(globalCtx, 0x1596U, &this->actor);
                this->unk_314 = 0x1596;
                break;
            case 0x1597:
                func_801518B0(globalCtx, 0x1597, &this->actor);
                this->unk_314 = 0x1597;
                break;
            case 0x1599:
                func_801518B0(globalCtx, 0x1599, &this->actor);
                this->unk_314 = 0x1599;
                break;
            case 0x15A6:
                func_801518B0(globalCtx, 0x15A6, &this->actor);
                this->unk_314 = 0x15A6;
                break;
            case 0x15A7:
                func_801518B0(globalCtx, 0x15A7, &this->actor);
                this->unk_314 = 0x15A7;
                break;
            case 0x158F:
                func_801477B4(globalCtx);
                func_80BD049C(this);
                break;
        }
    }
}

// TODO: Finish this one
#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hgo_0x80BD02B0/func_80BD0898.asm")
// s32 func_80BD0898(EnHgo* this, GlobalContext* globalCtx) {
//     u32 sp44;
//     u32 actionIndex;

//     if (func_800EE29C(globalCtx, 0x1E6U) != 0) {
//         actionIndex = func_800EE200(globalCtx, 0x1E6U);
//         if (this->unk_316 != globalCtx->csCtx.npcActions[actionIndex]->startFrame) {
//             this->unk_316 = globalCtx->csCtx.npcActions[actionIndex]->unk0;
//             switch (globalCtx->csCtx.npcActions[actionIndex]->unk0) {
//                 case 0:
//                     this->unk_218 = 0;
//                     func_800BDC5C(&this->skelAnime, D_80BD0EA0, 0);
//                     goto block_23;
//                 case 1:
//                     this->actor.draw = EnHgo_Draw;
//                     this->unk_218 = 1;
//                     func_800BDC5C(&this->skelAnime, D_80BD0EA0, 1);
//                     goto block_23;
//                 case 2:
//                     this->unk_218 = 2;
//                     func_800BDC5C(&this->skelAnime, D_80BD0EA0, 2);
//                     goto block_23;
//                 case 3:
//                     this->unk_218 = 3;
//                     func_800BDC5C(&this->skelAnime, D_80BD0EA0, 3);
//                     goto block_23;
//                 case 4:
//                     this->unk_218 = 4;
//                     func_800BDC5C(&this->skelAnime, D_80BD0EA0, 4);
//                     goto block_23;
//                 case 5:
//                     this->unk_218 = 5;
//                     func_800BDC5C(&this->skelAnime, D_80BD0EA0, 5);
//                     goto block_23;
//             }
//         } else {
//             if (func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) {
//                 if (this->unk_218 != 1) {
//                     if (this->unk_218 != 2) {
//                         if (this->unk_218 != 5) {

//                         } else {
//                             this->unk_218 = 6;
//                             func_800BDC5C(&this->skelAnime, D_80BD0EA0, 6);
//                         }
//                     } else {
//                         this->unk_218 = 3;
//                         func_800BDC5C(&this->skelAnime, D_80BD0EA0, 3);
//                     }
//                 } else if ((func_801378B8(&this->skelAnime, this->skelAnime.animFrameCount) != 0) &&
//                            (this->unk_312 == 0)) {
//                     this->unk_312 = 1;
//                     if ((gSaveContext.sceneSetupIndex == 0) &&
//                         ((globalCtx->csCtx.unk_12 == 2) || globalCtx->csCtx.unk_12 == 4)) {
//                         Audio_PlayActorSound2(&this->actor, 0x6961U);
//                     }
//                 }
//             }
//         }
//     block_23:
//         func_800EDF24(&this->actor, globalCtx, sp44);
//         return 1;
//     }
//     if ((globalCtx->csCtx.state == 0) && (((gSaveContext.weekEventReg[50]) & 0x20) != 0) &&
//         (func_80BD0410 == this->actionFunc)) {
//         this->actor.shape.rot.y = this->actor.world.rot.y;
//         Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0xC6, this->actor.focus.pos.x, this->actor.focus.pos.y,
//                     this->actor.focus.pos.z, 7, 0, 0, 0x7F5A);
//         func_80BD0420(this);
//     }
//     this->unk_316 = 0x63;
//     return 0;
// }

void func_80BD0B8C(EnHgo* this, GlobalContext* globalCtx) {
    func_800E9250(globalCtx, &this->actor, &this->unk_300, &this->unk_306, this->actor.focus.pos);
    if (this->unk_30E >= 3) {
        this->unk_30E--;
    } else if (this->unk_30E == 2) {
        this->unk_30C = 1;
        this->unk_30E = 1;
    } else if (this->unk_30E == 1) {
        this->unk_30C = 2;
        this->unk_30E = 0;
    } else {
        this->unk_30C = 0;
        this->unk_30E = 0x3C;
    }
}

void EnHgo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;
    s32 pad;

    this->actionFunc(this, globalCtx);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_80BD0898(this, globalCtx)) {
        func_800E8F08(&this->unk_300, &this->unk_306);
    } else {
        if (this->actionFunc != func_80BD0410) {
            if (this->actionFunc != func_80BD0434) {
                Collider_UpdateCylinder(this, &this->collider);
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider);
                func_80BD0B8C(this, globalCtx);
            }
        }
    }
}

s32 func_80BD0CF0(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnHgo* this = THIS;

    if (limbIndex == 0xB) {
        rot->x += this->unk_300.y;
        rot->z += this->unk_300.x;
    }
    return 0;
}

s32 func_80BD0D38(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Actor* thisx) {
    EnHgo* this = THIS;

    if (limbIndex == 0xB) {
        SysMatrix_CopyCurrentState(&this->unk_1D8);
        SysMatrix_GetStateTranslation(&this->actor.focus);
    }
}

void EnHgo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHgo* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80BD0F80[this->unk_30C]));
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount,
                     func_80BD0CF0, func_80BD0D38, this);
    SysMatrix_SetCurrentState(&this->unk_1D8);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_0600F248);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
