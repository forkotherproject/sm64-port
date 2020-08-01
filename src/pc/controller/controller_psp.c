#if defined(TARGET_PSP)

#include <stdbool.h>
#include <pspctrl.h>
#include <ultra64.h>

#include "controller_api.h"

static void controller_psp_init(void) {
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    // consider using sceCtrlSetIdleCancelThreshold
}

// n64 controls https://strategywiki.org/wiki/Super_Mario_64/Controls
// PSP -> N64 control mapping
//  SQUARE   -> B
//  CROSS    -> A
//  TRIANGLE -> Z Trigger
//  CIRCLE   -> Z Trigger
//  L Trig   -> L Trigger
//  R Trig   -> R Trigger
//  Analog   -> Move
//  Start    -> Start
//  DPad     -> Camera buttons
/*
#include <string.h>
*/
static void controller_psp_read(OSContPad *pad) {
    static SceCtrlData data;

    /*@Note: should we reset everything? */
    //memset(pad, 0, sizeof(OSContPad));
    //memset(&sce_pad, 0, sizeof(SceCtrlData));

    if (!sceCtrlPeekBufferPositive(&data, 1))
        return;

    /* flip and scale */
    pad->stick_x = (char)((((float)data.Lx)*0.625f)-80);
    pad->stick_y = (char)((((float)data.Ly)*0.625f)-80)*-1;

    if (data.Buttons & PSP_CTRL_START)
        pad->button |= START_BUTTON;
    if (data.Buttons & PSP_CTRL_SQUARE)
        pad->button |= B_BUTTON;
    if (data.Buttons & PSP_CTRL_CROSS)
        pad->button |= A_BUTTON;
    if (data.Buttons & PSP_CTRL_TRIANGLE)
        pad->button |= Z_TRIG;
    if (data.Buttons & PSP_CTRL_CIRCLE)
        pad->button |= Z_TRIG;
    if (data.Buttons & PSP_CTRL_LTRIGGER)
        pad->button |= L_TRIG;
    if (data.Buttons & PSP_CTRL_RTRIGGER)
        pad->button |= R_TRIG;
    if (data.Buttons & PSP_CTRL_UP)
        pad->button |= U_CBUTTONS;
    if (data.Buttons & PSP_CTRL_DOWN)
        pad->button |= D_CBUTTONS;
    if (data.Buttons & PSP_CTRL_LEFT)
        pad->button |= L_CBUTTONS;
    if (data.Buttons & PSP_CTRL_RIGHT)
        pad->button |= R_CBUTTONS;

}

struct ControllerAPI controller_psp = {
    controller_psp_init,
    controller_psp_read
};

#endif
