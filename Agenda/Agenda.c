#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void *pBuffer);
void add(void *pBuffer, void *pSentinel);
// void *remov(void *pBuffer);
// void show(void *pBuffer);
// void search(void *pBuffer);

//personsize = name[20] + age + tel + nextAddress
#define PERSON_SIZE (sizeof(char)*20 + sizeof(int) + sizeof(long int) + sizeof(void **))
 
int main(){
    void *pBuffer, *pSentinel;

    //pBuffer = choice + i
    pBuffer = (void *)calloc(2, sizeof(int));
    //pSentinel = size + sentinel(first address)
    pSentinel = (void *)calloc(1, (sizeof(int) + sizeof(void *)));

    if (!pBuffer || !pSentinel){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    //size = 0
    *(int *)pSentinel = 0;

    for(;;){
        menu(pBuffer);
        switch(*(int *)pBuffer){
            case 1:
                add(pBuffer, pSentinel);
                break;
            case 2:
                // pBuffer = remov(pBuffer);
                // *(int *)pBuffer = size;
                break;
            case 3:
                //search(pBuffer);
                break;
            case 4:
                //show(pBuffer);
                break;
            case 5:
                free(pBuffer);
                free(pSentinel);
                exit(0);
                break;
		}
    }
    return 0;
}

/*
void *remov(void *pBuffer){
    char name[10], nameaux[10];
    int person, i, c, k, j;

    if(size == 0){
        printf("\nNo data yet!\n");
        return pBuffer;
    }

    person = sizeof(int)*2+sizeof(char)*10;

    
    printf("Name to remove: "); scanf("%s", name);


    for(i = size, c = 1; c < size+1; i--, c++){

        for(k = 0; k < strlen(name)+1; k++){
            nameaux[k] = *(char *)(pBuffer + k + person*(size-i) + sizeof(int));
        }

        if(strcmp(nameaux, name) == 0){

            if(c != size){

                for(j = 0; j < 10; j++){
                    *(char *)(pBuffer + j + person*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + person*(size-i+1) + sizeof(int));
                }
                *(int *)(pBuffer+sizeof(char)*10+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+person*(size-i+1) + sizeof(int));
                *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i+1) + sizeof(int));


                for(i = i - 1; c < size-1; i--, c++){
                    for(j = 0; j < 10; j++){
                        *(char *)(pBuffer + j + person*(size-i) + sizeof(int)) = *(char *)(pBuffer + j + person*(size-i+1) + sizeof(int));
                    }
                    *(int *)(pBuffer+sizeof(char)*10+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+person*(size-i+1) + sizeof(int));
                    *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i) + sizeof(int)) = *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i+1) + sizeof(int));
                }

            }

            pBuffer = (char *)realloc(pBuffer, person*(size-1)+sizeof(int));
            if (!pBuffer){
                printf("Could not allocate required memory!\n");
                exit(1);
            }
            size--;
            return pBuffer;
        }
    }

    return pBuffer;
}*/

/*
void search(void *pBuffer){
    char name[10], nameaux[10];
    int person, i = 0, c = 0, k = 0;

    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    
    printf("Name to search: "); scanf("%s", name);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){

        for(k = 0; k < strlen(name)+1; k++){
            nameaux[k] = *(char *)(pBuffer + k + person*(size-i));
        }
        if(strcmp(nameaux, name) == 0){
            printf("\nPerson[%d]: \tName: ", c);
            for (k = 0; *(char *)(pBuffer + k + person*(size-i)) >= 'a' && *(char *)(pBuffer + k + person*(size-i)) <= 'z'; k++){
                printf("%c", *(char *)(pBuffer + k + person*(size-i)));
            }
            printf("\n\t\tAge: %d\n\t\tTel: %d\n\n", 
            *(int *)(pBuffer+sizeof(char)*10+person*(size-i)), *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i)));
        }
    }
}*/


void add(void *pBuffer, void *pSentinel){

    //*(int *)(pPeople+sizeof(int)) = (void *)calloc(1, PERSON_SIZE);
    void *pPerson = (void *)malloc(PERSON_SIZE);
    if (!pPerson){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    printf("\n-Add name: "); scanf("%19[^\n]c", pPerson); getchar();
    printf("-Add age: "); scanf("%ld", &*(int *)(pPerson+sizeof(char)*20));
    printf("-Add tel: "); scanf("%d", &*(long int *)(pPerson+sizeof(char)*20+sizeof(int)));
    *(void **)(pPerson+sizeof(char)*20+sizeof(int)+ sizeof(long int)) = NULL;

    printf("Name: %s, age: %d, tel: %ld\n", pPerson, *(int *)(pPerson+sizeof(char)*20), *(long int *)(pPerson+sizeof(char)*20+sizeof(int)));


    //size++
    *(int *)pSentinel += 1;

    if(*(int *)pSentinel == 0){
        //pSentinel receive first address
        *(void **)(pSentinel+sizeof(int)) = &pPerson;
    }else{
        for(;;){

        }
    }
}

/*
void show(void *pBuffer){
    int person, i = 0, c = 0, k = 0;
    
    person = sizeof(int)*2+sizeof(char)*10;

    if(size == 0){
        printf("\nNo data yet!\n");
        return;
    }
    printf("Size: %d\n\n", *(int *)pBuffer);


    pBuffer = pBuffer + sizeof(int); 

    for(i = size, c = 0; c < size; i--, c++){
        
        printf("Person[%d]: \tName: ", c);
        for(k = 0; *(char *)(pBuffer + k + person*(size-i)) >= 'a' && *(char *)(pBuffer + k + person*(size-i)) <= 'z'; k++){
            printf("%c", *(char *)(pBuffer + k + person*(size-i)));
        }

        printf("\n\t\tAge: %d\n\t\tTel: %d\n\n", 
        *(int *)(pBuffer+sizeof(char)*10+person*(size-i)), *(int *)(pBuffer+sizeof(char)*10+sizeof(int)+person*(size-i)));
    }
}*/


void menu(void *pBuffer){
    do{
		printf("\n1. Add;\n");
        printf("2. Remove;\n");
		printf("3. Search;\n");
        printf("4. Show all;\n");
		printf("5. Exit.\n");
		printf("\nPlease, choose what you want to do: "); scanf("%d", &*(int *)pBuffer);
	}while(*(int *)pBuffer < 1 || *(int *)pBuffer > 5);
    getchar();
}
