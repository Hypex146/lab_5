#include "graph.h"

void print_menu(void){
	printf("1) add vertex\n");
	printf("2) add edge\n");
	printf("3) remove vertex\n");
	printf("4) remove edge\n");
	printf("5) find a vertex\n");
	printf("6) find ostov\n");
	printf("7) print table\n");
	printf("8) draw graph\n");
	printf("9) delete table\n");
	printf("10) exit\n");
}


void UI(void){
	int choice;
	Gtable *table = NULL;
	do{
		choice = 0;
		if (!table){
			table = g_init();
			printf("table has been init\n");
		}
		print_menu();
		while (choice<1 || choice>10){
			get_int(&choice);
		}
		switch (choice){
			case 1:{
				add_vertex(table);
				break;
			}
			case 2:{
				add_edge(table);
				break;
			}
			case 3:{
				remove_vertex(table);
				break;
			}
			case 4:{
				remove_edge(table);
				break;
			}
			case 5:{
				find_vertex(table);
				break;
			}
			case 6:{
				Gtable *new_table = ostov_gtable(table);
				printf("Ostov found\n");
				print_table(new_table);
				draw_graph(new_table);
				system("./mkgv.sh");
				del_table(new_table);
				break;
			}
			case 7:{
				print_table(table);
				break;
			}
			case 8:{
				draw_graph(table);
				system("./mkgv.sh");
				break;
			}
			case 9:{
				del_table(table);
				table = NULL;
				break;
			}
			case 10:{
				del_table(table);
				table = NULL;
				break;
			}
		}
	} while (choice!=10);
}


int main(void){
	printf("Hello, world!\n");
	
	UI();
	
	printf("Bye!\n");
	return 0;
}


