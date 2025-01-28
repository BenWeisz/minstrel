#include "ui/ui_sed.h"

UI_SED* UI_SED_create()
{
    UI_SED* ui_sed = (UI_SED*)malloc(sizeof(UI_SED));
    if (ui_sed == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    ui_sed->song = NULL;

    u32 r = UI_SED_init(ui_sed);
    if (r == 0)
    {
        free(ui_sed);
        return NULL;
    }

    return ui_sed;
}

u32 UI_SED_init(UI_SED* ui_sed)
{
    return 1;
}

void UI_SED_render(UI_SED* ui_sed)
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    // Determine the window title
    char window_title[MAX_SMALL_STR_SIZE];
    window_title[MAX_SMALL_STR_SIZE - 1] = '\0';

    if (ui_sed->song == NULL)
    {
        sprintf(window_title, "Song Editor | None###sed-title");
    }
    else
    {
        sprintf(window_title, "Song Editor | %s###sed-title", ui_sed->title);
    }
    
    igBegin(window_title, NULL, window_flags);

    // Song Title
    igTextColored(UI_UTIL_COLOR_PINK, "Title:");
    igSameLine(0.0, -1.0);
    igText(ui_sed->title);

    igTextColored(UI_UTIL_COLOR_PINK, "Pack:");
    igTextColored(UI_UTIL_COLOR_PINK, "Pack #:");

    igEnd();
}

u32 UI_SED_update_from_song(UI_SED* ui_sed)
{
    if (ui_sed->song == NULL)
    {
        LOG_WARN("Cannot update UI_SED from NULL SONG\n");
        return 1;
    }

    ui_sed->title[MAX_SMALL_STR_SIZE - 1] = '\0';
    strncpy(ui_sed->title, ui_sed->song->title, MAX_SMALL_STR_SIZE - 1);
    
    return 1;
}

void UI_SED_update_to_song(UI_SED* ui_sed)
{

}

void UI_SED_set_song(UI_SED* ui_sed, SONG* song)
{
    ui_sed->song = song;
}

void UI_SED_cleanup(UI_SED* ui_sed)
{
    ui_sed->song = NULL;
}

void UI_SED_destroy(UI_SED* ui_sed)
{
    if (ui_sed == NULL) return;
    UI_SED_cleanup(ui_sed);
    free(ui_sed);
}