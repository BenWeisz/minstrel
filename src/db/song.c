#include "db/song.h"

SONG* SONG_create()
{
    SONG* song = (SONG*)malloc(sizeof(SONG));
    if (song == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    u32 r = SONG_init(song);
    if (r == 0)
    {
        free(song);
        return NULL;
    }

    return song;
}

u32 SONG_init(SONG* song)
{
    song->title = "Test Title";
    return 1;
}

void SONG_cleanup(SONG* song)
{
    song->title = NULL;
}

void SONG_destroy(SONG* song)
{
    if (song == NULL) return;
    SONG_cleanup(song);
    free(song);
}