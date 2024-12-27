#ifndef SONGF_H
#define SONGF_H

#include "types.h"

/*
    .songf file layout (little endian)
    
    0x00            Song Header
    0x00-0x03       magic:                      0xEC 0xF4 0x5C 0x00
    0x04-0x07       name:                       Index into string table
    0x08-0x0B       section_table_size:         Section table size in bytes
    0x0C-0x0F       section_table_offset:       Section table bytes offset in .songf file
    0x10-0x13       ordering_table_size:        Ordering table size in bytes
    0x14-0x17       ordering_table_offset:      Ordering table bytes offset in .songf file
    0x18-0x1B       string_table_size:          String table size in bytes
    0x1C-0x1F       string_table_offset:        String table size in bytes
    --------------------------------------------------------------------------------------
    0x??            Sections Table              (section_table_offset in .songf)
    ======
    0x??+0          name:                       Index of song section's name in the string table
    0x??+4          text:                       Index of song section's text in the string table
    ======
    0x??+8          name:                       Index of next song section's name in the string table
    0x??+12         text:                       Index of next song section's text in the string table
    ======
    ... section_table_size ... total SONGF_SECTION's
    --------------------------------------------------------------------------------------
    0x??            Orderings Table             (ordering_table_offset in .songf)
    ======
    0x??+0          name:                       Index of song ordering's name in the string table
    0x??+4          sections_size:              Number of sections part of this ordering
    0x??+8          sections_offset:            Ordering data byte offset in the .songf file
    ======
    0x??+12         name:                       Index of next song ordering's name in the string table
    0x??+16         sections_size:              Number of section's part of the next ordering
    0x??+20         sections_offset:            Next ordering data byte offset in the .songf file
    ======
    ... ordering_table_size ... total SONGF_ORDERING's
    --------------------------------------------------------------------------------------
    0x??            String Table                (string_table_offset in .songf)
    ======
    0x??+0          size:                       UTF-8 string size in bytes
    0x??+4          offset:                     Offset of this string in the .songf file
    ======
    0x??+8          size:                       Next UTF-8 string size in the bytes
    0x??+12         offset:                     Offset of the next string in the .songf file
    ======
    ... string_table_size ... total SONGF_STRING's
    --------------------------------------------------------------------------------------
    0x??            Ordering Data               (u32 data of section indices in ordering)
    --------------------------------------------------------------------------------------
    0x??            String Data                 (Raw u8 data representing UTF-8 codepoints)

*/

typedef struct SONGF
{
    u32 magic;
    u32 name;

    u32 section_table_size;
    u32 section_table_offset;

    u32 ordering_table_size;
    u32 ordering_table_offset;

    u32 string_table_size;
    u32 string_table_offset;
} SONGF;

typedef struct SONGF_SECTION
{
    u32 name;
    u32 text;
} SONGF_SECTION;

typedef struct SONGF_ORDERING
{
    u32 name;
    u32 sections_size;
    u32 sections_offset;
} SONGF_ORDERING;

typedef struct SONGF_STRING
{
    u32 size;
    u32 offset;
} SONGF_STRING;

#endif // SONGF_H