#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "list.h"
#include "utils.h"

#define NAME "main"

pthread_cond_t con_va;
pthread_mutex_t mutex;
list* message_list = NULL;

extern pthread_t producer_array[10];
extern consumer_thread_manager consumer_thread_manager_instance;
extern void init_producer();
extern void init_consumer();
extern void register_cb(void(*func)(void* arg));

static void message_handler_cba(void* data, void* arg)
{   
    LOG("%ld AAAAAA handler message : %s\n",pthread_self(),data);
}

static void message_handler_cbb(void* data, void* arg)
{   
    LOG("%ld BBBBBB handler message : %s\n",pthread_self(),data);
}

static void message_handler_cbc(void* data, void* arg)
{   
    LOG("%ld CCCCCC handler message : %s\n",pthread_self(),data);
}

static void message_handler_cbd(void* data, void* arg)
{   
    LOG("%ld DDDDDD handler message : %s\n",pthread_self(),data);
}

int main()
{
    message_list = list_create();
    LOG("main\n");

    // 1. register call_back
    register_cb(&message_handler_cba);
    register_cb(&message_handler_cbb);
    register_cb(&message_handler_cbc);
    register_cb(&message_handler_cbd);

    //2. init_consumer
    init_consumer();
    usleep(1000*1000);

    //3. init_producer
    init_producer();

    for(int i =0 ;i<10;i++){
        pthread_join(producer_array[i],NULL);
    }
    for(int i=0 ;i<consumer_thread_manager_instance.cb_size;i++){
        pthread_join(consumer_thread_manager_instance.consumer_array[i].thid,NULL);
    }
}