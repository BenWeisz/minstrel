#include "gfx/window.h"

void WINDOW_size_callback(GLFWwindow* window, i32 width, i32 height)
{
	WINDOW* user_window = (WINDOW*)glfwGetWindowUserPointer(window);
	user_window->width = width;
	user_window->height = height;
}

WINDOW* WINDOW_create(const i32 width, const i32 height, const char* title)
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
	if (!glfwInit()) return 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

	window->window = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
	if (!window->window) return 0;

	glfwMakeContextCurrent(window->window);

	glfwGetWindowSize(window->window, &(window->width), &(window->height));
    glfwSetWindowPos(window->window, 0, 0);

	glfwSetWindowUserPointer(window->window, (void*)window);
	glfwSetWindowSizeCallback(window->window, WINDOW_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("gladLoadGLLoader\n");
        return 0;
    }

	return 1;
}

void WINDOW_cleanup(WINDOW* window)
{
	window->width = 0;
	window->height = 0;

	if (window->window)
	{
		glfwDestroyWindow(window->window);
		window->window = NULL;
	}

	glfwTerminate();
}

void WINDOW_destroy(WINDOW* window)
{
	WINDOW_cleanup(window);
	free(window);
}

void WINDOW_frame_begin(WINDOW* window)
{
	if (window->ui) UI_frame_begin();

	/* Render here */
	glClearColor(21/255.0,44/255.0,67/255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void WINDOW_frame_end(WINDOW* window)
{
	if (window->ui) UI_frame_end();

	/* Swap front and back buffers */
	glfwSwapBuffers(window->window);

	/* Poll for and process events */
	glfwPollEvents();
}

void WINDOW_render(WINDOW* window)
{
	if (window->ui) UI_render(window->ui);
}

u32 WINDOW_should_close(WINDOW* window)
{
	return glfwWindowShouldClose(window->window) ? 1 : 0;
}

void WINDOW_set_ui(WINDOW* window, UI* ui)
{
	window->ui = ui;
}