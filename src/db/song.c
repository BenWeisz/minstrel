#include "db/song.h"

SONG* SONG_create(const char* path)
{
    SONG* song = (SONG*)malloc(sizeof(SONG));
    if (song == NULL)
    {
        LOG_ERROR("malloc\n");
        return NULL;
    }

    strncpy(song->path, path, MAX_SMALL_STR_SIZE - 1);
    song->path[MAX_SMALL_STR_SIZE - 1] = '\0';

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
    song->name = NULL;

    if (song->path[0] != '\0')
    {
        u32 r = SONG_load(song);
        return r;
    }
    
    return 0;
}

u32 SONG_load(SONG* song)
{
    u32 data_size;
    u8* data = IO_read_uchar(song->path, &data_size);
    if (data == NULL)
    {
        LOG_ERROR("IO_read_char_sized\n");
        return 0;
    }

    SONGF* songf = (SONGF*)data;
    if (songf->magic != 0x001F9DCC)
    {
        LOG_ERROR("%s does not match the .songf file spec\n", song->path);
        free(data);
        return 0;
    }
    
    // Load the string table
    if (songf->string_table_offset < 0 || songf->string_table_offset + sizeof(SONGF_STRING_TABLE) > data_size)
    {
        LOG_ERROR("Invalid string table location\n");
        free(data);
        return 0;
    }

    SONGF_STRING_TABLE* string_table = (SONGF_STRING_TABLE*)(data + songf->string_table_offset);
    if (string_table->strings_blob_offset < 0 || string_table->strings_blob_offset + string_table->strings_blob_size > data_size)
    {
        LOG_ERROR("Invalid strings blob location\n");
        free(data);
        return 0;
    }

    song->strings_blob = (u8*)malloc(sizeof(u8) * string_table->strings_blob_size);
    if (song->strings_blob == NULL)
    {
        LOG_ERROR("malloc\n");
        free(data);
        return 0;
    }

    memcpy(song->strings_blob, data + string_table->strings_blob_offset, string_table->strings_blob_size);

    // Load song name
    if (songf->name >= string_table->strings_blob_size)
    {
        LOG_ERROR("Invalid song name location\n");
        free(song->strings_blob);
        free(data);
        return 0;
    }

    song->name = song->strings_blob + songf->name;

    // Load the section table
    if (songf->section_table_offset < 0 || songf->section_table_offset + sizeof(SONGF_SECTION_TABLE) > data_size)
    {
        LOG_ERROR("Invalid section table location\n");
        free(song->strings_blob);
        free(data);
        return 0;
    }

    SONGF_SECTION_TABLE* section_table = (SONGF_SECTION_TABLE*)(data + songf->section_table_offset);

    if (section_table->section_offset < 0 || section_table->section_offset + (sizeof(SONGF_SECTION) * section_table->section_count) > data_size)
    {
        LOG_ERROR("Invalid section table\n");
        free(song->strings_blob);
        free(data);
        return 0;
    }

    SONGF_SECTION* sections = (SONGF_SECTION*)(data + section_table->section_offset);

    song->num_sections = section_table->section_count;
    song->sections = (SONG_SECTION*)malloc(sizeof(SONG_SECTION) * section_table->section_count);
    if (song->sections == NULL)
    {
        LOG_ERROR("malloc\n");
        free(song->strings_blob);
        free(data);
        return 0;
    }

    for (u32 section_i = 0; section_i < song->num_sections; section_i++)
    {
        SONG_SECTION* section = &(song->sections[section_i]);
        section->name = song->strings_blob + sections[section_i].name;
        section->text = song->strings_blob + sections[section_i].text;
    }

    // Load the ordering table
    if (songf->ordering_table_offset < 0 || songf->ordering_table_offset + sizeof(SONGF_ORDERING_TABLE) > data_size)
    {
        LOG_ERROR("Invalid ordering table location\n");
        free(song->sections);
        free(song->strings_blob);
        free(data);
        return 0;
    }

    SONGF_ORDERING_TABLE* ordering_table = (SONGF_ORDERING_TABLE*)(data + songf->ordering_table_offset);
    if (ordering_table->ordering_offset < 0 || ordering_table->ordering_offset + (sizeof(SONGF_ORDERING) * ordering_table->ordering_count) > data_size)
    {
        LOG_ERROR("Invalid ordering table\n");
        free(song->sections);
        free(song->strings_blob);
        free(data);
        return 0;
    }

    SONGF_ORDERING* orderings = (SONGF_ORDERING*)(data + ordering_table->ordering_offset);
    
    if (ordering_table->orderings_blob_offset < 0 || ordering_table->orderings_blob_offset + ordering_table->orderings_blob_size > data_size)
    {
        LOG_ERROR("Invalid ordering table\n");
        free(song->sections);
        free(song->strings_blob);
        free(data);
        return 0;
    }

    song->orderings_blob = (u8*)malloc(sizeof(u8) * ordering_table->orderings_blob_size);
    if (song->orderings_blob == NULL)
    {
        LOG_ERROR("malloc\n");
        free(song->sections);
        free(song->strings_blob);
        free(data);
        return 0;
    }

    memcpy(song->orderings_blob, data + ordering_table->orderings_blob_offset, ordering_table->orderings_blob_size);

    song->num_orderings = ordering_table->ordering_count;
    song->orderings = (SONG_ORDERING*)malloc(sizeof(SONG_ORDERING) * ordering_table->ordering_count);
    if (song->orderings == NULL)
    {
        LOG_ERROR("malloc\n");
        free(song->sections);
        free(song->strings_blob);
        free(song->orderings_blob);
        free(data);
        return 0;
    }

    for (u32 ordering_i = 0; ordering_i < song->num_orderings; ordering_i++)
    {
        SONGF_ORDERING* ordering = &(orderings[ordering_i]);
        if (ordering->sections_offset < 0 || ordering->sections_offset + (sizeof(u32) * ordering->sections_count) > ordering_table->orderings_blob_size)
        {
            LOG_ERROR("Invalid ordering location\n");
            free(song->sections);
            free(song->orderings);
            free(song->strings_blob);
            free(song->orderings_blob);
            free(data);
            return 0;
        }

        song->orderings[ordering_i].name = song->strings_blob + ordering->name;
        song->orderings[ordering_i].num_sections = ordering->sections_count;
        song->orderings[ordering_i].sections = (u32*)(song->orderings_blob + ordering->sections_offset);
    }

    free(data);

    for (u32 i = 0; i < song->num_orderings; i++)
    {
        LOG_PRINT("Ordering: %s\n", song->orderings[i].name);
        LOG_PRINT("num sections: %u\n", song->orderings[i].num_sections);
        for (u32 j = 0; j < song->orderings[i].num_sections; j++)
        {
            LOG_PRINT("%u\n", song->orderings[i].sections[j]);
        }
    }

    return 1;
}

void SONG_cleanup(SONG* song)
{
    song->path[0] = '\0';
    song->name = NULL;
    
    if (song->strings_blob != NULL)
    {
        free(song->strings_blob);
        song->strings_blob = NULL;
    }

    if (song->sections != NULL)
    {
        song->num_sections = 0;
        free(song->sections);
    }
}

void SONG_destroy(SONG* song)
{
    if (song == NULL) return;
    SONG_cleanup(song);
    free(song);
}