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
    memset(ui_sdb->filter, 0, UI_SDB_FILTER_SIZE);
    return 1;
}

void UI_SDB_render(UI_SDB* ui_sdb)
{
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    igBegin("Song DB", NULL, window_flags);
    
    igInputText("Filter", ui_sdb->filter, UI_SDB_FILTER_SIZE, ImGuiInputTextFlags_None, NULL, NULL);

    UI_UTIL_help_marker("Search for any song title or lyrics\n");

    // for (int i = 0; i < 16; i++)
    // {
    //     printf("0x%x ", ui_sdb->filter[i]);
    // }
    // printf("\n");

    ImVec2 songs_list_box_size = { -igGET_FLT_MIN(), 5 * igGetTextLineHeightWithSpacing() };
    if (igBeginListBox("##songs_list_box", songs_list_box_size))
    {
        ImVec2 selectable_size = { 0, 0 };
        igSelectable_Bool("one", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("two", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("three", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("foour", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("five", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("sixe", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("seven", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("eight", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("nine", false, ImGuiSelectableFlags_None, selectable_size);
        igSelectable_Bool("ten", false, ImGuiSelectableFlags_None, selectable_size);
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