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
	int *arrayInsertion, *arraySelection, *arrayQuick, *arrayMerge, size; //its needed to create multiple arrays, otherwise, it would be overwritten
    struct timeval begin, end; //used for measure time

	printf("\n> Enter the array size: "); scanf("%d", &size);
	arrayInsertion = (int *)calloc(size, sizeof(int)); //calloc for every array
    arraySelection = (int *)calloc(size, sizeof(int));
    arrayQuick = (int *)calloc(size, sizeof(int));
    arrayMerge = (int *)calloc(size, sizeof(int));

	srand(time(NULL));
	for (int i = 0; i < size; i++){ //generate random numbers
		arrayInsertion[i] = rand() % 100;
        arraySelection[i] = arrayInsertion[i];
        arrayQuick[i] = arrayInsertion[i];
        arrayMerge[i] = arrayInsertion[i];
	}

	printf("\n> Initial array: "); 
    printArray(arrayInsertion, size); //print the random array generated
    verify(arrayInsertion, size); //verify the random array

    printf("\n\n\n-> Insertion Sort: ");
    gettimeofday(&begin, 0); //get the time of the beginning of the insertion sort
	insertionSort(arrayInsertion, size); //sort
    gettimeofday(&end, 0); //get the time of the end of the insertion sort
    printArray(arrayInsertion, size);
    verify(arrayInsertion, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end)); //print the time passed
    free(arrayInsertion); //free the insertion array

    printf("\n\n-> Selection Sort: "); //same thing as above but with selection sort
    gettimeofday(&begin, 0);
	selectionSort(arraySelection, size);
    gettimeofday(&end, 0);
    printArray(arraySelection, size);
    verify(arraySelection, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end));
    free(arraySelection);

    printf("\n\n-> Quick Sort: "); //same thing as above but with quick sort
    gettimeofday(&begin, 0);
	quickSort(arrayQuick, 0, size-1);
    gettimeofday(&end, 0);
    printArray(arrayQuick, size);
    verify(arrayQuick, size);
    printf("\n- Time passed: %.6f", timePassed(begin, end));
    free(arrayQuick);

    printf("\n\n-> Merge Sort: "); //same thing as above but with merge sort
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


void verify(int *array, int size){ //pass through the array checking if it is sorted
	if(size > 1){
        for(int i = 1; i < size; i++){
            if(array[i-1] > array[i]){ //compares the current element with the previous element
                printf("\n- It's not in order.");
                return;
            }
        }
    }
    printf("\n- Is in order.");
}


void printArray(int *array, int size){
    for(int i= 0; i < size; i++){
        printf("%d ", array[i]); //print every number on the array
    }      
}


void swap(int *a, int *b){ //swap the "a" with the "b", used on the selection sort and quick sort
    int temp = *a;
    *a = *b;
    *b = temp;
}


double timePassed(struct timeval begin, struct timeval end){ //gets the time passed
	long seconds = end.tv_sec - begin.tv_sec;
	long microseconds = end.tv_usec - begin.tv_usec;
	return seconds + microseconds * 1e-6;
}


void insertionSort(int *array, int size){ //worst case: O(n^2)-inverted      best case: O(n)-sorted
	int aux, j;

	for(int i = 1; i < size; i++){ //suppose the array is 2 3 1 on the first iteration
		aux = array[i]; //get the number 3 on the first iteration, then the number 1 on the second iteration
        j = i - 1; //get the number 2 on the first iteration, and number 3 on second iteration
        
        while((j >= 0) && (aux < array[j])){ //first iteration 3 < 2 == false, second iteration 1 < 3 == true, third iteration 1 < 2 == true
            array[j+1] = array[j]; //3 gets passed forward, so now it's 2 3 3, on the second iteration the 2 gets passed forward, so now it's 2 2 3
            j--; //now points to the previous element, the number 2, and on the second iteration it will point to no one
        }
        array[j+1] = aux; //now the array will receive the number that was on the aux, so the array will be 1 2 3
	}
}


void selectionSort(int *array, int size){ //worst case: O(n^2)      best case: O(n^2)
    //always need to go to the end of the vector to make sure the element being analyzed is the smallest
	int minIndex, j;

    for(int i = 0; i < size-1; i++){ //suppose the array is 2 3 1
        minIndex = i; //minIndex = 2, minIndex = 3
        for(j = i+1; j < size; j++){ //j = 3, j = 1 / j = 2
            if(array[j] < array[minIndex]){ //3 < 2 == false, 1 < 2 == true / 2 < 3 == true
                minIndex = j; //update the index of the smallest element
            }
        }
        swap(&array[minIndex], &array[i]); //1 <--> 2, now it's 1 3 2 / 2 <--> 3, now it's 1 2 3
    }
}


void quickSort(int *array, int first, int last){ 
    //worst case: O(n^2) - the pivot is always smaller or bigger than everyone else
    //best case: O(n log(n)) - the pivot is always a central number

    if(first < last){ //suppose the array is 2 4 1 3, 0 < 3 == true / 2 < 3 == true
        int pivot = first; //the pivot is going to be the first element, in that case, the number 2 / pivot = 4
        int i = first; 
        int j = last;

        while(i < j){ //0 < 3 == true / 1 < 2 == true / 2 < 3 == true
            while(array[i] <= array[pivot] && i < last){ //2 <= 2 == true, 4 <= 2 == false / 1 <= 2 == true, 4 <= 2 == false / 4 <= 4 && 2 < 3, 3 < 3
                i++;
            }
            while(array[j] > array[pivot]){ //3 > 2 == true, 1 > 2 == false / 4 > 2 == true, 1 > 2 == false / 3 > 4 == false
                j--;
            }
            if(i < j){ //1 < 2 == true / 2 < 1 == false / 3 < 3 == false
                swap(&array[i], &array[j]); //4 <--> 1, now the array is 2 1 4 3
            }
        }
        swap(&array[pivot], &array[j]); //2 <--> 1, now the array is 1 2 4 3 / 4 <--> 3, now the array is 1 2 3 4
        quickSort(array, first, j-1); //quicksort 0 ... 0 == 1 / 2 ... 2 == 3
        quickSort(array, j+1, last); //quicksort 2 .. 3 == 4 3 / 4 ... 4 == 4
    }
}


void mergeSort(int *array, int begin, int end){ //worst case: O(n log(n))       best case: O(n log(n))
    //suppose we have the array 4 2 1 3
    if(begin < end){ //0 < 3 == true / 0 < 1 == true / 2 < 3 == true
        int middle = begin + (end - begin) / 2; //middle is the point where the array is divided into two subarrays
        //in this case is 0+(3-0)/2 = 1.5 == 1 / when 0 .. 1 then is 0+(1-0)/2 = 0.5 == 0 / when 2 .. 3 then is 2+(3-2)/2 = 2.5 == 2

        mergeSort(array, begin, middle); //divide the rest of the left part, in this case is 0 .. 1 == 4 2
        mergeSort(array, middle + 1, end); //divide the rest of the right part, in this case 2 .. 3 == 1 3
        
        merge(array, begin, middle, end); //merge the sorted subarrays, 2 4 and 1 3 and than become 1 2 3 4
    }
}


void merge(int *array, int begin, int middle, int end){ 
    //first time passing is 4 and 2, so its begin = 0 and middle = 0 and end = 1
    //for the third time passing is 2 4 and 1 3, the begin is 0 and middle is 1 and end is 3
    int i, j, k;
    
    int amount1 = middle - begin + 1; //0-0+1=1 / 1-0+1 = 2
    int amount2 = end - middle; //1-0=1 / 3-1 = 2
    int firstHalf[amount1], secondHalf[amount2]; //Create firstHalf <- A[begin..middle] and secondHalf <- A[middle+1..end]

    for(int i = 0; i < amount1; i++)
        firstHalf[i] = array[begin+i]; //firsthalf = array[0+0](4) / firsthalf[0] = array[0+0](2), firsthalf[1] = array[0+1](4)
    for(int j = 0; j < amount2; j++)
        secondHalf[j] = array[middle+1+j]; //secondhalf = array[0+1+0](2) / secondhalf[0] = array[1+1+0](1), secondHalf[1] = array[1+1+1](3)

    //maintain current index of sub-arrays and main array
    i = 0;
    j = 0;
    k = begin;

    while(i < amount1 && j < amount2){ //(0<1&&0<1)==true, (0<1&&1<1)==false / (0<2&&0<2)==true, (0<2&&1<2)==true, (1<2&&1<2)==true, (1<2&&2<2)==false
        if(firstHalf[i] <= secondHalf[j]){ //4 <= 2 == false / 2 <= 1 == false, 2 <= 3 == true, 4 <= 3 == false
            array[k] = firstHalf[i]; //array[1] = 2
            i++;
        }else{
            array[k] = secondHalf[j]; //array[0] = 2 / array[0] = 1, array[2] = 3
            j++;
        }
        k++; //now k is 1
    }

    while(i < amount1){ //0 < 1 == true / 1 < 2 == true
        array[k] = firstHalf[i]; //array[1] = 4 / array[4] = 4
        i++; k++;
    }
    while(j < amount2){ //1 < 1 == false / 2 < 2 == false
        array[k] = secondHalf[j];
        j++; k++;
    }
}
