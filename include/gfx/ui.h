#ifndef UI_H
#define UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

#include <stdlib.h>

#include "types.h"
#include "log.h"
#include "io/io.h"

typedef struct UI
{
    GLFWwindow* window;
    u32 width;
    u32 height;
} UI;

UI* UI_create(GLFWwindow* window, const u32 width, const u32 height);
u32 UI_init(UI* ui);
void UI_init_fonts();

void UI_cleanup(UI* ui);
void UI_destroy(UI* ui);

void UI_frame_begin();
void UI_frame_end();
void UI_render(UI* ui);

#endif // UI_H