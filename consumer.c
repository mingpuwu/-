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
#define NAME "Consumer"

consumer_thread consumer_array[5];
pthread_t delay_thread_id;
extern pthread_cond_t con_va;
extern pthread_mutex_t mutex;
extern list* message_list;

static void message_handler(void* data, void* arg)
{
    LOG("thid %ld, handler message : %s\n",pthread_self(),data);
}

static void delay_handler(void* data)
{
    LOG("delay_handler start\n");
    usleep(1000*1000);
    LOG("thid %ld, delay handler message : %s\n",pthread_self(),data);
    LOG("delay_handler end\n");
}

static void consumer(void* arg)
{
    LOG("consumer thread start\n");
    LOG("consumer thread id : %ld\n",pthread_self());
    consumer_thread* thread_instance = (consumer_thread*)arg;
    while(1)
    {
        pthread_mutex_lock(thread_instance->th_mutex);
        while(thread_instance->list_buffer->size == 0){
            pthread_cond_wait(thread_instance->th_con_va, thread_instance->th_mutex);
        }
        LOG("thid %ld, message_list is : %d\n",pthread_self(),thread_instance->list_buffer->size);
        list_for_each(thread_instance->list_buffer, &message_handler, NULL);
        LOG("thid %ld,handler complete\n",pthread_self());
        list_clear(thread_instance->list_buffer);
        pthread_mutex_unlock(thread_instance->th_mutex);
        usleep(5000*100);
        //LOG();
    }
}

static void delay_thread(void* arg)
{
    LOG("delay_thread start\n");
    LOG("delay_thread id : %ld\n",pthread_self());

    while(1){
        while(message_list->size == 0)
            pthread_cond_wait(&con_va, &mutex);
        list* tmp_list = list_copy(message_list);
        pthread_mutex_unlock(&mutex);
        list_for_each(tmp_list, &delay_handler, NULL);
        list_destory(tmp_list);
        usleep(5000*100);
    }
}

void init_consumer(void* arg)
{
    LOG("init\n");
    for(int i = 0; i<5; i++){
        consumer_array[i].th_con_va = &con_va;
        consumer_array[i].th_mutex = &mutex;
        consumer_array[i].list_buffer = list_create();
        pthread_create(&consumer_array[i].thid, NULL, &consumer, &consumer_array[i]);
    }

    //pthread_create(&delay_thread_id, NULL, &delay_thread, NULL);
}