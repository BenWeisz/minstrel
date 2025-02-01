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

#define EVENT_TYPE_INVALID          0x00
#define EVENT_TYPE_SED_OPEN_SONG    0x01

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

typedef struct EVENT_MANAGER
{
    EVENT_LIST* curr_events;
    EVENT_LIST* next_events;

    EVENT_MANAGER_HANDLER handlers[MAX_COUNT_EVENT_TYPES + 1];
    EVENT_MANAGER_HANDLER_CONTEXT contexts[MAX_COUNT_EVENT_TYPES + 1];
} EVENT_MANAGER;

u32 EVENT_MANAGER_init();
void EVENT_MANAGER_cleanup();

void EVENT_MANAGER_register_handler(EVENT_MANAGER_HANDLER handler, u32 event_type, EVENT_MANAGER_HANDLER_CONTEXT context);
void EVENT_MANAGER_add_event(EVENT event);
void EVENT_MANAGER_handle_events();

#endif // EVENT_H