#include "sort.h"
#include "functions.h"

uint64_t comparisons;


uint64_t BubbleSort(uint32_t * sortarray, uint32_t arraysize){
    comparisons = 0;

    for(uint32_t n = arraysize; n > 1; n--){
        for(uint32_t i = 0; i < n - 1; i++){
            if(sortarray[i] > sortarray[i+1]){
                swapValue(&sortarray[i], &sortarray[i+1]);
            }
            comparisons++;
        }
    }
    return comparisons;
}


uint64_t SelectionSort(uint32_t * sortarray, uint32_t arraysize){
    comparisons = 0;
    uint32_t * plowest;                                 //pointer to the lowest element

    for(uint32_t i = 0; i < (arraysize - 1); i++) {
        plowest = &sortarray[i];                        //lowest element always the starting element at first
        for (uint32_t n = i; n < arraysize; n++) {
            if(n < (arraysize - 1)){
                if(sortarray[n+1] < *plowest){          //the (to this time) lowest element gets compared to the next, until the last element
                    plowest = &sortarray[n+1];          //if the next element is lower the ADDRESS is written to plowest
                }
                comparisons++;
            }
            else{
                swapValue(&sortarray[i], plowest);           //at the end of one circle the starting element gets swapped with the lowest.
            }
        }
    }
    return comparisons;
}


uint64_t InsertionSort(uint32_t * sortarray, uint32_t arraysize){
    comparisons = 0;
    uint32_t i, value;          //value => value that gets written to the element before the current one
    int32_t j;

    for (i = 1; i < arraysize; i++)
    {
        value = sortarray[i];
        j = i-1;

        //insertion of the current element into the set in front
        while ((j >= 0) && (sortarray[j] > value)){
            comparisons++;
            sortarray[j+1] = sortarray[j];
            j = j-1;
        }
        comparisons++;
        sortarray[j+1] = value;
    }
    return comparisons;
}


uint64_t MergeSort(uint32_t * sortarray, uint32_t arraysize){
    comparisons = 0;
    uint32_t mid, indR, indL, indM, *left, *right, leftcount, rightcount; //indexRight, indexLeft, indexMerged
    if(arraysize < 2){
        return comparisons;
    }
    mid = arraysize / 2;

    left = (uint32_t*) malloc (mid * sizeof(uint32_t));
    right = (uint32_t*) malloc ((arraysize - mid) * sizeof(uint32_t));

    for(indL = 0; indL < mid; indL++){
        left[indL] = sortarray[indL];
    }
    for(indL = mid; indL < arraysize; indL++){
        right[indL - mid] = sortarray[indL];
    }

    comparisons += MergeSort(left, mid);
    comparisons += MergeSort(right, arraysize - mid);

    indR = indL = indM = 0;
    leftcount = mid;
    rightcount = arraysize - mid;
    while(indL < leftcount && indR < rightcount){
        if(left[indL] < right[indR]){
            sortarray[indM++] = left[indL++];
        }
        else{
            sortarray[indM++] = right[indR++];
        }
        comparisons++;
    }
    while(indL < leftcount){
        sortarray[indM++] = left[indL++];
    }
    while (indR < rightcount){
        sortarray[indM++] = right[indR++];
    }
    free(left);
    free(right);
    return comparisons;
}


uint64_t CocktailSort(uint32_t * sortarray, uint32_t arraysize){
    comparisons = 0;
    uint32_t left = 0, right = arraysize - 1, mov;
    uint32_t j, temp;

    do{
        for(j = right; j >= left + 1; j--){
            if(sortarray[j-1] > sortarray[j]){
                    temp = sortarray[j-1];
                    sortarray[j-1] = sortarray[j];
                    sortarray[j] = temp;
                    mov = j;
            }
            comparisons++;
        }

        left = mov;

        for(j = left; j <= right - 1; j++)
        {
            if(sortarray[j] > sortarray[j+1])
            {
                temp = sortarray[j+1];
                sortarray[j+1] = sortarray[j];
                sortarray[j] = temp;
                mov = j;
            }
            comparisons++;
        }

        right = mov;

    } while(left < right);

    return comparisons;
}


uint64_t RadixSort(uint32_t * sortarray, uint32_t arraysize){
    int32_t i;
    uint32_t helparray[arraysize];
    int32_t digit = 1;
    uint32_t largestnumber = 0;

    for(i = 0; i < arraysize; i++){
        if(sortarray[i] > largestnumber){
            largestnumber = sortarray[i];
        }
    }

    while((largestnumber / digit) > 0){
        uint32_t bucket[10] = {0};
        for(i = 0; i < arraysize; i++) {
            bucket[(sortarray[i] / digit) % 10]++;
        }
        for(i = 1; i < 10; i++){
            bucket[i] += bucket[i - 1];
        }
        for(i = arraysize - 1; i >= 0; i--){
            helparray[--bucket[(sortarray[i] / digit) % 10]] = sortarray[i];
        }
        for(i = 0; i < arraysize; i++){
            sortarray[i] = helparray[i];
        }
        digit *= 10;
    }

return 0;
}
