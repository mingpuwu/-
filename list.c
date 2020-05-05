#include "list.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

#define NAME "List"

list* list_create()
{
    list* list = malloc(sizeof(list));
    if(list == NULL)
        return NULL;
    list->size = 0;
    list->head = malloc(sizeof(node));
    if(list->head == NULL){
        free(list);
        return NULL;
    }
    list->head->data = NULL;
    list->tail = list->head;
    list->tail->next = NULL;

    return list;
}

int list_append(list* list, void* data)
{
    if(list == NULL || data == NULL){
        printf("111\n");
        return -1;
    }
    if(list->tail == NULL){
        printf("222\n");
        return -1;
    }
    node* lastnode = list->tail;
    list->tail = malloc(sizeof(node));
    if(list->tail == NULL)
        return -1;
    list->size++;
    
    list->tail->data = malloc(sizeof(char)*strlen(data)+1);
    memset(list->tail->data,0,sizeof(char)*strlen(data)+1);
    memcpy(list->tail->data,data,strlen(data));
    lastnode->next = list->tail;
    return 0;
}

void* list_getnode(list* list, int num)
{
    if((list == NULL) || (num > list->size) || (list->size == 0))
        return NULL;
    node* node = list->head->next;
    if(node == NULL)
        return NULL;
    for(int i=0; i<num; i++) {
        node = node->next;
    }
    return node->data;
}

void list_for_each(list* list, void(*fun)(void*,void*),void* arg)
{
    if(list == NULL || list->size == 0 || fun == NULL)
        return;
    for(int i=0; i<list->size; i++){
        fun(list_getnode(list, i), arg);
    }
}

void get_tail(list* list, void* data)
{
    if (list == NULL || data == NULL)
        return;
    strcpy(data,list->tail->data);
    free(list->tail->data);
    list->tail->data = NULL;
}

list* list_copy(list* list_arg)
{   
    if(list_arg == NULL)
        return NULL;
    list* ret_list = list_create();
    node* current = list_arg->head->next;
    for(int i = 0;i<list_arg->size; i++){
        list_append(ret_list,current->data);
        current = current->next;
        if(current == NULL)
            break;
    }
    ret_list->size = list_arg->size;
    return ret_list;
}

void list_destory(list* list)
{
    if(list == NULL)
        return;
    node* current = list->head->next;
    if(current == NULL)
        return;

    for(int i = 0; i<list->size; i++){
        if(current->next ==NULL)
            break;
        node* next = current->next;
        if(current->data != NULL){
            free(current->data);
            current->data = NULL;
            current->next = NULL;
            free(current);
            current = NULL;
        }
        current = next;
    }

    free(list->head);
    list->head = NULL;

    list->size = 0;
    free(list);
    list = NULL;
}

void list_clear(list* list_arg)
{
    if(list_arg == NULL)
        return;
    node* current = list_arg->head->next;
    if(current == NULL)
        return;

    for(int i = 0; i<list_arg->size; i++){
        if(current->next ==NULL)
            break;
        node* next = current->next;
        if(current->data != NULL){
            free(current->data);
            current->data = NULL;
            current->next = NULL;
            free(current);
            current = NULL;
        }
        current = next;
    }
    list_arg->tail = list_arg->head;
    list_arg->size = 0;
}