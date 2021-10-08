#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int *array, int size);
void selectionSort(int *array, int size);
void quickSort(int *array, int first, int last);
void mergeSort(int *array, int begin, int end);
void verify(int *array, int size);
void printArray(int *array, int size);
void swap(int *a, int *b);
double timePassed(struct timeval begin, struct timeval end);


int main(){
	int *arrayInsertion, *arraySelection, *arrayQuick, *arrayMerge, size;
    struct timeval begin, end;

	printf("\n> Enter the array size: "); scanf("%d", &size);
	arrayInsertion = (int *)calloc(size, sizeof(int));
    arraySelection = (int *)calloc(size, sizeof(int));
    arrayQuick = (int *)calloc(size, sizeof(int));
    arrayMerge = (int *)calloc(size, sizeof(int));

	srand(time(NULL));
	for (int i = 0; i < size; i++){
		arrayInsertion[i] = rand() % 100;
        arraySelection[i] = arrayInsertion[i];
        arrayQuick[i] = arrayInsertion[i];
        arrayMerge[i] = arrayInsertion[i];
	}

	printf("\n> Initial array: ");
    printArray(arrayInsertion, size);
    verify(arrayInsertion, size);

    printf("\n\n\n-> Insertion Sort: ");
    gettimeofday(&begin, 0);
	insertionSort(arrayInsertion, size);
    gettimeofday(&end, 0);
    printArray(arrayInsertion, size);
    verify(arrayInsertion, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end));
    free(arrayInsertion);

    printf("\n\n-> Selection Sort: ");
    gettimeofday(&begin, 0);
	selectionSort(arraySelection, size);
    gettimeofday(&end, 0);
    printArray(arraySelection, size);
    verify(arraySelection, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end));
    free(arraySelection);

    printf("\n\n-> Quick Sort: ");
    gettimeofday(&begin, 0);
	quickSort(arrayQuick, 0, size-1);
    gettimeofday(&end, 0);
    printArray(arrayQuick, size);
    verify(arrayQuick, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end));
    free(arrayQuick);

    printf("\n\n-> Merge Sort: ");
    gettimeofday(&begin, 0);
	mergeSort(arrayMerge, 0, size-1);
    gettimeofday(&end, 0);
    printArray(arrayMerge, size);
    verify(arrayMerge, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end));
    free(arrayMerge);

    printf("\n\n");
	return 0;
}


void verify(int *array, int size){
	if(size > 1){
        for(int i = 1; i < size; i++){
            if(array[i-1] > array[i]){
                printf("\n- It's not in order.");
                return;
            }
        }
    }
    printf("\n- Is in order.");
}


void printArray(int *array, int size){
    for(int i= 0; i < size; i++){
        printf("%d ", array[i]);
    }      
}


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


double timePassed(struct timeval begin, struct timeval end){
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	return seconds + microseconds * 1e-6;
}


void insertionSort(int *array, int size){
	int aux, j;

	for(int i = 1; i < size; i++){
		aux = array[i];
        j = i - 1;
        while(aux < array[j] && j >= 0){
            array[j+1] = array[j];
            --j;
        }
        array[j+1] = aux;
	}
}


void selectionSort(int *array, int size){
	int minIndex, j;

    for(int i = 0; i < size-1; i++){
        minIndex = i;
        for(j = i+1; j < size; j++){
            if(array[j] < array[minIndex]){
                minIndex = j;
            }
        }
        swap(&array[minIndex], &array[i]);
    }
}


void quickSort(int *array, int first, int last){
    int aux;

    if(first < last){
        int pivot = first;
        int i = first;
        int j = last;

        while(i < j){
            while(array[i] <= array[pivot] && i < last){
                i++;
            }
            while(array[j] > array[pivot]){
                j--;
            }
            if(i < j){
                aux = array[i];
                array[i] = array[j];
                array[j] = aux;
            }
        }

        aux = array[pivot];
        array[pivot] = array[j];
        array[j] = aux;
        quickSort(array, first, j-1);
        quickSort(array, j+1, last);
    }
}


void mergeSort(int *array, int begin, int end){
    if(begin < end){
        int middle = begin + (end - begin) / 2; //m is the point where the array is divided into two subarrays

        mergeSort(array, begin, middle);
        mergeSort(array, middle + 1, end);
        
        merge(array, begin, middle, end); //merge the sorted subarrays
    }
}


void merge(int *array, int begin, int middle, int end){
    int i, j, k;

    //Create firstHalf ← A[begin..middle] and secondHalf ← A[middle+1..end]
    int amount1 = middle - begin + 1;
    int amount2 = end - middle;

    int firstHalf[amount1], secondHalf[amount2];

    for (int i = 0; i < amount1; i++)
        firstHalf[i] = array[begin+i];
    for (int j = 0; j < amount2; j++)
        secondHalf[j] = array[middle+1+j];

    // Maintain current index of sub-arrays and main array
    i = 0;
    j = 0;
    k = begin;

    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while(i < amount1 && j < amount2){
        if(firstHalf[i] <= secondHalf[j]){
            array[k] = firstHalf[i];
            i++;
        }else{
            array[k] = secondHalf[j];
            j++;
        }
        k++;
    }

    // When we run out of elements in either L or M,
    // pick up the remaining elements and put in A[p..r]
    while(i < amount1){
        array[k] = firstHalf[i];
        i++; k++;
    }
    while(j < amount2){
        array[k] = secondHalf[j];
        j++; k++;
    }
}
