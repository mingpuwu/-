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

consumer_thread_manager consumer_thread_manager_instance;
/* pthread_t delay_thread_id; */
extern pthread_cond_t con_va;
extern pthread_mutex_t mutex;
extern list* message_list;

/* static void delay_handler(void* data)
{
    LOG("delay_handler start\n");
    usleep(1000*1000);
    LOG("thid %ld, delay handler message : %s\n",pthread_self(),data);
    LOG("delay_handler end\n");
}
 */
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
        list_for_each(thread_instance->list_buffer, thread_instance->call_back, NULL);
        LOG("thid %ld,handler complete\n",pthread_self());

        list_clear(thread_instance->list_buffer);
        pthread_mutex_unlock(thread_instance->th_mutex);

        usleep(5000*100);
        //LOG();
    }
}

/* static void delay_thread(void* arg)
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
} */

void init_consumer(void* arg)
{
    LOG("init\n");
    if(consumer_thread_manager_instance.cb_size == 0){
        LOG("No register call_back\n");
        return;
    }
    for(int i = 0; i<consumer_thread_manager_instance.cb_size; i++){
        consumer_thread_manager_instance.consumer_array[i].th_con_va = &con_va;
        consumer_thread_manager_instance.consumer_array[i].th_mutex = &mutex;
        consumer_thread_manager_instance.consumer_array[i].list_buffer = list_create();
        pthread_create(&consumer_thread_manager_instance.consumer_array[i].thid,
                       NULL, 
                       &consumer, 
                       &consumer_thread_manager_instance.consumer_array[i]);
    }
}

void register_cb(void(*func)(void* arg))
{
    if(func == NULL)
        return;
    if(consumer_thread_manager_instance.cb_size == 30)
        return;
    LOG("current register cb size is : %d\n",consumer_thread_manager_instance.cb_size);
    consumer_thread_manager_instance.consumer_array[consumer_thread_manager_instance.cb_size].call_back = func;
    consumer_thread_manager_instance.cb_size++;
}