#ifndef UI_H
#define UI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

void UI_init(GLFWwindow* glfw_window);
void UI_destroy();

void UI_frame_begin();
void UI_frame_end();
void UI_render();

#endif // UI_H