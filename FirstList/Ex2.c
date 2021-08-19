#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
char* add(char *names);
char* remov(char *names);
void show(char *names, int sizeName);

int sizeName = 0;
 
int main(){
    int choice;
    char *names;

    names = (char *)calloc(1, 1);
    if (!names){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    for(;;){
        choice = menu();
        switch (choice){
            case 1:
                names = add(names);
                sizeName++;
                break;
            case 2:
                names = remov(names);
                break;
            case 3:
                show(names, sizeName);
                break;
            case 4:
                free(names);
                exit(0);
                break;
		}
    }
    return 0;
}

void show(char *names, int sizeName){
    if(sizeName == 0){
        printf("\nNo names yet!\n");
        return;
    }
    
    printf("\n-All names:\n%s\n", names);
}

char* remov(char *names){
    char buffer[10];
    int i = 0, size;
    printf("\n-Remove name: "); scanf("%s", buffer);

    char *pch = strstr(names, buffer);
    size = strlen(names);

    if(pch){

        for(i = 0; i < strlen(buffer)+1; i++){
            memmove(pch, (pch+1), strlen(pch+1) + 1);
        }

        if(size == i){
            names = (char *)realloc(names, size-i+2);
            sizeName--;
            return names;
        }
        names = (char *)realloc(names, size-i+1);

        sizeName--;

    }else{
        printf("\nName not found!\n");
    }

    return names;
}

char* add(char *names){
    char buffer[10];
    printf("\n-Add name: "); scanf("%s", buffer);
    strcat(buffer, " ");

    names = (char *)realloc(names, strlen(names)+strlen(buffer)+1);
    strcat(names, buffer);

    return names;
}

int menu(void){	
	int choice = 0;
    
	do{
		printf("\n1. Add;\n");
        printf("2. Remove;\n");
		printf("3. Show;\n");
		printf("4. Exit.\n");
		printf("\nPlease, choose what you want to do: "); scanf("%d", &choice);
	}while(choice < 1 || choice > 4);
	getchar();

	return choice;
}
