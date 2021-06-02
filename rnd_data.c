#include "rnd_data.h"

int rnd_int(int start, int end){
    return (start + rand()%(end - start + 1));
}


char *rnd_str(int len){
	char *string = (char*)malloc((len+1)*sizeof(char));
	for (int i=0; i<len; i++){
		string[i] = (char)rnd_int(65, 90);
	}
	string[len] = '\0';
	return string;
}





