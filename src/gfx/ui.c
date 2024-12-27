#include "gfx/ui.h"

void UI_init(GLFWwindow* glfw_window)
{
    /* Initialized ImGui */
	igCreateContext(NULL);
	ImGui_ImplGlfw_InitForOpenGL(glfw_window, 1);
	ImGui_ImplOpenGL3_Init("#version 150");
}

void UI_destroy()
{
	/* Free ImGui resources */
   	ImGui_ImplOpenGL3_Shutdown();
   	ImGui_ImplGlfw_Shutdown();
   	igDestroyContext(NULL);
}

void UI_frame_begin()
{
    /* Begin ImGui Frame */
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    igNewFrame();
}

void UI_frame_end()
{

}

void UI_render()
{
    igShowDemoWindow(NULL);

    /* Render ImGui data */
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}