#ifndef __LIST_H__
#define __LIST_H__

typedef struct node
{
    void* data;
    struct node* next;
}node;


typedef struct list
{
    int size;
    node* head;
    node* tail;
}list;

list* list_create();
int list_append(list* list, void* data);
void* list_getnode(list* list, int num);
void list_for_each(list* list, void(*fun)(void*, void*),void* arg);
void list_destory(list* list);
void get_tail(list* list, void* data);
list* list_copy(list* list);
void list_clear(list* list);
#endif