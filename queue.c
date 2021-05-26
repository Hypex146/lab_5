#include "queue.h"

Queue *q_init(void){
	return list_init();
}


int q_push(Queue *queue, Vertex *vertex){
	return list_insert(queue, vertex, list_len(queue));
}


Vertex *q_pop(Queue *queue){
	Vertex *vertex = NULL;
	list_take(queue, 0, &vertex);
	list_remove(queue, 0);
	return vertex;
}


int q_len(Queue *queue){
	return list_len(queue);
}


int q_clear(Queue *queue){
	return list_clear(queue);
}

