#ifndef SONG_H
#define SONG_H

/*
    Runtime representation of a song.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "io/log.h"
#include "io/io.h"
#include "util/consts.h"

typedef struct SONG
{
    char path[MAX_SMALL_STR_SIZE];
    char title[MAX_SMALL_STR_SIZE];
} SONG;

SONG* SONG_create();
u32 SONG_init(SONG* song);

u32 SONG_load(SONG* song);

void SONG_cleanup(SONG* song);
void SONG_destroy(SONG* song);

#endif // SONG_H