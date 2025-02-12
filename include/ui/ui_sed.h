#ifndef UI_SED_H
#define UI_SED_H

/*
    UI_SED (Song Editor)
*/

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "util/consts.h"
#include "io/log.h"

#include "event/event.h"
#include "event/event_types.h"
#include "event/event_sed.inc"

#include "db/song.h"

#include "ui/ui_util.h"

typedef struct UI_SED
{
    u32 width;
    u32 height;

    bool is_open;
    
    SONG* song;
} UI_SED;

UI_SED* UI_SED_create(u32 width, u32 height);
u32 UI_SED_init(UI_SED* ui_sed);

void UI_SED_render(UI_SED* ui_sed);

void UI_SED_cleanup(UI_SED* ui_sed);
void UI_SED_destroy(UI_SED* ui_sed);

// Event Handlers
void UI_SED_event_handler(EVENT* event, void* context);

#endif // UI_SED_H