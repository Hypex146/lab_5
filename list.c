#include "list.h"


static List_element *list_element_init(Vertex *vertex){
    List_element *new_list_element = (List_element*)malloc(1*sizeof(List_element));
    new_list_element->vertex = vertex;
    new_list_element->next = NULL;
    return new_list_element;
}


List *list_init(void){
    List *new_list = (List*)malloc(1 * sizeof(List));
    List_element *header = list_element_init(NULL);
    new_list->head = header;
    return new_list;
}


int list_insert(List *list, Vertex *vertex, int index){
    int i = 0;
    List_element *now = list->head;
    while (i < index && now->next){
        i++;
        now = now->next;
    }
    List_element *new_list_element = list_element_init(vertex);
    new_list_element->next = now->next;
    now->next = new_list_element;
    return 0;
}


int list_remove(List *list, int index){
    if(list->head->next){
        int i = 0;
        List_element *now = list->head;
        while (i < index && now->next->next){
            i++;
            now = now->next;
        }
        List_element *for_del = now->next;
        now->next = now->next->next;
		//free(for_del->string);
        free(for_del);
		return 0;
    } else{
		return -1;
	}
}


int list_take(List *list, int index, Vertex **ret){
	if (list->head->next){
		int i = 0;
		List_element *now = list->head;
		while(i <= index && now->next){
			i++;
			now = now->next;
		}
		*ret = now->vertex;
		return 0;
	} else{
		return -1;
	}
}


int list_value_count(List *list, Vertex *vertex){
	if (list->head->next){
		int count = 0;
		List_element *now = list->head->next;
		while(now){
			if (now->vertex == vertex){
				count++;
			}
			now = now->next;
		}
		return count;
	} else{
		return -1;
	}
}


int list_value_index(List *list, Vertex *vertex){
	if (list->head->next){
		int i = 0;
		List_element *now = list->head->next;
		while(now){
			if (now->vertex == vertex){
				return i;
			}
			i++;
			now = now->next;
		}
	} else{
		return -1;
	}
	return -1;
}


int list_len(List* list){
    int count = 0;
    List_element *now = list->head;
    while (now->next){
        count++;
        now = now->next;
    }
    return count;
}


int list_write(List *list){
    if(list->head->next) {
        List_element *now = list->head->next;
        while (now){
            printf("%s ", now->vertex->name);
            now = now->next;
        }
    }
    return 0;
}


int list_clear(List *list){
    List_element *now = list->head;
    List_element *tmp = NULL;
    while (now->next){
        tmp = now->next;
		//free(now->string);
        free(now);
        now = tmp;
    }
	//free(now->string);
    free(now);
    free(list);
    return 0;
}

