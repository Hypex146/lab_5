#include "graph.h"

void print_menu(void){
	printf("0) load graph\n");
	printf("1) rnd graph\n");
	printf("2) add vertex\n");
	printf("3) add edge\n");
	printf("4) remove vertex\n");
	printf("5) remove edge\n");
	printf("6) find a vertex\n");
	printf("7) find ostov\n");
	printf("8) find the path length\n");
	printf("9) print table\n");
	printf("10) draw graph\n");
	printf("11) unload graph\n");
	printf("12) delete table\n");
	printf("13) timing find way\n");
	printf("14) exit\n");
}


void UI(void){
	int choice;
	Gtable *table = NULL;
	do{
		choice = -1;
		if (!table){
			table = g_init();
			//printf("table has been init\n");
		}
		print_menu();
		while (choice<0 || choice>14){
			get_int(&choice);
		}
		switch (choice){
			case 0:{
				if (table){
					del_table(table);
					table = NULL;
				}
				table = graph_load();
				break;
			}
			case 1:{
				if (table){
					del_table(table);
					table = NULL;
				}
				table = rnd_graph();
				break;
			}
			case 2:{
				add_vertex(table);
				break;
			}
			case 3:{
				add_edge(table);
				break;
			}
			case 4:{
				remove_vertex(table);
				break;
			}
			case 5:{
				remove_edge(table);
				break;
			}
			case 6:{
				find_vertex(table);
				break;
			}
			case 7:{
				Gtable *new_table = ostov_gtable(table);
				printf("Ostov found\n");
				print_table(new_table);
				draw_graph(new_table);
				system("./mkgv.sh");
				del_table(new_table);
				break;
			}
			case 8:{
				find_way(table);
				break;
			}
			case 9:{
				print_table(table);
				break;
			}
			case 10:{
				draw_graph(table);
				system("./mkgv.sh");
				break;
			}
			case 11:{
				graph_unload(table);
				break;
			}
			case 12:{
				del_table(table);
				table = NULL;
				break;
			}
			case 13:{
				timing_search();
				break;
			}
			case 14:{
				del_table(table);
				table = NULL;
				break;
			}
		}
	} while (choice!=14);
}


int main(void){
	printf("Hello, world!\n");
	
	UI();
	
	printf("Bye!\n");
	return 0;
}


