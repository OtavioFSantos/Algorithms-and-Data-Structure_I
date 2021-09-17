#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(void *pBuffer);
void add(void *pSentinel, void *pBuffer);
void remov(void *pSentinel, void *pBuffer);
void search(void *pSentinel, void *pBuffer);
void showAll(void *pSentinel, void *pBuffer);

//defines to make the code more readable
#define PERSON_SIZE (sizeof(char)*20+sizeof(int)+sizeof(long int)+sizeof(void **)*2) //personsize = name[20] + age + tel + previousAddress + nextAddress
#define NEXT (sizeof(char)*20+sizeof(int)+sizeof(long int)+sizeof(void **))
#define PREV (sizeof(char)*20+sizeof(int)+sizeof(long int))
#define FIRST (sizeof(int)+sizeof(void **))
#define LAST (sizeof(int))
#define NAME (sizeof(void **)+sizeof(int))


int main(){
    void *pBuffer, *pSentinel;
    pSentinel = (void *)calloc(1, (sizeof(int) + sizeof(void **)*2)); //pSentinel = size + last address + first address
    pBuffer = (void *)calloc(1, sizeof(void **) + sizeof(int)); //pBuffer = pointer to pointer + choice

    if(!pSentinel || !pBuffer){
        printf("Could not allocate required memory!\n");
        return -1;
    }

    *(int *)pSentinel = 0; //size = 0
    *(void **)(pSentinel+sizeof(int)) = NULL; //last address = NULL
    *(void **)(pSentinel+FIRST) = NULL; //first address = NULL
    *(void **)pBuffer = NULL; //pointer to pointer = NULL

    for(;;){
        menu(pBuffer);
        switch(*(int *)(pBuffer+sizeof(void **))){
            case 1:
                add(pSentinel, pBuffer);
                break;
            case 2:
                remov(pSentinel, pBuffer);
                break;
            case 3:
                search(pSentinel, pBuffer);
                break;
            case 4:
                showAll(pSentinel, pBuffer);
                break;
            case 5:
                if(*(int *)pSentinel != 0){
                    void *pAux = *(void **)(pSentinel+LAST); //aux = last person
                    do{
                        if(*(int *)pSentinel == 1){
                            free(pAux); //free first person
                            *(int *)pSentinel -= 1; //size--
                        }else{
                            pAux = *(void **)(pAux+PREV); //aux = previous person
                            void *pAux2 = *(void **)(pAux+NEXT); //aux2 = next person
                            free(pAux2); //free next person so the list can keep going
                            
                            *(int *)pSentinel -= 1; //size--
                        }
                    }while(*(int *)pSentinel != 0);
                }
                free(pBuffer);
                free(pSentinel);
                exit(0);
                break;
		}
    }
    return 0;
}


void add(void *pSentinel, void *pBuffer){
    void *aux;
    void *pPerson = (void *)malloc(PERSON_SIZE);

    if (!pPerson){
        printf("Could not allocate required memory!\n");
        return;
    }

    //read person data
    printf("\nAddress: %p", pPerson);
    printf("\n-Add name: "); scanf("%19[^\n]c", (char *)pPerson); getchar();
    printf("-Add age: "); scanf("%d", &*(int *)(pPerson+sizeof(char)*20));
    printf("-Add tel: "); scanf("%ld", &*(long int *)(pPerson+sizeof(char)*20+sizeof(int)));

    *(void **)(pPerson+NEXT) = NULL; //person nextAdress = NULL;
    *(void **)(pPerson+PREV) = NULL; //person previousAddress = NULL;

    if(*(int *)pSentinel == 0){
        //if this is the first person being added then pSentinel receive first address and last address
        *(void **)(pSentinel+LAST) = pPerson;
        *(void **)(pSentinel+FIRST) = pPerson;
        
        *(int *)pSentinel += 1; //size++
        return;
    }

    pBuffer = *(void **)(pSentinel+FIRST); //pBuffer receives first address
    do{
        if(strcmp((char *)pPerson, (char *)pBuffer) < 0){
            
            *(void **)(pPerson+PREV) = *(void **)(pBuffer+PREV); //current person(prev) = previous person
            *(void **)(pPerson+NEXT) = pBuffer; //current person(next) = next person

            //in the case of the person being added to the beginning
            if(*(int *)pSentinel > 1 && *(void **)(pBuffer+PREV) != NULL){
                aux = *(void **)(pBuffer+PREV);
                *(void **)(aux+NEXT) = pPerson; //previous person(next) = current person
            }
            *(void **)(pBuffer+PREV) = pPerson; //next person(prev) = current person

            //updates the new first address if needed
            if(*(void **)(pPerson+PREV) == NULL){
                *(void **)(pSentinel+FIRST) = pPerson; //pSentinel receive first address
            }

            *(int *)pSentinel += 1; //size++
            return;
        }

        //needs this otherwise there will be segmentation fault later on
        if(*(void **)(pBuffer+NEXT) == NULL){
            break;
        }
        pBuffer = *(void **)(pBuffer+NEXT); //receives next address
    }while(pBuffer != NULL);

    //in the case of the person is being added to the end
    *(void **)(pPerson+PREV) = pBuffer;
    *(void **)(pBuffer+NEXT) = pPerson;
    *(void **)(pSentinel+LAST) = pPerson;

    *(int *)pSentinel += 1; //size++
    return;
}


void remov(void *pSentinel, void *pBuffer){
    void *aux;
    void *auxName = calloc(1, sizeof(char)*20); //aux to read the name to remove

    //if there is no one yet
    if(*(int *)pSentinel == 0){
        printf("\nNo data yet!\n");
        return;
    }

    printf("\nName to remove: "); scanf("%19[^\n]c", (char *)auxName); getchar(); //name to remove

    pBuffer = *(void **)(pSentinel+FIRST); 
    do{
        //if finds the right person to remove
        if(strcmp((char *)pBuffer, (char *)auxName) == 0){

            if(*(void **)(pBuffer+PREV) != NULL){
                aux = *(void **)(pBuffer+PREV); //aux = previous person
                *(void **)(aux+NEXT) = *(void **)(pBuffer+NEXT); //previous person(next) = next person
            }else{
                *(void **)(pSentinel+FIRST) = *(void **)(pBuffer+NEXT); //updates first address if the first person is being removed
            }
            
            if(*(void **)(pBuffer+NEXT) != NULL){
                aux = *(void **)(pBuffer+NEXT); //aux = next person
                *(void **)(aux+PREV) = *(void **)(pBuffer+PREV); //next person(prev) = previous person
            }else{
                *(void **)(pSentinel+LAST) = *(void **)(pBuffer+PREV); //updates last address if the last person is being removed
            }
   
            *(int *)pSentinel -= 1; //size--
            free(pBuffer);
            free(auxName);
            return;
        } 
        
        pBuffer = *(void **)(pBuffer+NEXT); //receive next address
    }while(pBuffer != NULL);

    printf("\nName not found!\n");
    free(auxName);
}


void search(void *pSentinel, void *pBuffer){
    void *auxName = calloc(1, sizeof(char)*20); //aux to read the name of the person being searched for

    if(*(int *)pSentinel == 0){
        printf("\nNo data yet!\n");
        return;
    }

    printf("\nName to search: "); scanf("%19[^\n]c", (char *)auxName); getchar(); //read the name to search

    pBuffer = *(void **)(pSentinel+FIRST); 
    do{
        if(strcmp((char *)pBuffer, (char *)auxName) == 0){
            //if it finds the right person, prints it
            printf("\n> Person address: %p\n", pBuffer);
            printf("--Person: %s, Age: %d, Cellphone: %ld, Previous Address: %p, Next Address: %p\n", (char *)pBuffer, *(int *)(pBuffer+sizeof(char)*20), *(long int *)(pBuffer+sizeof(char)*20+sizeof(int)), *(void **)(pBuffer+PREV), *(void **)(pBuffer+NEXT));
            free(auxName);
            return;
        } 
        pBuffer = *(void **)(pBuffer+NEXT); //receive next address
    }while(pBuffer != NULL);

    printf("\nName not found!\n");
    free(auxName);
}


void showAll(void *pSentinel, void *pBuffer){
    //cant show everyone if there is no one :)
    if(*(int *)pSentinel == 0){
        printf("\nNo data yet!\n");
        return;
    }

    //print size and everyone else
    printf("\nSize: %d\n", *(int *)pSentinel);
    pBuffer = *(void **)(pSentinel+FIRST);
    do{
        printf("\n> Person address: %p\n", pBuffer);
        printf("--Person: %s, Age: %d, Cellphone: %ld, Previous Address: %p, Next Address: %p\n", (char *)pBuffer, *(int *)(pBuffer+sizeof(char)*20), *(long int *)(pBuffer+sizeof(char)*20+sizeof(int)), *(void **)(pBuffer+PREV), *(void **)(pBuffer+NEXT));

        pBuffer = *(void **)(pBuffer+NEXT); //receive next address
    }while(pBuffer != NULL);
}


void menu(void *pBuffer){
    //surely the hardest part to understand
    do{
        printf("\n--------------------------------------\n");
		printf("1. Add;\n");
        printf("2. Remove;\n");
		printf("3. Search;\n");
        printf("4. Show all;\n");
		printf("5. Exit.\n");
		printf("\nPlease, choose what you want to do: "); scanf("%d", &*(int *)(pBuffer+sizeof(void **)));
        printf("--------------------------------------\n");
	}while(*(int *)(pBuffer+sizeof(void **)) < 1 || *(int *)(pBuffer+sizeof(void **)) > 5);
    getchar();
}
