#include "ui/ui_sdb.h"

UI_SDB* UI_SDB_create()
{
    UI_SDB* ui_sdb = (UI_SDB*)malloc(sizeof(UI_SDB));
    if (ui_sdb == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    u32 r = UI_SDB_init(ui_sdb);
    if (r == 0)
    {
        free(ui_sdb);
        return NULL;
    }

    return ui_sdb;
}

u32 UI_SDB_init(UI_SDB* ui_sdb)
{
    ui_sdb->temp_songs[0].title = "Title 1";
    ui_sdb->temp_songs[0].path = "/home/benweisz/dev/minstrel/data/db/test.songf";
    ui_sdb->temp_songs[1].title = "Title 2";
    ui_sdb->temp_songs[1].path = "/Users/bweisz/dev/minstrel/data/db/0a5e0255.songf";
    ui_sdb->temp_songs[2].title = "Title 3";
    ui_sdb->temp_songs[2].path = "/Users/bweisz/dev/minstrel/data/db/0a5f0256.songf";
    ui_sdb->temp_songs[3].title = "Title 4";
    ui_sdb->temp_songs[3].path = "/Users/bweisz/dev/minstrel/data/db/0a600257.songf";
    ui_sdb->temp_songs[4].title = "Title 5";
    ui_sdb->temp_songs[4].path = "/Users/bweisz/dev/minstrel/data/db/0a610258.songf";
    ui_sdb->temp_songs[5].title = "Title 6";
    ui_sdb->temp_songs[5].path = "/Users/bweisz/dev/minstrel/data/db/0a620259.songf";
    ui_sdb->temp_songs[6].title = "Title 7";
    ui_sdb->temp_songs[6].path = "/Users/bweisz/dev/minstrel/data/db/0a63025a.songf";
    ui_sdb->temp_songs[7].title = "Title 8";
    ui_sdb->temp_songs[7].path = "/Users/bweisz/dev/minstrel/data/db/0a64025b.songf";
    return 1;
}

void UI_SDB_render(UI_SDB* ui_sdb)
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    igBegin("Song DB", NULL, window_flags);

    igText("Song List:");

    ImVec2 songs_list_box_dim = { -igGET_FLT_MIN(), 5 * igGetTextLineHeightWithSpacing() };
    if (igBeginListBox("##songs_list_box", songs_list_box_dim))
    {
        bool selected[8] = { false, false, false, false, false, false, false, false };
        ImVec2 selectable_dim = { 0, 0 };
        for (u32 i = 0; i < 8; i++)
        {
            igSelectable_Bool(ui_sdb->temp_songs[i].title, false, ImGuiSelectableFlags_None, selectable_dim);
            if (igBeginPopupContextItem(NULL, ImGuiPopupFlags_MouseButtonRight))
            {
                ImVec2 edit_song_dim = { 0, 0 };
                if (igSelectable_Bool("Edit Song", &(selected[i]), ImGuiSelectableFlags_None, edit_song_dim))
                {
                    EVENT_SED_OPEN_SONG* event_sed_open_song = EVENT_MANAGER_alloc(sizeof(EVENT_SED_OPEN_SONG));
                    if (event_sed_open_song != NULL)
                    {
                        strncpy(event_sed_open_song->path, ui_sdb->temp_songs[i].path, MAX_SMALL_STR_SIZE - 1);
                        event_sed_open_song->path[MAX_SMALL_STR_SIZE - 1] = '\0';

                        EVENT event;
                        event.type = EVENT_TYPE_SED_OPEN_SONG;
                        event.data = event_sed_open_song;
                        EVENT_MANAGER_add_event(event);
                    }
                }

                igEndPopup();
            }
        }
        igEndListBox();
    }

    igEnd();
}

void UI_SDB_cleanup(UI_SDB* ui_sdb)
{
}

void UI_SDB_destroy(UI_SDB* ui_sdb)
{
    if (ui_sdb == NULL) return;
    UI_SDB_cleanup(ui_sdb);
    free(ui_sdb);
}