#include "event/event.h"

EVENT_MANAGER* event_manager_instance = NULL;

u32 EVENT_MANAGER_init()
{
    if (event_manager_instance != NULL)
    {
        LOG_WARN("EVENT_MANAGER already initialized, reinitializing!\n");
        EVENT_MANAGER_cleanup();
    }

    // Initialize the Event Manager
    event_manager_instance = (EVENT_MANAGER*)malloc(sizeof(EVENT_MANAGER));
    if (event_manager_instance == NULL)
    {
        LOG_ERROR("malloc\n");
        return 0;
    }

    event_manager_instance->curr_events = NULL;
    event_manager_instance->next_events = NULL;

    // Initialize the event lists
    event_manager_instance->curr_events = (EVENT_LIST*)malloc(sizeof(EVENT_LIST));
    if (event_manager_instance->curr_events == NULL)
    {
        LOG_ERROR("malloc\n");
        EVENT_MANAGER_cleanup();
        return 0;
    }
    event_manager_instance->curr_events->size = 0;

    event_manager_instance->next_events = (EVENT_LIST*)malloc(sizeof(EVENT_LIST));
    if (event_manager_instance->next_events == NULL)
    {
        LOG_ERROR("malloc\n");
        EVENT_MANAGER_cleanup();
        return 0;
    }
    event_manager_instance->next_events->size = 0;

    // Initialize the handler pointers and contexts
    memset(event_manager_instance->handlers, 0x00, sizeof(EVENT_MANAGER_HANDLER) * (MAX_COUNT_EVENT_TYPES + 1));
    memset(event_manager_instance->contexts, 0x00, sizeof(EVENT_MANAGER_HANDLER_CONTEXT) * (MAX_COUNT_EVENT_TYPES + 1));

    // Initialize the event manager buffer
    event_manager_instance->buffer.data = (u8*)malloc(sizeof(u8) * EVENT_MANAGER_BUFFER_SIZE);
    if (event_manager_instance->buffer.data == NULL)
    {
        LOG_ERROR("malloc\n");
        EVENT_MANAGER_cleanup();
        return 0;
    }
    event_manager_instance->buffer.head = 0;
    event_manager_instance->buffer.size = 0;

    return 1;
}

void EVENT_MANAGER_cleanup()
{
    if (event_manager_instance->curr_events != NULL)
    {
        free(event_manager_instance->curr_events);
        event_manager_instance->curr_events = NULL;
    }
    if (event_manager_instance->next_events != NULL)
    {
        free(event_manager_instance->next_events);
        event_manager_instance->curr_events = NULL;
    }

    if (event_manager_instance->buffer.data != NULL)
    {
        free(event_manager_instance->buffer.data);
        event_manager_instance->buffer.data = NULL;
    }
    
    free(event_manager_instance);
    event_manager_instance = NULL;
}

void EVENT_MANAGER_register_handler(EVENT_MANAGER_HANDLER handler, u32 event_type, EVENT_MANAGER_HANDLER_CONTEXT context)
{
    if (handler == NULL)
    {
        LOG_WARN("EVENT_MANAGER_HANDLER must not be NULL\n");
        return;
    }

    if (event_type == EVENT_TYPE_INVALID)
    {
        LOG_WARN("Event type must be valid type\n");
        return;
    }

    event_manager_instance->handlers[event_type] = handler;
    event_manager_instance->contexts[event_type] = context;
}

void EVENT_MANAGER_add_event(EVENT event)
{
    if (event_manager_instance->next_events->size >= MAX_SIZE_EVENT_LIST - 1)
    {
        LOG_WARN("Refusing to add event, event list is full\n");
        return;
    }

    event_manager_instance->next_events->events[event_manager_instance->next_events->size++] = event;
}

void EVENT_MANAGER_handle_events()
{
    EVENT_LIST* temp_events = event_manager_instance->curr_events;
    event_manager_instance->curr_events = event_manager_instance->next_events;
    event_manager_instance->next_events = temp_events;
    event_manager_instance->next_events->size = 0;

    for (u32 event_index = 0; event_index < event_manager_instance->curr_events->size; event_index++)
    {
        EVENT* event = &(event_manager_instance->curr_events->events[event_index]);
        if (event->type == EVENT_TYPE_INVALID)
        {
            LOG_WARN("Refusing to handle invalid event\n");
            continue;
        }
        else if (event_manager_instance->handlers[event->type] == NULL)
        {
            LOG_WARN("Cannot handle event that doesn't have a registered handler\n");
            continue;
        }

        event_manager_instance->handlers[event->type](event, event_manager_instance->contexts[event->type]);
    }

    event_manager_instance->buffer.size = 0;
}

void* EVENT_MANAGER_alloc(size_t size)
{
    if (size + event_manager_instance->buffer.head > EVENT_MANAGER_BUFFER_SIZE)
    {
        event_manager_instance->buffer.size += EVENT_MANAGER_BUFFER_SIZE - event_manager_instance->buffer.head;

        if (size + event_manager_instance->buffer.size > EVENT_MANAGER_BUFFER_SIZE)
        {
            LOG_ERROR("Ran out of EVENT_MANAGER_BUFFER memory, increase EVENT_MANAGER_BUFFER_SIZE\n");
            return NULL;
        }

        event_manager_instance->buffer.head = size;
        event_manager_instance->buffer.size += size;

        return (void*)event_manager_instance->buffer.data;
    }
    else
    {
        if (size + event_manager_instance->buffer.size > EVENT_MANAGER_BUFFER_SIZE)
        {
            LOG_ERROR("Ran out of EVENT_MANAGER_BUFFER memory, increase EVENT_MANAGER_BUFFER_SIZE\n");
            return NULL;
        }
        
        u8* addr = event_manager_instance->buffer.data + event_manager_instance->buffer.head;
        event_manager_instance->buffer.head += size;
        event_manager_instance->buffer.size += size;

        return (void*)addr;
    }

}