#ifndef UI_DB_H
#define UI_DB_H

/*
    UI_SDB (Song Database)
*/

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "io/log.h"
#include "util/consts.h"

#include "event/event.h"
#include "event/event_types.h"
#include "event/event_sed.inc"
#include "event/event_svu.inc"

#include "ui/ui_util.h"

typedef struct TEMP_SONG
{
    char* title;
    char* path;
} TEMP_SONG;

typedef struct UI_SDB
{
    TEMP_SONG temp_songs[8];
} UI_SDB;

UI_SDB* UI_SDB_create();
u32 UI_SDB_init(UI_SDB* ui_sdb);

void UI_SDB_render(UI_SDB* ui_sdb);

void UI_SDB_cleanup(UI_SDB* ui_sdb);
void UI_SDB_destroy(UI_SDB* ui_sdb);

#endif // UI_DB_H