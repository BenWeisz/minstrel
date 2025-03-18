#ifndef UI_SVU_H
#define UI_SVU_H

/*
    UI_SVU (Song View)
*/

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include <stdlib.h>

#include "types.h"
#include "io/log.h"

#include "event/event.h"
#include "event/event_types.h"
#include "event/event_svu.inc"

#include "db/song.h"

typedef struct UI_SVU
{
    bool is_open;

    SONG* song;
} UI_SVU;

UI_SVU* UI_SVU_create();
u32 UI_SVU_init(UI_SVU* ui_svu);

void UI_SVU_render(UI_SVU* ui_svu);

void UI_SVU_cleanup(UI_SVU* ui_svu);
void UI_SVU_destroy(UI_SVU* ui_svu);

void UI_SVU_event_handler(EVENT* event, void* context);

#endif // UI_SVU_H