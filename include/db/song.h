#ifndef SONG_H
#define SONG_H

/*
    Runtime representation of a song.
*/

#include <stdlib.h>

#include "types.h"
#include "io/log.h"

typedef struct SONG
{
    char* title;
} SONG;

SONG* SONG_create();
u32 SONG_init(SONG* song);

void SONG_cleanup(SONG* song);
void SONG_destroy(SONG* song);

#endif // SONG_H