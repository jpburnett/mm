#include "global.h"

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_Start.s")
void TransitionFade_Start(void* thisx) {
    TransitionFade* this = (TransitionFade*)thisx;

    switch (this->fadeType) {
        case 0:
            break;
        case 1:
            this->fadeTimer = 0;
            this->fadeColor.a = this->fadeDirection != 0 ? 0xFF : 0;
            break;
        case 2:
            this->fadeColor.a = 0;
            break;
    }
    this->isDone = false;
}

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_Init.s")
void* TransitionFade_Init(void* thisx) {
    TransitionFade* this = (TransitionFade*)thisx;

    bzero(this, sizeof(*this));
    return this;
}

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_Destroy.s")
void TransitionFade_Destroy(void* thisx) {
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_Update.s")
// void TransitionFade_Update(void* thisx, s32 updateRate) {
//     s32 alpha;
//     s16 newAlpha;
//     TransitionFade* this = (TransitionFade*)thisx;

//     switch (this->fadeType) {
//         case 0:
//             break;
//         case 1:
//             this->fadeTimer += updateRate;
//             if (this->fadeTimer >= gSaveContext.transFadeDuration) {
//                 this->fadeTimer = gSaveContext.transFadeDuration;
//                 this->isDone = true;
//             }
//             alpha = (255.0f * this->fadeTimer) / ((void)0, gSaveContext.transFadeDuration);
//             this->fadeColor.a = (this->fadeDirection != 0) ? 255 - alpha : alpha;
//             break;
//         case 2:
//             newAlpha = this->fadeColor.a;
//             if (iREG(50) != 0) {
//                 if (iREG(50) < 0) {
//                     if (Math_StepToS(&newAlpha, 255, 255)) {
//                         iREG(50) = 150;
//                     }
//                 } else {
//                     Math_StepToS(&iREG(50), 20, 60);
//                     if (Math_StepToS(&newAlpha, 0, iREG(50))) {
//                         iREG(50) = 0;
//                         this->isDone = true;
//                     }
//                 }
//             }
//             this->fadeColor.a = newAlpha;
//             break;
//     }
// }

#pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_Draw.s")
// void TransitionFade_Draw(void* thisx, Gfx** gfxP) {
//     TransitionFade* this = (TransitionFade*)thisx;
//     Gfx* gfx;
//     Color_RGBA8_u32* color = &this->fadeColor;

//     if (color->a > 0) {
//         gfx = *gfxP;
//         gSPDisplayList(gfx++, &D_801D0CB0);
//         gDPSetPrimColor(gfx++, 0, 0, color->r, color->g, color->b, color->a);
//         gSPDisplayList(gfx++, &D_0E0002E0);
//         *gfxP = gfx;
//     }
// }

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_IsDone.s")
s32 TransitionFade_IsDone(void* thisx) {
    TransitionFade* this = (TransitionFade*)thisx;

    return this->isDone;
}

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_SetColor.s")
void TransitionFade_SetColor(void* thisx, u32 color) {
    TransitionFade* this = (TransitionFade*)thisx;

    this->fadeColor.rgba = color;
}


// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_fade/TransitionFade_SetType.s")
void TransitionFade_SetType(void* thisx, s32 type) {
    TransitionFade* this = (TransitionFade*)thisx;

    if (type == 1) {
        this->fadeType = 1;
        this->fadeDirection = 1;
    } else if (type == 2) {
        this->fadeType = 1;
        this->fadeDirection = 0;
    } else if (type == 3) {
        this->fadeType = 2;
    } else {
        this->fadeType = 0;
    }
}
