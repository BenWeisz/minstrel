#include "ui/ui.h"

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
    ui->ui_sdb = NULL;
    ui->ui_sed = NULL;
    ui->song = NULL;

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

    UI_init_style();
    UI_init_fonts();

    ui->ui_sdb = UI_SDB_create();
    if (ui->ui_sdb == NULL)
        return 0;

    ui->ui_sed = UI_SED_create(ui->width / 4, ui->height * (3.0 / 4));
    if (ui->ui_sed == NULL)
        return 0;

    ui->song = SONG_create();
    if (ui->song == NULL)
        return 0;

    return 1;
}

void UI_init_style()
{
    ImGuiStyle* style = igGetStyle();
    igStyleColorsClassic(style);

    ImVec2 separator_text_padding = { 20, 5 };
    style->SeparatorTextPadding = separator_text_padding;
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

    UI_SDB_destroy(ui->ui_sdb);
    ui->ui_sdb = NULL;
    
    UI_SED_destroy(ui->ui_sed);
    ui->ui_sed = NULL;

    SONG_destroy(ui->song);
    ui->song = NULL;

    /* Free ImGui resources */
   	ImGui_ImplOpenGL3_Shutdown();
   	ImGui_ImplGlfw_Shutdown();
   	igDestroyContext(NULL);
}

void UI_destroy(UI* ui)
{
    if (ui == NULL) return;
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
    UI_SDB_render(ui->ui_sdb);
    UI_SED_render(ui->ui_sed);

    /* Render ImGui data */
    igRender();
    ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}