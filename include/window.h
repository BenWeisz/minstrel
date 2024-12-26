#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "types.h"
#include "log.h"

typedef struct WINDOW
{
	GLFWwindow* window;
	unsigned int width;
	unsigned int height;
	const char* title;
} WINDOW;

WINDOW* WINDOW_create(const unsigned int width, const unsigned int height, const char* title);
u32 WINDOW_init(WINDOW* window);

void WINDOW_cleanup(WINDOW* window);
void WINDOW_destroy(WINDOW* window);

#endif // WINDOW_H
