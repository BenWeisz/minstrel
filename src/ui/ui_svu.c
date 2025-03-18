#include "ui/ui_svu.h"

UI_SVU* UI_SVU_create()
{
    UI_SVU* ui_svu = (UI_SVU*)malloc(sizeof(UI_SVU));
    if (ui_svu == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    u32 r = UI_SVU_init(ui_svu);
    if (r == 0)
    {
        free(ui_svu);
        return NULL;
    }

    return ui_svu;
}

u32 UI_SVU_init(UI_SVU* ui_svu)
{
    EVENT_MANAGER_register_handler(UI_SVU_event_handler, EVENT_TYPE_SVU_OPEN_SONG, ui_svu);

    ui_svu->is_open = false;
    ui_svu->song = NULL;
    
    return 1;
}

void UI_SVU_render(UI_SVU* ui_svu)
{
    if (!ui_svu->is_open) return;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    igBegin("Song Viewer", &(ui_svu->is_open), window_flags);

    if (ui_svu->song != NULL)
        igText(ui_svu->song->name);
    
    igEnd();
}

void UI_SVU_cleanup(UI_SVU* ui_svu)
{
    ui_svu->is_open = false;
    ui_svu->song = NULL;
}

void UI_SVU_destroy(UI_SVU* ui_svu)
{
    UI_SVU_cleanup(ui_svu);
    free(ui_svu);
}

void UI_SVU_event_handler(EVENT* event, void* context)
{
    UI_SVU* ui_svu = (UI_SVU*)context;
    if (event->type == EVENT_TYPE_SVU_OPEN_SONG)
    {
        EVENT_SVU_OPEN_SONG* event_svu_open_song = (EVENT_SVU_OPEN_SONG*)(event->data);

        if (ui_svu->song != NULL)
        {
            SONG_destroy(ui_svu->song);
            ui_svu->song = NULL;
        }

        ui_svu->song = SONG_create(event_svu_open_song->path);
        if (ui_svu->song == NULL)
        {
            LOG_ERROR("Failed to load song: %s\n", ui_svu->song->path);
            return;
        }

        if (!ui_svu->is_open)
        {
            ui_svu->is_open = true;
        }
    }
}