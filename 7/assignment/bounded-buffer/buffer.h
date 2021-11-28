typedef struct
{
    int next;
    int current;
    unsigned int size;
    int *items;
} buffer;

void buffer_init(buffer *b, unsigned int size);
void buffer_destroy(buffer *b);

void buffer_add(buffer *b, int item);
int buffer_remove(buffer *b);
int buffer_current(const buffer const *b);