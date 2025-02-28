#ifndef SONG_H
#define SONG_H

/*
    Runtime representation of a song.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>

#include "types.h"
#include "io/log.h"
#include "io/io.h"
#include "util/consts.h"

#include "db/songf.h"

typedef struct SONG_SECTION
{
    u8* name;
    u8* text;
} SONG_SECTION;

typedef struct SONG_ORDERING
{
    u8* name;

    u32 num_sections;
    u32* sections; 
} SONG_ORDERING;

typedef struct SONG
{
    char path[MAX_SMALL_STR_SIZE];
    
    u8* name;
    
    u32 num_sections;
    SONG_SECTION* sections;

    u32 num_orderings;
    SONG_ORDERING* orderings;

    u8* strings_blob;
    u8* orderings_blob;
} SONG;

SONG* SONG_create(const char* path);
u32 SONG_init(SONG* song);

u32 SONG_load(SONG* song);

void SONG_cleanup(SONG* song);
void SONG_destroy(SONG* song);

#endif // SONG_H