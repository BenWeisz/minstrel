#include "gfx/window.h"

float BKG_COLOR[3] = {229 / 255.0, 220 / 255.0, 197 / 255.0};

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
	if (!glfwInit()) return 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window->window = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
	if (!window->window) return 0;

	glfwMakeContextCurrent(window->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("gladLoadGLLoader\n");
        return 0;
    }

	const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowSize(window->window, vidmode->width, vidmode->height);
    glfwSetWindowPos(window->window, 0, 0);

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
	UI_frame_begin();

	/* Render here */
	glClearColor(BKG_COLOR[0], BKG_COLOR[1], BKG_COLOR[2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void WINDOW_frame_end(WINDOW* window)
{
	UI_frame_end();

	/* Swap front and back buffers */
	glfwSwapBuffers(window->window);

	/* Poll for and process events */
	glfwPollEvents();
}

void WINDOW_render(WINDOW* window)
{
	UI_render();
}

u32 WINDOW_should_close(WINDOW* window)
{
	return glfwWindowShouldClose(window->window) ? 1 : 0;
}