#include "fs_StackList.h"

int Stack_Create(int L) {
    fs_stack_head *a;
    a = malloc(sizeof(fs_stack_head));
    a->len = 0;
    a->maxlen = L;
    a->next = NULL;
    return a;
}

int Stack_AddHead(fs_stack_head *a, content_type data) {
    if (a->len == a->maxlen) return -1;
    fs_stack_elem *newelem = malloc(sizeof(fs_stack_elem));
    newelem->data = data;
    newelem->next = a->next;
    newelem->prev = a;
    if (a->next != NULL) a->next->prev = newelem;
    a->next = newelem;
    a->len++;
    return 1;
}

int Stack_DelHead(fs_stack_head *a) {
    if (a->len == 0) return -1;
    fs_stack_elem *temp;
    temp = a->next;
    if (a->next->next != NULL) a->next->next->prev = a;
    a->next = a->next->next;
    free(temp);
    a->len--;
    if (a->len == 0) a->next = NULL;
    return 1;
}

int Stack_Print(fs_stack_head *a) {
    if (a->len == 0) return -1;
    fs_stack_elem *temp = a->next;
    //printf("%d", temp->data);
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    return 1;
}

content_type Stack_GetHead(fs_stack_head *a) {
    if (a->len == 0) return -1;
    return a->next->data;
}

content_type Stack_PopHead(fs_stack_head *a) {
    if (a->len == 0) return -1;
    content_type b;
    b = Stack_GetHead(a);
    Stack_DelHead(a);
    return b;
}
