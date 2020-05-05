#include <stdio.h>
#include <pthread.h>
#include "list.h"

#define LOG(...)   do{ \
    printf(""NAME" Info : "__VA_ARGS__);    \
}while(0)

typedef struct {
    pthread_t thid;
    pthread_cond_t* th_con_va;
    pthread_mutex_t* th_mutex;
    void (*call_back)(void*);
    list* list_buffer;
}consumer_thread;

typedef struct{
    consumer_thread consumer_array[30];
    int cb_size;
}consumer_thread_manager;