#include "ui/ui_sed.h"

UI_SED* UI_SED_create(u32 width, u32 height)
{
    UI_SED* ui_sed = (UI_SED*)malloc(sizeof(UI_SED));
    if (ui_sed == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    ui_sed->width = width;
    ui_sed->height = height;

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
    EVENT_MANAGER_register_handler(UI_SED_event_handler, EVENT_TYPE_SED_OPEN_SONG, ui_sed);
    
    ui_sed->is_open = false;
    ui_sed->song = NULL;

    return 1;
}

void UI_SED_render(UI_SED* ui_sed)
{
    if (!ui_sed->is_open) return;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
    window_flags |= ImGuiWindowFlags_NoCollapse;

    // // Determine the window title
    // char window_title[MAX_SMALL_STR_SIZE];
    // window_title[MAX_SMALL_STR_SIZE - 1] = '\0';

    // if (ui_sed->song == NULL)
    // {
    //     snprintf(window_title, MAX_SMALL_STR_SIZE, "Song Editor | None###sed-title");
    // }
    // else
    // {
    //     snprintf(window_title, MAX_SMALL_STR_SIZE, "Song Editor | %s (%u)###sed-title", ui_sed->title, ui_sed->pack_index);
    // }
    
    ImVec2 sed_dimensions = { ui_sed->width, ui_sed->height };
    igSetNextWindowSize(sed_dimensions, 0);
    // igBegin(window_title, NULL, window_flags);

    igBegin("Song Editor", &(ui_sed->is_open), window_flags);

    if (ui_sed->song == NULL)
    {
        igText("No Song!");
    }
    else
    {
        igText(ui_sed->song->path);
        igText(ui_sed->song->name);
    }


    // Song Meta Data
    igSeparatorText("Meta Data");

    // Pack Data
    // igText("Pack: %s", ui_sed->pack_name);
    // igText("Index in Pack: %u", ui_sed->pack_index);

    // // Song Title
    // igAlignTextToFramePadding();
    // igText("Song Title:");
    // igSameLine(0.0, -1.0);
    // igInputTextWithHint("###song-title-input", "Enter title for song", ui_sed->title, MAX_SMALL_STR_SIZE, 0, NULL, NULL);

    // // Song Lyrical Data
    // igSeparatorText("Lyrics Data");

    // igText("Orderings:");

    // ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    // tab_bar_flags |= ImGuiTabBarFlags_Reorderable;
    // tab_bar_flags |= ImGuiTabBarFlags_AutoSelectNewTabs;
    // tab_bar_flags |= ImGuiTabBarFlags_TabListPopupButton;
    // tab_bar_flags |= ImGuiTabBarFlags_NoCloseWithMiddleMouseButton;
    // tab_bar_flags |= ImGuiTabBarFlags_FittingPolicyScroll;
    // static bool arr[3] = { true, true, true };
    // if (igBeginTabBar("MyTabBar", tab_bar_flags ))
    // {
    //     if (igBeginTabItem("asdf", &(arr[0]), 0))
    //     {
    //         static char b[100];
    //         igAlignTextToFramePadding();
    //         igText("Ordering Name:");
    //         igSameLine(0.0, -1.0);
    //         igInputTextWithHint("###a", "Enter ordering name", b, 100, 0, NULL, NULL);
    //         igSameLine(0.0, -1.0);
    //         igSmallButton("Save");
    //         igEndTabItem();
    //     }
    //     if (igBeginTabItem("zxcv", &(arr[1]), 0))
    //     {
    //         igText("This is the %s tab!", "zxcv");
    //         igEndTabItem();
    //     }
    //     if(igBeginTabItem("qwer", &(arr[2]), 0))
    //     {
    //         igText("This is the %s tab!", "qwer");
    //         igEndTabItem();
    //     }
    //     igEndTabBar();
    // }

    igEnd();
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

// Event Handlers

void UI_SED_event_handler(EVENT* event, void* context)
{
    UI_SED* ui_sed = (UI_SED*)context;
    if (event->type == EVENT_TYPE_SED_OPEN_SONG)
    {
        EVENT_SED_OPEN_SONG* event_sed_open_song = (EVENT_SED_OPEN_SONG*)(event->data);

        if (ui_sed->song != NULL)
        {
            SONG_destroy(ui_sed->song);
            ui_sed->song = NULL;
        }

        ui_sed->song = SONG_create(event_sed_open_song->path);
        if (ui_sed->song == NULL)
        {
            LOG_ERROR("Failed to load song: %s\n", ui_sed->song->path);
            return;
        }

        if (!ui_sed->is_open)
        {
            ui_sed->is_open = true;
        }
    }
}