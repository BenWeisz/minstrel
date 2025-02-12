#include "db/song.h"

SONG* SONG_create()
{
    SONG* song = (SONG*)malloc(sizeof(SONG));
    if (song == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    song->path[0] = '\0';

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
    song->title[0] = '\0';

    if (song->path[0] != '\0')
    {
        u32 r = SONG_load(song);
        return r;
    }
    
    return 1;
}

u32 SONG_load(SONG* song)
{
    char* data = IO_read_char(song->path);
    if (data == NULL)
    {
        LOG_ERROR("IO_read_char_sized\n");
        return 0;
    }

    strncpy(song->title, data, MAX_SMALL_STR_SIZE - 1);
    song->title[MAX_SMALL_STR_SIZE - 1] = '\0';

    free(data);

    return 1;
}

void SONG_cleanup(SONG* song)
{
    song->path[0] = '\0';
    song->title[0] = '\0';
}

void SONG_destroy(SONG* song)
{
    if (song == NULL) return;
    SONG_cleanup(song);
    free(song);
}