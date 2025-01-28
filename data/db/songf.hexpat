import type.base;

struct SONGF
{
    u32 magic;
    u32 name;

    type::Hex<u32> section_table_offset;
    type::Hex<u32> ordering_table_offset;
    type::Hex<u32> string_table_offset;
};

struct SONGF_SECTION
{
    u32 name;
    u32 text;
};

struct SONGF_SECTION_TABLE
{
    u32 section_count;
    type::Hex<u32> section_offset;
};

struct SONGF_ORDERING
{
    u32 name;
    u32 sections_count;
    type::Hex<u32> sections_offset;
};

struct SONFG_ORDERING_TABLE
{
    u32 ordering_count;
    type::Hex<u32> ordering_offset;

    u32 ordering_blob_size;
    type::Hex<u32> ordering_blob_offset;
};

struct SONGF_STRING_TABLE
{
    u32 string_blob_size;
    type::Hex<u32> string_blob_offset;
};

SONGF songf @ 0x00;
SONGF_SECTION_TABLE section_table @ songf.section_table_offset;
SONFG_ORDERING_TABLE ordering_table @ songf.ordering_table_offset;
SONGF_STRING_TABLE string_table @ songf.string_table_offset;

SONGF_SECTION sections[section_table.section_count] @ section_table.section_offset;
SONGF_ORDERING orderings[ordering_table.ordering_count] @ ordering_table.ordering_offset;

u32 ordering0[orderings[0].sections_count] @ ordering_table.ordering_blob_offset + orderings[0].sections_offset;