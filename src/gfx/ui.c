#include "gfx/ui.h"

UI* UI_create(GLFWwindow* window, const u32 width, const u32 height)
{
    UI* ui = (UI*)malloc(sizeof(UI));
    if (ui == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    ui->window = window;
    ui->width = width;
    ui->height = height;

    u32 r = UI_init(ui);
    if (r == 0)
    {
        free(ui);
        return NULL;
    }

    return ui;
}

u32 UI_init(UI* ui)
{
    /* Initialized ImGui */
	igCreateContext(NULL);
	ImGui_ImplGlfw_InitForOpenGL(ui->window, 1);
	ImGui_ImplOpenGL3_Init("#version 150");

    UI_init_fonts();

    return 1;
}

void UI_init_fonts()
{
    ImGuiIO* io = igGetIO();

    // Set up the range builder
    ImVector_ImWchar ranges;
    ImVector_ImWchar_Init(&ranges);
    ImFontGlyphRangesBuilder* builder = ImFontGlyphRangesBuilder_ImFontGlyphRangesBuilder();

    // Select the range
    ImFontGlyphRangesBuilder_AddRanges(builder, ImFontAtlas_GetGlyphRangesDefault(io->Fonts));
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00F6);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00FC);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00F3);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x0151);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00FA);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x0171);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00E9);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00E1);
    ImFontGlyphRangesBuilder_AddChar(builder, 0x00ED);

    // Build the range
    ImFontGlyphRangesBuilder_BuildRanges(builder, &ranges);

    // Load the font file
    ImFontAtlas_AddFontFromFileTTF(io->Fonts, RESOURCE "font/Cousine-Regular.ttf", 13, NULL, ranges.Data);
    ImFontAtlas_Build(io->Fonts);

    // Clean up the range builder
    ImFontGlyphRangesBuilder_destroy(builder);
    ImVector_ImWchar_UnInit(&ranges);
}

void UI_cleanup(UI* ui)
{
    ui->window = NULL;
    ui->width = 0;
    ui->height = 0;

    /* Free ImGui resources */
   	ImGui_ImplOpenGL3_Shutdown();
   	ImGui_ImplGlfw_Shutdown();
   	igDestroyContext(NULL);
}

void UI_destroy(UI* ui)
{
    UI_cleanup(ui);
    free(ui);
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

void UI_render(UI* ui)
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    igBegin("Song DB", NULL, window_flags);
    igEnd();

    /* Render ImGui data */
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}