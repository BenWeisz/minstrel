#include "window.h"

#include <stdio.h>

WINDOW* WINDOW_create(const unsigned int width, const unsigned int height, const char* title)
{
	WINDOW* window = (WINDOW*)malloc(sizeof(WINDOW));
	if (window == NULL)
	{
		LOG_ERROR("malloc\n");
		return NULL;
	}

	window->width = width;
	window->height = height;
	window->title = title;

	u32 r = WINDOW_init(window);
	if (r == 0)
	{
		free(window);
		return NULL;
	}

	return window;
}

u32 WINDOW_init(WINDOW* window)
{
	window->window = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
	if (!window->window) return 0;

	return 1;
}

void WINDOW_cleanup(WINDOW* window)
{
	window->width = 0;
	window->height = 0;

	glfwDestroyWindow(window->window);
	window->window = NULL;
}

void WINDOW_destroy(WINDOW* window)
{
	WINDOW_cleanup(window);
	free(window);
}
