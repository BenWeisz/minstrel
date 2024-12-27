import type.base;

struct SONGF
{
    u32 magic;
    u32 name;

    u32 section_table_size;
    type::Hex<u32> section_table_offset;

    u32 ordering_table_size;
    type::Hex<u32> ordering_table_offset;

    u32 string_table_size;
    type::Hex<u32> string_table_offset;
};

struct SONGF_SECTION
{
    u32 name;
    u32 text;
};

struct SONGF_ORDERING
{
    u32 name;
    u32 sections_size;
    type::Hex<u32> sections_offset;
};

struct SONGF_STRING
{
    u32 size;
    type::Hex<u32> offset;
};

SONGF song @ 0x00;
SONGF_SECTION sections[2] @ 0x20;
SONGF_ORDERING orderings[1] @0x30;
SONGF_STRING strings[6] @0x3C;