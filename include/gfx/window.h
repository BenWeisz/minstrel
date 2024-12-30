#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "types.h"
#include "log.h"
#include "ui.h"

typedef struct WINDOW
{
	GLFWwindow* 	window;
	i32 			width;
	i32 			height;
	const char* 	title;

	UI* 			ui;
} WINDOW;

WINDOW* WINDOW_create(const i32 width, const i32 height, const char* title);
u32 WINDOW_init(WINDOW* window);

void WINDOW_cleanup(WINDOW* window);
void WINDOW_destroy(WINDOW* window);

void WINDOW_frame_begin(WINDOW* window);
void WINDOW_frame_end(WINDOW* window);

void WINDOW_render(WINDOW* window);

u32 WINDOW_should_close(WINDOW* window);

void WINDOW_set_ui(WINDOW* window, UI* ui);

#endif // WINDOW_H
