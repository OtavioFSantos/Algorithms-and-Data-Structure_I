#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(void *pBuffer);
void add(void *pBuffer);
void *remov(void *pBuffer);
void show(void *pBuffer);
void *search(void *pBuffer);

typedef struct{
    char name[20];
    int age;
}Person;

Person people[10];
 
int main(){
    void *pBuffer;

    pBuffer = (void *)calloc(3, sizeof(int));
    if (!pBuffer){
        printf("Could not allocate required memory!\n");
        return -1;
    }
    
    *(int *)(pBuffer + sizeof(int)) = 0;

    for(;;){
        *(int *)pBuffer = menu(pBuffer);
        
        switch(*(int *)pBuffer){
            case 1:
                add(pBuffer);
                break;
            case 2:
                pBuffer = remov(pBuffer);
                break;
            case 3:
                pBuffer = search(pBuffer);
                break;
            case 4:
                show(pBuffer);
                break;
            case 5:
                free(pBuffer);
                exit(0);
                break;
		}
    }
    return 0;
}


void add(void *pBuffer){
    if(*(int *)(pBuffer + sizeof(int)) >= 10){
        printf("Maximum capacity!\n");
        return;
    }
    printf("\n-Insert name: "); scanf("%s", (people+*(int *)(pBuffer + sizeof(int)))->name);
    printf("-Insert age: "); scanf("%d", &(people+*(int *)(pBuffer + sizeof(int)))->age);

    *(int *)(pBuffer + sizeof(int)) += 1; 
}


void show(void *pBuffer){
    if(*(int *)(pBuffer + sizeof(int)) == 0){
        printf("\nNo data yet!\n");
        return;
    }
    printf("\n-Size: %d\n", *(int *)(pBuffer + sizeof(int)));

    for(*(int *)(pBuffer+sizeof(int)*2) = 0; *(int *)(pBuffer+sizeof(int)*2) < *(int *)(pBuffer+sizeof(int)); *(int *)(pBuffer+sizeof(int)*2) += 1){
        printf("\nName: %s\nAge: %d\n", (people+*(int *)(pBuffer+sizeof(int)*2))->name, (people+*(int *)(pBuffer+sizeof(int)*2))->age);
    }
}


void *remov(void *pBuffer){
    if(*(int *)(pBuffer + sizeof(int)) == 0){
        printf("\nNo data yet!\n");
        return pBuffer;
    }
    
    pBuffer = (void *)realloc(pBuffer, sizeof(int)*3+sizeof(char)*20);

    printf("\nInsert name to remove: "); scanf("%s", (char *)(pBuffer+sizeof(int)*3));

    for(*(int *)(pBuffer+sizeof(int)*2) = 0; *(int *)(pBuffer+sizeof(int)*2) < *(int *)(pBuffer+sizeof(int)); *(int *)(pBuffer+sizeof(int)*2) += 1){

        if(strcmp((char *)(pBuffer+sizeof(int)*3), (people+*(int *)(pBuffer+sizeof(int)*2))->name) == 0){
            for(; *(int *)(pBuffer+sizeof(int)*2) < (*(int *)(pBuffer+sizeof(int))-1); *(int *)(pBuffer+sizeof(int)*2) += 1){ 
                strcpy((people+*(int *)(pBuffer+sizeof(int)*2))->name, (people+1+*(int *)(pBuffer+sizeof(int)*2))->name);
                (people+*(int *)(pBuffer+sizeof(int)*2))->age = (people+1+*(int *)(pBuffer+sizeof(int)*2))->age;
            }

            *(int *)(pBuffer + sizeof(int)) -= 1;
            return pBuffer;
        }
    }
    printf("Name not found!\n");
    return pBuffer;
}


void *search(void *pBuffer){
    if(*(int *)(pBuffer + sizeof(int)) == 0){
        printf("\nNo data yet!\n");
        return pBuffer;
    }
    pBuffer = (void *)realloc(pBuffer, sizeof(int)*3+sizeof(char)*20);

    printf("\nInsert name to search: "); scanf("%s", (char *)(pBuffer+sizeof(int)*3));

    for(*(int *)(pBuffer+sizeof(int)*2) = 0; *(int *)(pBuffer+sizeof(int)*2) < *(int *)(pBuffer+sizeof(int)); *(int *)(pBuffer+sizeof(int)*2) += 1){

        if(strcmp((char *)(pBuffer+sizeof(int)*3), (people+*(int *)(pBuffer+sizeof(int)*2))->name) == 0){

            printf("\nName: %s\nAge: %d\n", (people+*(int *)(pBuffer+sizeof(int)*2))->name, (people+*(int *)(pBuffer+sizeof(int)*2))->age);
            return pBuffer;
        }
    }
    
    printf("Name not found!\n");
    return pBuffer;
}

int menu(void *pBuffer){
	do{
		printf("\n1. Add;\n");
        printf("2. Remove;\n");
		printf("3. Search;\n");
        printf("4. Show all;\n");
		printf("5. Exit.\n");
		printf("\nPlease, choose what you want to do: "); scanf("%d", &*(int *)pBuffer);
	}while(*(int *)pBuffer < 1 || *(int *)pBuffer > 5);
	getchar();

	return *(int *)pBuffer;
}