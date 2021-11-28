#include <stdlib.h>
#include <math.h>
#include "buffer.h"

void buffer_init(buffer *b, unsigned int size)
{
    b->current = 0;
    b->next = 1;
    b->size = size;
    b->items = malloc(sizeof(int) * size);
}
void buffer_destroy(buffer *b)
{
    free(b->items);
}

void buffer_add(buffer *b, int item)
{
    if (b->current >= b->size)
    {
        return;
    }

    b->current = b->next++;
    b->items[b->current] = item;
}

int buffer_remove(buffer *b)
{
    int item = b->items[b->current];
    b->next--;
    b->current--;

    if (b->current < 0)
    {
        b->current = 0;
        b->next = 1;
    }
    return item;
}

int buffer_current(const buffer const *b)
{
    return b->items[b->current];
}