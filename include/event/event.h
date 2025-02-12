#ifndef EVENT_H
#define EVENT_H

/*
    Events system that is used to communicate between different components of the program.
*/

#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "io/log.h"

// Events
#define MAX_COUNT_EVENT_TYPES       256      

// Value 0x00 is RESERVED for EVENT_TYPE_INVALID
#define EVENT_TYPE_INVALID          0x00

typedef struct EVENT
{
    u32 type;
    void* data;
} EVENT;

// Event List
#define MAX_SIZE_EVENT_LIST 256

typedef struct EVENT_LIST
{
    EVENT events[MAX_SIZE_EVENT_LIST];
    u32 size;
} EVENT_LIST;

// Event Manager
typedef void (*EVENT_MANAGER_HANDLER)(EVENT* event, void* context);
typedef void* EVENT_MANAGER_HANDLER_CONTEXT;

#define EVENT_MANAGER_BUFFER_SIZE 1024 * 1024 * 16

// Ring buffer
typedef struct EVENT_MANAGER_BUFFER
{
    u8* data; // Where the event.data can be allocated from
    u32 head; // Where the next allocation is to come from
    u32 size; // The number of bytes allocated this update cycle
} EVENT_MANAGER_BUFFER;

typedef struct EVENT_MANAGER
{
    EVENT_LIST* curr_events;
    EVENT_LIST* next_events;

    EVENT_MANAGER_HANDLER handlers[MAX_COUNT_EVENT_TYPES + 1];
    EVENT_MANAGER_HANDLER_CONTEXT contexts[MAX_COUNT_EVENT_TYPES + 1];

    EVENT_MANAGER_BUFFER buffer;
} EVENT_MANAGER;

u32 EVENT_MANAGER_init();
void EVENT_MANAGER_cleanup();

void EVENT_MANAGER_register_handler(EVENT_MANAGER_HANDLER handler, u32 event_type, EVENT_MANAGER_HANDLER_CONTEXT context);
void EVENT_MANAGER_add_event(EVENT event);
void EVENT_MANAGER_handle_events();

// Data allocated with this function need not be free-d by user
void* EVENT_MANAGER_alloc(size_t size);

#endif // EVENT_H