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
#include "db/song.h"

#include "ui/ui_util.h"

typedef struct UI_SED
{
    // Song being edited
    SONG* song;

    char title[MAX_SMALL_STR_SIZE];
} UI_SED;

UI_SED* UI_SED_create();
u32 UI_SED_init(UI_SED* ui_sed);

void UI_SED_render(UI_SED* ui_sed);

// Write update to UI_SED state from song
u32 UI_SED_update_from_song(UI_SED* ui_sed);
// Write update to song from UI_SED state
void UI_SED_update_to_song(UI_SED* ui_sed);
// Change the reference song instance
void UI_SED_set_song(UI_SED* ui_sed, SONG* song);

void UI_SED_cleanup(UI_SED* ui_sed);
void UI_SED_destroy(UI_SED* ui_sed);

#endif // UI_SED_H