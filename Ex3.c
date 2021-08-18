#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void);
void *add(void *pBuffer, int size);
void *remov(void *pBuffer, int size);
void show(void *pBuffer, int size);
void search(void *pBuffer, int size);

 
int main(){
    int choice, size = 0;
    void *pBuffer;

    pBuffer = (void *)malloc(sizeof(int));
    if (!pBuffer){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    *(int *)pBuffer = size;

    for(;;){
        choice = menu();
        switch (choice){
            case 1:
                size++;
                *(int *)pBuffer = size;
                pBuffer = add(pBuffer, size);
                break;
            case 2:
                pBuffer = remov(pBuffer, size);
                size--;
                *(int *)pBuffer = size;
                break;
            case 3:
                search(pBuffer, size);
                break;
            case 4:
                show(pBuffer, size);
                break;
            case 5:
                free(pBuffer);
                exit(0);
                break;
		}
    }
    return 0;
}


void *remov(void *pBuffer, int size){
    char name[10], nameaux[10];
    int person, i, c;

    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    
    printf("Name to remove: "); scanf("%s", name);


    for(i = size, c = 0; c < size; i--, c++){

        for(int k = 0; k < strlen(name)+1; k++){
            nameaux[k] = *(char *)(pBuffer + k + person*(size-i) + sizeof(int));
        }

        if(strcmp(nameaux, name) == 0){

            if(c != size){

                for(int j = 0; j < 10; j++){
                    *(char *)(pBuffer + j + person*(size-i) + sizeof(int)) = *(char *)(pBuffer + j - 1 + person*(size-i+1) + sizeof(int));
                }
                *(int *)(pBuffer+sizeof(char)*10+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+person*(size-i+1) + sizeof(int));
                *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i+1) + sizeof(int));

            }

            pBuffer = (char *)realloc(pBuffer, person*(size-1)+sizeof(int));
            if (!pBuffer){
                printf("Could not allocate required memory!\n");
                exit(1);
            }
            return pBuffer;
        }
    }

    return pBuffer;
}


void search(void *pBuffer, int size){
    char name[10], nameaux[10];
    int person, i, c;

    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    
    printf("Name to search: "); scanf("%s", name);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){

        for(int k = 0; k < strlen(name)+1; k++){
            nameaux[k] = *(char *)(pBuffer + k + person*(size-i));
        }
        if(strcmp(nameaux, name) == 0){
            printf("\nPerson[%d]: \tName: ", c);
            for (int k = 0; k < 10; k++){
                printf("%c", *(char *)(pBuffer + k + person*(size-i)));
            }
            printf("\n\t\tAge: %d\n\t\tTel: %d\n\n", 
            *(int *)(pBuffer+sizeof(char)*10+person*(size-i)), *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i)));
        }
    }
}


void *add(void *pBuffer, int size){
    char name[10];
    int age, tel, person;

    person = sizeof(int)*2+sizeof(char)*10;

    printf("\n-Add name: "); scanf("%s", name);
    printf("-Add age: "); scanf("%d", &age);
    printf("-Add tel: "); scanf("%d", &tel);

    pBuffer = (char *)realloc(pBuffer, person*size+sizeof(int));
    if (!pBuffer){
        printf("Could not allocate required memory!\n");
        exit(1);
    }


    pBuffer = pBuffer + sizeof(int);  
    pBuffer = pBuffer + person*(size-1);
    for(int i = 0; i < strlen(name)+1; i++){
        *(char *)(pBuffer + i) = name[i];
    }

    pBuffer = pBuffer + sizeof(char)*10;   
    *(int *)pBuffer = age;  

    pBuffer = pBuffer + sizeof(int);    
    *(int *)pBuffer = tel;               

    
    pBuffer = pBuffer - sizeof(int);
    pBuffer = pBuffer - sizeof(char)*10;  
    pBuffer = pBuffer - person*(size-1);
    pBuffer = pBuffer - sizeof(int);

    return pBuffer;
}


void show(void *pBuffer, int size){
    int person, i, c;
    
    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    printf("Size: %d\n\n", *(int *)pBuffer);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){
        printf("Person[%d]: \tName: ", c);
        for (int k = 0; k < 10; k++){
            printf("%c", *(char *)(pBuffer + k + person*(size-i)));
        }

        printf("\n\t\tAge: %d\n\t\tTel: %d\n\n", 
        *(int *)(pBuffer+sizeof(char)*10+person*(size-i)), *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i)));
    }
}


int menu(void){	
	int choice = 0;
    
	do{
		printf("\n1. Add;\n");
        printf("2. Remove;\n");
		printf("3. Search;\n");
        printf("4. Show all;\n");
		printf("5. Exit.\n");
		printf("\nPlease, choose what you want to do: "); scanf("%d", &choice);
	}while(choice < 1 || choice > 5);
	getchar();

	return choice;
}