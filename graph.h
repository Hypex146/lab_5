#ifndef GRAPH_H
#define GRAPH_H

typedef struct _Vertex{
	char *name;
	int x, y;
} Vertex;

typedef struct _Gline{
	struct _Vertex *self;
	int count_other;
	struct _LIST* other_list;
} Gline;

typedef struct _Gtable{
	int count_line;
	struct _Gline *line;
} Gtable;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "queue.h"

int get_int(int *a);
Gtable *g_init(void);
void add_vertex(Gtable *table);
void print_table(Gtable *table);
void del_table(Gtable *table);
void add_edge(Gtable *table);
void remove_vertex(Gtable *table);
void remove_edge(Gtable *table);
void draw_graph(Gtable *table);
void find_vertex(Gtable *table);
//void ostov(Gtable *table);
Gtable *ostov_gtable(Gtable *table);


#endif

