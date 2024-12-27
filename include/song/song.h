#ifndef SONG_H
#define SONG_H

typedef struct SONG_SECTION
{
    char* name;
    char* text;
} SONG_SECTION;

typedef struct SONG_ORDERING
{
    u32     num_sections;
    u32*    sections;
} SONG_ORDERING;

typedef struct SONG
{
    char*           title;
    char*           path;

    u32             num_sections;
    SONG_SECTION*   sections;
    
    u32             num_orderings;
    SONG_ORDERING*  orderings;
} SONG;

#endif // SONG_H