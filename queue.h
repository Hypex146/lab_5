#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"

typedef List Queue;
Queue *q_init(void);
int q_push(Queue *queue, Vertex *vertex);
Vertex *q_pop(Queue *queue);
int q_len(Queue *queue);
int q_clear(Queue *queue);

#endif