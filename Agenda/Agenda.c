#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void *pBuffer);
void add(void *pBuffer, void *pSentinel, void *aux);
void showall(void *pBuffer, void *pSentinel, void *aux);

//personsize = name[20] + age + tel + previousAddress + nextAddress
#define PERSON_SIZE (sizeof(char)*20+sizeof(int)+sizeof(long int)+sizeof(void **)*2)
#define NEXT (sizeof(char)*20+sizeof(int)+sizeof(long int)+sizeof(void **))
#define PREV (sizeof(char)*20+sizeof(int)+sizeof(long int))
#define PTOP (sizeof(int))
#define FIRST (sizeof(int)+sizeof(void **))
#define LAST (sizeof(int))


int main(){
    void *pBuffer, *pSentinel;

    void *aux = *(void **)calloc(1, PERSON_SIZE);

    //pSentinel = size + last address + first address
    pSentinel = (void *)calloc(1, (sizeof(int) + sizeof(void **)*2));

    //pBuffer = choice + pointer to pointer
    pBuffer = (void *)calloc(1, (sizeof(int) + sizeof(void **)));

    if(!pBuffer || !pSentinel){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    //size = 0
    *(int *)pSentinel = 0;

    //last address = NULL
    *(void **)(pSentinel+sizeof(int)) = NULL;

    //first address = NULL
    *(void **)(pSentinel+FIRST) = NULL;

    *(void **)(pBuffer+PTOP) = NULL;

    for(;;){
        menu(pBuffer);
        switch(*(int *)pBuffer){
            case 1:
                add(pBuffer, pSentinel, aux);
                break;
            case 2:
                // pBuffer = remov(pBuffer);
                // *(int *)pBuffer = size;
                break;
            case 3:
                //search(pBuffer);
                break;
            case 4:
                showall(pBuffer, pSentinel, aux);
                break;
            case 5:
                free(pBuffer);
                free(pSentinel);
                free(aux);
                exit(0);
                break;
		}
    }
    return 0;
}



void add(void *pBuffer, void *pSentinel, void *aux){
    void *aux2;

    void *pPerson = (void *)malloc(PERSON_SIZE);
    if (!pPerson){
        printf("Could not allocate required memory!\n");
        return;
    }
    printf("Address: %p", pPerson);
    printf("\n-Add name: "); scanf("%19[^\n]c", (char *)pPerson); getchar();
    printf("-Add age: "); scanf("%d", &*(int *)(pPerson+sizeof(char)*20));
    printf("-Add tel: "); scanf("%ld", &*(long int *)(pPerson+sizeof(char)*20+sizeof(int)));

    //nextAdress = NULL;
    *(void **)(pPerson+NEXT) = NULL;
    //previousAddress = NULL;
    *(void **)(pPerson+PREV) = NULL;

    printf("Name: %s, age: %d, tel: %ld, previous: %p, next: %p\n", (char *)pPerson, *(int *)(pPerson+sizeof(char)*20), *(long int *)(pPerson+sizeof(char)*20+sizeof(int)),*(void **)(pPerson+PREV), *(void **)(pPerson+NEXT));


    if(*(int *)pSentinel == 0){
        //pSentinel receive first address
        *(void **)(pSentinel+LAST) = pPerson;
        *(void **)(pSentinel+FIRST) = pPerson;
        printf("\nFirst address: %p\n", *(void **)(pSentinel+FIRST));

        //size++
        *(int *)pSentinel += 1;
        return;
    }

    aux = *(void **)(pSentinel+FIRST);
    
    do{
        if(strcmp((char *)pPerson, (char *)aux) < 0){
            
            //ed = de
            *(void **)(pPerson+PREV) = *(void **)(aux+PREV);
            //ed = ot
            *(void **)(pPerson+NEXT) = aux;

            if(*(int *)pSentinel > 1 && *(void **)(aux+PREV) != NULL){
                aux2 = *(void **)(aux+PREV);
                printf("DENISE: %s\n", aux2);
                //de = ed
                *(void **)(aux2+NEXT) = pPerson;
            }
            //ot = ed
            *(void **)(aux+PREV) = pPerson;
            
            

            if(*(void **)(pPerson+PREV) == NULL){
                //pSentinel receive first address
                *(void **)(pSentinel+FIRST) = pPerson;
                printf("\nFirst address: %p\n", *(void **)(pSentinel+FIRST));
            }
            if(*(void **)(aux+NEXT) == NULL && *(int *)pSentinel == 1){
                //pSentinel receive last address
                *(void **)(pSentinel+LAST) = aux;
                printf("\nLast address: %p\n", *(void **)(pSentinel+LAST));
            }

            //size++
            *(int *)pSentinel += 1;
            //free(aux);
            printf("\nFirst address: %s\n", *(void **)(pSentinel+FIRST));
            printf("\nLast address: %s\n", *(void **)(pSentinel+LAST));
            return;
        }
        
        if(*(void **)(aux+NEXT) == NULL){
            aux2 = aux;
        }
        //receive next address
        aux = *(void **)(aux+NEXT);
    }while(aux != NULL);

    printf("OTAVIO: %s\n", aux2);

    //wi = ot
    *(void **)(pPerson+PREV) = aux2;
    //ot = wi
    *(void **)(aux2+NEXT) = pPerson;

    *(void **)(pSentinel+LAST) = pPerson;

    printf("\nFirst address: %s\n", *(void **)(pSentinel+FIRST));
    printf("\nLast address: %s\n", *(void **)(pSentinel+LAST));


    //size++
    *(int *)pSentinel += 1;
    //free(aux);
    return;
}


void showall(void *pBuffer, void *pSentinel, void *aux){
    
    aux = *(void **)(pSentinel+FIRST);
    do{
        printf("\n--Current address: %p\n", aux);
        printf("\tPerson: %s\n", aux);
        printf("--Previous address: %p\n", *(void **)(aux+PREV));
        printf("--Next address: %p\n", *(void **)(aux+NEXT));

        //receive next address
        aux = *(void **)(aux+NEXT);
    }while(aux != NULL);
}


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
