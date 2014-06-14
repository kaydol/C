typedef int content_type;

typedef struct fs_stack_elem {
    content_type data;
    struct fs_stack_elem *next, *prev;
} fs_stack_elem;

typedef struct fs_stack_head {
    int len, maxlen;
    struct fs_stack_elem *next;
} fs_stack_head;

int Stack_Create(int);
int Stack_AddHead(fs_stack_head*, content_type);
int Stack_DelHead(fs_stack_head*);
int Stack_Print(fs_stack_head*);
content_type Stack_GetHead(fs_stack_head*);
content_type Stack_PopHead(fs_stack_head*);