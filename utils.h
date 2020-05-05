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
    list* list_buffer;
}consumer_thread;