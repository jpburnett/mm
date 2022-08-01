/*
 * File: z_dm_hina.c
 * Overlay: ovl_Dm_Hina
 * Description: Boss mask cutscene objects
 */

#include "z_dm_hina.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmHina*)thisx)

void DmHina_Init(Actor* thisx, PlayState* play);
void DmHina_Destroy(Actor* thisx, PlayState* play);
void DmHina_Update(Actor* thisx, PlayState* play);
void DmHina_Draw(Actor* thisx, PlayState* play);

void func_80A1F470(DmHina* this, PlayState* play);
void DmHina_AwaitMessageBoxClosing(DmHina* this, PlayState* play);
void DmHina_SetupSubCamera(DmHina* this, PlayState* play);
void DmHina_MoveSubCamera(DmHina* this, PlayState* play);

const ActorInit Dm_Hina_InitVars = {
    ACTOR_DM_HINA,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BSMASK,
    sizeof(DmHina),
    (ActorFunc)DmHina_Init,
    (ActorFunc)DmHina_Destroy,
    (ActorFunc)DmHina_Update,
    (ActorFunc)DmHina_Draw,
};

void DmHina_Init(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    this->unk_180 = true;
    this->actionFunc = func_80A1F470;
    this->unk_158 = this->actor.world.pos.y;
    this->unk_148 = 0.0f;
    this->unk_15C = 1.0f;
    this->actor.focus.pos.x = this->actor.world.pos.x;
    this->actor.focus.pos.y = this->actor.world.pos.y;
    this->actor.focus.pos.z = this->actor.world.pos.z;
}

void DmHina_Destroy(Actor* thisx, PlayState* play) {
}

void func_80A1F470(DmHina* this, PlayState* play) {
    Player* player;

    player = GET_PLAYER(play);
    Math_SmoothStepToF(&this->unk_148, 0.6f, 0.5f, 0.05f, 0.001f);
    this->unk_154 = Math_SinS((play->gameplayFrames * 0x708)) * 8.0f;
    if ((player->stateFlags1 & 0x400) && (this->actor.xzDistToPlayer < 80.0f)) {
        this->unk_180 = false;
        this->unk_154 = 0.0f;
        this->actor.world.pos.y += 40.0f;
        this->actionFunc = DmHina_AwaitMessageBoxClosing;
    }
}

void DmHina_AwaitMessageBoxClosing(DmHina* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == 2) {
        this->timer = 2;
        this->actionFunc = DmHina_SetupSubCamera;
    }
}

void DmHina_SetupSubCamera(DmHina* this, PlayState* play) {
    this->timer--;
    if (this->timer == 0) {
        this->unk_180 = true;
        Cutscene_Start(play, &play->csCtx);
        this->subCamId = Play_CreateSubCamera(play);
        Play_CameraChangeStatus(play, 0, 1);
        Play_CameraChangeStatus(play, this->subCamId, 7);
        this->actionFunc = DmHina_MoveSubCamera;
    }
}

void DmHina_MoveSubCamera(DmHina* this, PlayState* play) {
    this->subCamEye.x = this->actor.world.pos.x + 100.0f;
    this->subCamEye.y = this->unk_158 + 260.0f;
    this->subCamEye.z = this->actor.world.pos.z + 100.0f;
    this->subCamAt.x = this->actor.world.pos.x;
    this->subCamAt.y = this->actor.world.pos.y + (this->unk_154 * this->unk_15C) + (40.0f * this->unk_15C);
    this->subCamAt.z = this->actor.world.pos.z;
    Play_CameraSetAtEye(play, this->subCamId, &this->subCamAt, &this->subCamEye);
    Math_SmoothStepToF(&this->actor.world.pos.y, this->unk_158 + 300.0f, 0.5f, 2.0f, 0.1f);
    if (((this->unk_158 + 240.0f) < this->actor.world.pos.y) && (this->unk_17E != 1)) {
        this->unk_17E = 1;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_OC_WHITE_OUT_INTO_KYOJIN);
    }
    Actor_PlaySfxAtPos(&this->actor, 0x219B);
}

void func_80A1F75C(DmHina* this, PlayState* play) {
    f32 var_ft5;
    s32 i;

    switch (this->unk_17E) {
        case 0:
            this->unk_17F = 0;
            this->unk_14C = 0.0f;
            break;
        case 1:
            Math_SmoothStepToF(&this->unk_14C, 1.0f, 0.4f, 0.05f, 0.001f);
            this->unk_17F = this->unk_14C * 255.0f;
            this->unk_150 = Math_SinS(play->state.frames * 0x1F40);
            var_ft5 = this->unk_14C * -255.0f;

            for (i = 0; i < 3; i++) {
                play->envCtx.lightSettings.ambientColor[i] = play->envCtx.lightSettings.fogColor[i] =
                    play->envCtx.lightSettings.diffuseColor1[i] = this->unk_14C * -255.0f;
            }
            play->envCtx.lightSettings.fogNear = this->unk_14C * (-500.0f);
            if (play->envCtx.lightSettings.fogNear < -0x12C) {
                play->roomCtx.currRoom.segment = NULL;
            }
            break;
    }
}

void DmHina_Update(Actor* thisx, PlayState* play) {
    DmHina* this = THIS;

    this->actionFunc(this, play);
    func_80A1F75C(this, play);
}

void func_80A1F9AC(DmHina* this, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    if (this->unk_17E != 0) {
        OPEN_DISPS(gfxCtx);

        func_8012C2DC(play->state.gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, (u8)(this->unk_14C * 100.0f) + 155, this->unk_17F);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, (u8)(this->unk_150 * 100.0f) + 50, 0);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrb1DL);
        Matrix_Translate(this->actor.world.pos.x,
                         this->actor.world.pos.y + (this->unk_154 * this->unk_15C) + (40.0f * this->unk_15C),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);
        Matrix_Scale(this->unk_14C * 20.0f, this->unk_14C * 20.0f, this->unk_14C * 20.0f, MTXMODE_APPLY);
        Matrix_RotateZF(Rand_ZeroFloat(6.2831855f), MTXMODE_APPLY);
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gLightOrbVtxDL);

        CLOSE_DISPS(gfxCtx);
    }
}

void DmHina_Draw(Actor* thisx, PlayState* play) {
    f32 temp_fa0;
    DmHina* this = THIS;

    if (this->unk_180) {
        Matrix_Translate(this->actor.world.pos.x,
                         this->actor.world.pos.y + (this->unk_154 * this->unk_15C) + (40.0f * this->unk_15C),
                         this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_RotateZYX(0, (s16)(play->gameplayFrames * 1000), 0, MTXMODE_APPLY);
        temp_fa0 = this->unk_148 * (1.0f - this->unk_14C) * this->unk_15C;
        Matrix_Scale(temp_fa0, temp_fa0, temp_fa0, MTXMODE_APPLY);
        switch (this->actor.params) {
            case 0:
                GetItem_Draw(play, GID_REMAINS_ODOLWA);
                break;
            case 1:
                GetItem_Draw(play, GID_REMAINS_GOHT);
                break;
            case 2:
                GetItem_Draw(play, GID_REMAINS_GYORG);
                break;
            case 3:
                GetItem_Draw(play, GID_REMAINS_TWINMOLD);
                break;
        }
        func_80A1F9AC(this, play);
    }
}
