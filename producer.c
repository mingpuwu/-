#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "utils.h"
#include "list.h"

#undef NAME
#define NAME "Producer"

extern consumer_thread_manager consumer_thread_manager_instance;
pthread_t producer_array[10];

extern pthread_cond_t con_va;
extern pthread_mutex_t mutex;
extern list* message_list;

static void list_append_message(void* data, void* arg)
{
    LOG("append : %s\n",data);
    list_append((list*)arg, data);
}

void append_message(void* data)
{
    pthread_mutex_lock(&mutex);
    list_append(message_list,data);
    LOG("list size is : %d\n",message_list->size);
    for(int i = 0;i<consumer_thread_manager_instance.cb_size;i++){
        list_for_each(message_list,
                      &list_append_message,
                      consumer_thread_manager_instance.consumer_array[i].list_buffer);
    }
    list_clear(message_list);
    LOG("clear list size is : %d\n",message_list->size);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&con_va);
}

//append

static void producer(void* arg)
{
    LOG("producer thread start\n");
    LOG("thread is : %ld\n", pthread_self());
    while(1){
        char data1[] = "Message1";
        append_message(data1);
        /* char data2[] = "Message2";
        append_message(data2);
        char data3[] = "Message3";
        append_message(data3);
        char data4[] = "Message4";
        append_message(data4);
        char data5[] = "Message5";
        append_message(data5); */
        usleep(1000*1000);
    }
}

void init_producer(){
    for(int i=0; i<10; i++){
        pthread_create(&producer_array[i], NULL, &producer, NULL);
    }
}