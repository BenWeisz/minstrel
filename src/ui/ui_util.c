#include "ui/ui_util.h"

void UI_UTIL_help_marker(const char* msg)
{
    igSameLine(0.0, -1.0);
    igTextDisabled("(?)");
    if (igBeginItemTooltip())
    {
        igPushTextWrapPos(igGetFontSize() * 35.0f);
        igTextUnformatted(msg, NULL);
        igPopTextWrapPos();
        igEndTooltip();
    }
}