#ifndef UI_DB_H
#define UI_DB_H

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "io/log.h"

#include "ui/ui_util.h"

#define UI_SDB_FILTER_SIZE 512

typedef struct UI_SDB
{
    char filter[UI_SDB_FILTER_SIZE];
} UI_SDB;

UI_SDB* UI_SDB_create();
u32 UI_SDB_init(UI_SDB* ui_sdb);

void UI_SDB_render(UI_SDB* ui_sdb);

void UI_SDB_cleanup(UI_SDB* ui_sdb);
void UI_SDB_destroy(UI_SDB* ui_sdb);

#endif // UI_DB_H