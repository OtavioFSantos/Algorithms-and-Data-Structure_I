#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
char* add(char *names);
char* remov(char *names);
void show(char *names);
 
int main(){
    int choice;
    char *names;

    names = (char *)malloc(1);
    if (!names){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    for(;;){
        choice = menu();
        switch (choice){
            case 1:
                names = add(names);
                break;
            case 2:
                names = remov(names);
                break;
            case 3:
                show(names);
                break;
            case 4:
                free(names);
                exit(0);
                break;
		}
    }
    return 0;
}

void show(char *names){
    if(!strlen(names)){
        printf("\nNo names!\n");
    }else{
        printf("\n-All names:\n%s\n", names);
    }
}

char* remov(char *names){
    char buffer[10];
    int i = 0;
    printf("\n-Remove name: "); scanf("%s", buffer);

    char *pch = strstr(names, buffer);

    if(pch){

        for(i = 0; i < strlen(buffer)+1; i++){
            strcpy(pch, (pch+1));
        }
        names = (char *)realloc(names, strlen(names)-i);

    }else{
        printf("\nName not found!\n");
    }

    return names;
}

char* add(char *names){
    char buffer[10];
    printf("\n-Add name: "); scanf("%s", buffer);
    strcat(buffer, " ");

    names = (char *)realloc(names, strlen(names)+strlen(buffer));
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