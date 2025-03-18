#ifndef UI_H
#define UI_H

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include <stdlib.h>

#include "types.h"
#include "io/log.h"
#include "io/io.h"

#include "ui/ui_sdb.h"
#include "ui/ui_sed.h"
#include "ui/ui_svu.h"

typedef struct UI
{
    GLFWwindow* window;
    u32 width;
    u32 height;

    UI_SDB* ui_sdb;
    UI_SED* ui_sed;
    UI_SVU* ui_svu;
} UI;

UI* UI_create(GLFWwindow* window, const u32 width, const u32 height);
u32 UI_init(UI* ui);

void UI_init_style();
void UI_init_fonts();

void UI_cleanup(UI* ui);
void UI_destroy(UI* ui);

void UI_frame_begin();
void UI_frame_end();
void UI_render(UI* ui);

#endif // UI_H