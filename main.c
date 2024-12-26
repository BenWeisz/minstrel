#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#include "window.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"
#include "cimgui_impl.h"

float BKG_COLOR[3] = {229 / 255.0, 220 / 255.0, 197 / 255.0};

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

	/* Configure the opengl profile */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
	WINDOW* window = WINDOW_create(640, 480, "Minstrel");
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window->window);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowSize(window->window, mode->width, mode->height);
    glfwSetWindowPos(window->window, 0, 0);
    // printf("%d, %d\n", mode->width, mode->height);

	// glfwMaximizeWindow(window);

    /* Fix up the GL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("ERROR: Failed to initialize GLAD.\n");
        return -1;
    }    

    /* Setup a basic input handler */
    glfwSetKeyCallback(window->window, key_callback);

	/* Initialized ImGui */
	igCreateContext(NULL);
	ImGui_ImplGlfw_InitForOpenGL(window->window, 1);
	ImGui_ImplOpenGL3_Init("#version 150");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window->window))
    {
    	/* Begin ImGui Frame */
		ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
		igNewFrame();

		igShowDemoWindow(NULL);

        /* Render here */
        glClearColor(BKG_COLOR[0], BKG_COLOR[1], BKG_COLOR[2], 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

		/* Render ImGui data */
		igRender();
		ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window->window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	/* Free ImGui resources */
   	ImGui_ImplOpenGL3_Shutdown();
   	ImGui_ImplGlfw_Shutdown();
   	igDestroyContext(NULL);

	WINDOW_destroy(window);
    glfwTerminate();
    return 0;
}
