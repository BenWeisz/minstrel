#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "gfx/window.h"
#include "gfx/ui.h"

int main(void)
{
    // Initialize the WINDOW
	WINDOW* window = WINDOW_create(640, 480, "Minstrel");
    if (!window)
    {
        WINDOW_destroy(window);
        return -1;
    }

    // Initialize the UI
    UI* ui = UI_create(window->window, window->width, window->height);
    if (!ui)
    {
        WINDOW_destroy(window);
        return -1;
    }

    WINDOW_set_ui(window, ui);

    // Loop until the user closes the window
    while (!WINDOW_should_close(window))
    {
        WINDOW_frame_begin(window);
        WINDOW_render(window);
        WINDOW_frame_end(window);
    }

    // Destroy the UI and WINDOW
    UI_destroy(ui);
	WINDOW_destroy(window);

    return 0;
}
