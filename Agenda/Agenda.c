#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void *pBuffer);
void add(void *pSentinel, void *aux);
void showall(void *pSentinel, void *aux);

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
    pBuffer = (void *)calloc(1, sizeof(int));

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
                add(pSentinel, aux);
                break;
            case 2:
                // pBuffer = remov(pBuffer);
                // *(int *)pBuffer = size;
                break;
            case 3:
                //search(pBuffer);
                break;
            case 4:
                showall(pSentinel, aux);
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



void add(void *pSentinel, void *aux){
    void *aux2;

    void *pPerson = (void *)malloc(PERSON_SIZE);
    if (!pPerson){
        printf("Could not allocate required memory!\n");
        return;
    }
    printf("\nAddress: %p", pPerson);
    printf("\n-Add name: "); scanf("%19[^\n]c", (char *)pPerson); getchar();
    printf("-Add age: "); scanf("%d", &*(int *)(pPerson+sizeof(char)*20));
    printf("-Add tel: "); scanf("%ld", &*(long int *)(pPerson+sizeof(char)*20+sizeof(int)));

    //nextAdress = NULL;
    *(void **)(pPerson+NEXT) = NULL;
    //previousAddress = NULL;
    *(void **)(pPerson+PREV) = NULL;


    if(*(int *)pSentinel == 0){
        //pSentinel receive first address and last address
        *(void **)(pSentinel+LAST) = pPerson;
        *(void **)(pSentinel+FIRST) = pPerson;
        //size++
        *(int *)pSentinel += 1;
        return;
    }

    //aux receives first address
    aux = *(void **)(pSentinel+FIRST);
    
    do{
        if(strcmp((char *)pPerson, (char *)aux) < 0){
            
            //current person(prev) = previous person
            *(void **)(pPerson+PREV) = *(void **)(aux+PREV);
            //current person(next) = next person
            *(void **)(pPerson+NEXT) = aux;

            if(*(int *)pSentinel > 1 && *(void **)(aux+PREV) != NULL){
                aux2 = *(void **)(aux+PREV);
                //previous person(next) = current person
                *(void **)(aux2+NEXT) = pPerson;
            }
            //next person(prev) = current person
            *(void **)(aux+PREV) = pPerson;  


            if(*(void **)(pPerson+PREV) == NULL){
                //pSentinel receive first address
                *(void **)(pSentinel+FIRST) = pPerson;
            }
            if(*(void **)(aux+NEXT) == NULL && *(int *)pSentinel == 1){
                //pSentinel receive last address
                *(void **)(pSentinel+LAST) = aux;
            }

            //size++
            *(int *)pSentinel += 1;
            return;
        }

        if(*(void **)(aux+NEXT) == NULL){
            aux2 = aux;
        }
        //receive next address
        aux = *(void **)(aux+NEXT);
    }while(aux != NULL);

    //last person on the list
    *(void **)(pPerson+PREV) = aux2;
    *(void **)(aux2+NEXT) = pPerson;
    *(void **)(pSentinel+LAST) = pPerson;

    //size++
    *(int *)pSentinel += 1;
    return;
}


void showall(void *pSentinel, void *aux){
    aux = *(void **)(pSentinel+FIRST);
    do{
        printf("\n--Current address: %p\n", aux);
        printf("> Person: %s, Age: %d, Cellphone: %ld, Previous Address: %p, Next Address: %p\n\n", (char *)aux, *(int *)(aux+sizeof(char)*20), *(long int *)(aux+sizeof(char)*20+sizeof(int)), *(void **)(aux+PREV), *(void **)(aux+NEXT));

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
