#ifndef SONGF_H
#define SONGF_H

#include "types.h"

/*
    .songf file layout (little endian)
    
    0x00            Song Header
    0x00-0x03       magic:                      0xCC 0x9D 0x1F 0x00
    0x04-0x07       name:                       Byte offset into string table (string table location denoted by SONGF.string_table_offset)
    0x08-0x0B       string_table_offset:        Byte offset into the .songf file where the SONGF_STRING_TABLE struct appears
    0x0C-0x0F       section_table_offset:       Byte offset into the .songf file where SONGF_SECTION_TABLE struct appears
    0x10-0x13       ordering_table_offset:      Byte offset into the .songf file where the SONFG_ORDERING_TABLE struct appears
    --------------------------------------------------------------------------------------
    0x??            Section Table               (section_table_offset in .songf file)
    ======
    0x??+0          section_count:              Number of SONGF_SECTION structs in the section table
    0x??+4          section_offset:             Byte offset in the .songf file where the SONGF_SECTION structs appear
    --------------------------------------------------------------------------------------
    0x??            Ordering Table              (ordering_table_offset in .songf file)
    ======
    0x??+0          ordering_count:            Number of SONGF_ORDERING structs in the odering table
    0x??+4          ordering_offset:           Byte offset in the .songf file where the SONGF_ORDERING structs appear
    0x??+8          orderings_blob_size:         Ordering data blob size in bytes 
    0x??+12         orderings_blob_offset:       Ordering data blob offset in bytes from the start of the .songf file
    --------------------------------------------------------------------------------------
    0x??            String Table                (string_table_offset in .songf file)
    ======
    0x??+0          strings_blob_size:           String data blob size in bytes
    0x??+4          strings_blob_offset:         String data blob offset in bytes from the start of the .songf file   
    --------------------------------------------------------------------------------------
    0x??            Sections
    ======
    0x??+0          name:                       Byte offset of name string in the string data blob
    0x??+4          text:                       Byte offset of text string in the string data blob
    ======
    0x??+8          name:                       Byte offset of another name string in the string data blob
    0x??+12         text:                       Byte offset of another text string in the string data blob
    ======
    ...
    --------------------------------------------------------------------------------------
    0x??            Orderings
    ======
    0x??+0          name:                       Byte offset of name string in the string data blob
    0x??+4          sections_count:             Number of sections part of this ordering
    0x??+8          sections_offset:            u32 offset of sections data in ordering data blob
    ======
    0x??+12         name:                       Byte offset of the 
    0x??+16         sections_count:             Number of sections part of another ordering
    0x??+20         sections_offset:            u32 offset of sections data of another ordering in ordering data blob
    ======
    ... 
    --------------------------------------------------------------------------------------
    0x??            Orderings Data             (Located at SONFG_ORDERING_TABLE.ordering_offset bytes from the start of the .songf file)
    ======
    0x??+0          Data Blob                  List of u32's specifying indices from the sections struct which are part of each of the orderings
    --------------------------------------------------------------------------------------
    0x??            String Data                (Located at SONGF_STRING_TABLE.strings_blob_offset bytes from the start of the .songf file)
    ======
    0x??+0          Data Blob                  List of null terminated, UTF-8 encoded strings
*/

typedef struct SONGF
{
    u32 magic;
    u32 name;

    u32 string_table_offset;
    u32 section_table_offset;
    u32 ordering_table_offset;
} SONGF;

typedef struct SONGF_SECTION
{
    u32 name;
    u32 text;
} SONGF_SECTION;

typedef struct SONGF_SECTION_TABLE
{
    u32 section_count;
    u32 section_offset;
} SONGF_SECTION_TABLE;

typedef struct SONGF_ORDERING
{
    u32 name;
    u32 sections_count;
    u32 sections_offset;
} SONGF_ORDERING;

typedef struct SONFG_ORDERING_TABLE
{
    u32 ordering_count;
    u32 ordering_offset;

    u32 orderings_blob_size;
    u32 orderings_blob_offset;
} SONGF_ORDERING_TABLE;

typedef struct SONGF_STRING_TABLE
{
    u32 strings_blob_size;
    u32 strings_blob_offset;
} SONGF_STRING_TABLE;

#endif // SONGF_H