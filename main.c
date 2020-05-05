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
extern pthread_t consumer_array[5];
extern pthread_t producer_array[10];

extern void init_producer();
extern void init_consumer();

int main()
{
    message_list = list_create();
    LOG("main\n");
    init_consumer();
    usleep(1000*1000);
    init_producer();

    for(int i =0 ;i<10;i++){
        pthread_join(producer_array[i],NULL);
    }
    for(int i=0 ;i<5;i++){
        pthread_join(consumer_array[i],NULL);
    }
}