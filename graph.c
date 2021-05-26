#include "graph.h"

static char *get_str(void){
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }
    return res;
}


static char *fget_str(FILE *file){
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n == EOF) return NULL;
        else if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(file, "%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}


int get_int(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0) return 1;
        if (n == 0){
            printf("Error!\n");
            scanf("%*c");
        }
    } while (n == 0);
    return 0;
}


Gtable *g_init(void){
	Gtable *table = NULL;
	table = (Gtable*)malloc(1*sizeof(Gtable));
	table->count_line = 0;
	table->line = NULL;
	return table;
}


static Vertex *find_vertex_by_name(Gtable *table, char *name){
	Vertex *vertex = NULL;
	if (table){
		for (int i=0; i<table->count_line; i++){
			//printf("find_vertex_by_name -> %s | our name -> %s\n", table->line[i].self->name, name);
			if (!strcmp(table->line[i].self->name, name)){
				vertex = table->line[i].self;
			}
		}
		if (!vertex){
			//printf("Vertex not found\n");
		}
	} else{
		//printf("Table is not init\n");
	}
	return vertex;
}


static char *enter_vertex_name(Gtable *table, int new){
	char *name = NULL;
	int code = 0;
	do{
		code = 0;
		if (name){
			free(name);
			name = NULL;
		}
		name = get_str();
		if (!new){
			if (!find_vertex_by_name(table, name)){
			printf("There is no such vertex\n");
			code = 1;
			}
		} else{
			if (find_vertex_by_name(table, name)){
			printf("The name is already taken\n");
			code = 1;
			}
		}
	} while (code);
	return name;
}


static Vertex *create_vertex(Gtable *table){
	Vertex *vertex = NULL;
	char *name = NULL;
	int x = 0, y = 0;
	printf("Enter the name of vertex\n");
	scanf("%*c");
	int code = 0;
	name = enter_vertex_name(table, 1);
	printf("Enter the x position\n");
	get_int(&x);
	printf("Enter the y position\n");
	get_int(&y);
	vertex = (Vertex*)malloc(1*sizeof(Vertex));
	vertex->name = name;
	vertex->x = x;
	vertex->y = y;
	return vertex;
}


void add_vertex(Gtable *table){
	Vertex *vertex = create_vertex(table);
	table->count_line++;
	table->line = realloc(table->line, table->count_line*sizeof(Gline));
	table->line[table->count_line-1].self = vertex;
	table->line[table->count_line-1].count_other = 0;
	table->line[table->count_line-1].other_list = list_init();
}


void add_edge(Gtable *table){
	char *first_name = NULL;
	char *second_name = NULL;
	Vertex *first = NULL;
	Vertex *second = NULL;
	printf("Enter the name of first vertex\n");
	scanf("%*c");
	first_name = enter_vertex_name(table, 0);
	first = find_vertex_by_name(table, first_name);
	free(first_name);
	printf("Enter the name of second vertex\n");
	second_name = enter_vertex_name(table, 0);
	second = find_vertex_by_name(table, second_name);
	free(second_name);
	if (first == second) return;
	int t = 0;
	for (int i=0; i<table->count_line; i++){
		if (table->line[i].self == first){
			if (list_value_count(table->line[i].other_list, second)<1){
				list_insert(table->line[i].other_list, second, 0);
			}
			t++;
			if (t==2) break;
		}
		if (table->line[i].self == second){
			if (list_value_count(table->line[i].other_list, first)<1){
				list_insert(table->line[i].other_list, first, 0);
			}
			t++;
			if (t==2) break;
		}
	}
}


void remove_vertex(Gtable *table){
	Vertex *vertex = NULL;
	char *name = NULL;
	printf("Enter the vertex name\n");
	scanf("%*c");
	name = enter_vertex_name(table, 0);
	vertex = find_vertex_by_name(table, name);
	int index_edge = -1;
	
	for (int i=0; i<table->count_line; i++){
		if (table->line[i].self != vertex){
			index_edge = list_value_index(table->line[i].other_list, vertex);
			if (index_edge != -1){
				list_remove(table->line[i].other_list, index_edge);
			}
		}
	}
	
	for (int i=0; i<table->count_line; i++){
		if (table->line[i].self == vertex){
			list_clear(table->line[i].other_list);
			table->count_line--;
			
			if (i==0){
                Gline *new_line = (Gline*)malloc(table->count_line*sizeof(Gline));
                memcpy(new_line, table->line+1, table->count_line*sizeof(Gline));
                free(table->line);
                table->line = new_line;
			} else if (i >= table->count_line){
				table->line = (Gline*)realloc(table->line, table->count_line*sizeof(Gline));
				
			} else{
				Gline *new_line = (Gline*)malloc(table->count_line*sizeof(Gline));
				memcpy(new_line, table->line, i*sizeof(Gline));
                memcpy(new_line+i, table->line+i+1, (table->count_line-i)*sizeof(Gline));
				free(table->line);
				table->line = new_line;
			}
			
		}
	}
	if (table->count_line == 0) table->line = NULL;
	free(vertex->name);
	free(vertex);
	free(name);
}


void remove_edge(Gtable *table){
	char *first_name = NULL;
	char *second_name = NULL;
	Vertex *first = NULL;
	Vertex *second = NULL;
	printf("Enter the name of first vertex\n");
	scanf("%*c");
	first_name = enter_vertex_name(table, 0);
	first = find_vertex_by_name(table, first_name);
	free(first_name);
	printf("Enter the name of second vertex\n");
	second_name = enter_vertex_name(table, 0);
	second = find_vertex_by_name(table, second_name);
	free(second_name);
	
	int index_edge = -1;
	int t = 0;
	for (int i=0; i<table->count_line; i++){
		if (table->line[i].self == first){
			index_edge = list_value_index(table->line[i].other_list, second);
			if (index_edge != -1){
				list_remove(table->line[i].other_list, index_edge);
			}
			t++;
			if (t==2) break;
		}
		
		if (table->line[i].self == second){
			index_edge = list_value_index(table->line[i].other_list, first);
			if (index_edge != -1){
				list_remove(table->line[i].other_list, index_edge);
			}
			t++;
			if (t==2) break;
		}
	}
}


void print_table(Gtable *table){
	if (table->count_line > 0){
		printf("Table:\n");
		for (int i=0; i<table->count_line; i++){
			printf("%s | ", table->line[i].self->name);
			list_write(table->line[i].other_list);
			printf("\n");
		}
	} else{
		printf("Table is empty!\n");
	}
}


static void create_meta_code_for_gv(Gtable *table, FILE *file){
	fprintf(file, "digraph Tree{\n");
	Vertex *edge = NULL;
	for (int i=0; i<table->count_line; i++){
		fprintf(file, "  \"%s\";\n", table->line[i].self->name);
		for (int j=0; j<list_len(table->line[i].other_list); j++){
			list_take(table->line[i].other_list, j, &edge);
			fprintf(file, "  \"%s\" -> \"%s\";\n", table->line[i].self->name, edge->name);
		}
	}
	fprintf(file, "}\n");
}


void draw_graph(Gtable *table){
	if (table){
		if (table->count_line>0){
			char name[] = "gv.gv";
			FILE *file;
			if ((file = fopen(name, "w")) == NULL)
			{
				printf("File not found\n");
				return;
			}
			create_meta_code_for_gv(table, file);
			fclose(file);
		} else{
			printf("Graph have not vertex\n");
		}
	} else{
		printf("Graph is not init\n");
	}
}


void del_table(Gtable *table){
	if (table){
		for (int i=0; i<table->count_line; i++){
			free(table->line[i].self->name);
			free(table->line[i].self);
			list_clear(table->line[i].other_list);
		}
		if (table->line) free(table->line);
		free(table);
	} else{
		printf("Table is not init\n");
	}
}


static void add_vertex_static(Gtable *table, Vertex *vertex){
	table->count_line++;
	table->line = realloc(table->line, table->count_line*sizeof(Gline));
	table->line[table->count_line-1].self = vertex;
	table->line[table->count_line-1].count_other = 0;
	table->line[table->count_line-1].other_list = list_init();
}


static void add_edge_static(Gtable *table, Vertex *first, Vertex *second){
	int t = 0;
	for (int i=0; i<table->count_line; i++){
		if (table->line[i].self == first){
			if (list_value_count(table->line[i].other_list, second)<1){
				list_insert(table->line[i].other_list, second, 0);
			}
			t++;
			if (t==2) break;
		}
		if (table->line[i].self == second){
			if (list_value_count(table->line[i].other_list, first)<1){
				list_insert(table->line[i].other_list, first, 0);
			}
			t++;
			if (t==2) break;
		}
	}
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static Vertex *find_vertex_ptr(Gtable *table){
	if (table->count_line>0){
		char *start_name = NULL;
		char *end_name = NULL;
		Vertex *start = NULL;
		Vertex *end = NULL;
		printf("Enter the start vertex name\n");
		scanf("%*c");
		start_name = enter_vertex_name(table, 0);
		start = find_vertex_by_name(table, start_name);
		free(start_name);
		printf("Enter the name of the vertex you are looking for\n");
		end_name = enter_vertex_name(table, 0);
		end = find_vertex_by_name(table, end_name);
		free(end_name);
		if (start == end) return start;
		
		Queue *queue = q_init();
		List *burn = list_init();
		q_push(queue, start);
		list_insert(burn, start, 0);
		Vertex *vertex = NULL;
		while (q_len(queue)>0){
			vertex = q_pop(queue);
			int i = 0;
			while (table->line[i].self != vertex){
				i++;
			}
			for (int j=0; j<list_len(table->line[i].other_list); j++){
				Vertex *tmp = NULL;
				list_take(table->line[i].other_list, j, &tmp);
				if (list_value_count(burn, tmp)==0){
					if (tmp==end){
						q_clear(queue);
						list_clear(burn);
						return tmp;
					}
					q_push(queue, tmp);
					list_insert(burn, tmp, 0);
				}
			}
		}
		printf("Vertex not found\n");
		q_clear(queue);
		list_clear(burn);
		return NULL;
	} else{
		printf("Graph is empty\n");
		return NULL;
	}
}


void find_vertex(Gtable *table){
	Vertex *vertex = find_vertex_ptr(table);
	if (vertex){
		printf("We found vertex\n");
		printf("name: %s\n", vertex->name);
		printf("x: %d | y: %d\n", vertex->x, vertex->y);
	}
}


static void ostov_gtable_rec(Gtable *table, Gtable *new_table, List *parsed, Vertex *vertex){
	int i = 0;
	while (strcmp(table->line[i].self->name, vertex->name)!=0){
		i++;
	}
	for (int j=0; j<list_len(table->line[i].other_list); j++){
		Vertex *probably_vertex = NULL;
		list_take(table->line[i].other_list, j, &probably_vertex);
		if (list_value_count(parsed, probably_vertex)==0){
			Vertex *verified_vertex = NULL;
			verified_vertex = (Vertex*)malloc(1*sizeof(Vertex));
			memcpy(verified_vertex, probably_vertex, 1*sizeof(Vertex));
			char *name = NULL;
			name = (char*)malloc((strlen(table->line[0].self->name)+1)*sizeof(char));
			memcpy(name, probably_vertex->name, (strlen(probably_vertex->name)+1)*sizeof(char));
			verified_vertex->name = name;
			add_vertex_static(new_table, verified_vertex);
			add_edge_static(new_table, vertex, verified_vertex);
			list_insert(parsed, probably_vertex, 0);
			ostov_gtable_rec(table, new_table, parsed, verified_vertex);
		}
	}
}


Gtable *ostov_gtable(Gtable *table){
	if (table->count_line>0){
		List *parsed = NULL;
		Gtable *new_table = NULL;
		new_table = g_init();
		parsed = list_init();
		Vertex *first_vertex = NULL;
		first_vertex = (Vertex*)malloc(1*sizeof(Vertex));
		memcpy(first_vertex, table->line[0].self, 1*sizeof(Vertex));
		char *name = NULL;
		name = (char*)malloc((strlen(table->line[0].self->name)+1)*sizeof(char));
		memcpy(name, table->line[0].self->name, (strlen(table->line[0].self->name)+1)*sizeof(char));
		//printf("s-> %s\n", name);
		first_vertex->name = name;
		//printf("E1\n");
		add_vertex_static(new_table, first_vertex);
		//printf("E2\n");
		list_insert(parsed, table->line[0].self, 0);
		ostov_gtable_rec(table, new_table, parsed, first_vertex);
		list_clear(parsed);
		return new_table;
	} else{
		printf("Graph is empty\n");
		return NULL;
	}
}


/*
void ostov(Gtable *table){
	Gtable *new_table = NULL;
	new_table = ostov_gtable(table);
	printf("Ostov found\n");
	print_table(new_table);
	draw_graph(new_table);
	del_table(new_table);
}
*/



