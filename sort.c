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


uint64_t ShellSort(uint32_t* sortarray, uint32_t arraysize){
	uint64_t anzahlVergleiche=0;
	uint32_t j, temp, n;
	//Spannweite
	n = 6;
	//Schleife zum verringern der Spannweiter
	while(n > 0){
		//Schleife zum Weiterschieben der beiden Vergleichsobjekte
		for (uint32_t i = n; i < arraysize; i++){
			temp = sortarray[i];
			//Wenn eine Zahl getauscht werden muss (vorheriges groesser als hinteres), dann
			//wird die kleinere Zahl rückwirkend mit der Spannweite n zur passenden Stelle verschoben
			for(j = i; j >= n && sortarray[j-n] > temp; j -= n){
				anzahlVergleiche++;
				//an der hinteren Stelle wird die vordere Zahl gespeichert
				sortarray[j] = sortarray[j-n];
			}
		//Wenn passende Stelle für temp (kleinere Zahl) gefunden -> speichern
		sortarray[j] = temp;
		}
		//Spannweite verkleinern
		n--;
	}
	return anzahlVergleiche;
}


uint64_t QuickSort(uint32_t* first, uint32_t* last){
	uint64_t anzahlVergleiche=0;
	uint32_t* firstTemp = first;
	uint32_t* lastTemp = last;
	uint32_t temp;
	//Pivotelement: In der Mitte
	uint32_t pivot = *(first + (last - first >> 1));
	do{
		//suchen nach groessere Zahlen als das Pivotelement auf der linken Seite
		while(*firstTemp < pivot){
			firstTemp++;
		}
		//suchen nach kleineren Zahlen als das Pivotelement auf der rechten Seite
		while(*lastTemp > pivot){
			lastTemp--;
		}
		anzahlVergleiche++;
		//Wenn sich die zeiger noch nicht gekreuzt haben -> tauschen und weiterschalten
		if(firstTemp <= lastTemp){
			temp = *firstTemp;
			*firstTemp = *lastTemp;
			*lastTemp = temp;
			firstTemp++;
			lastTemp --;
		}
		//Abbruch wenn Zeiger sich "kreuzen"
	}while(firstTemp <= lastTemp);
	//wenn es kleinere Zahlen als das Pivotelement gibt: Teilen und Quicksort neu aufrufen
	if(first < lastTemp){
		anzahlVergleiche += QuickSort(first, lastTemp);
	}
	anzahlVergleiche++;
	//wenn es groessere Zahlen als das Pivotelement gibt: Teilen und Quicksort neu aufrufen
	if(last > firstTemp){
		anzahlVergleiche += QuickSort(firstTemp, last);
	}
	return anzahlVergleiche;
}

uint64_t HeapSort(uint32_t* sortarray, uint32_t arraysize){
	uint64_t anzahlVergleiche=0;
	//Heapsort: Aufteilen in Binärbaum: Zu einem Kind am Index i ist (i+1)/2-1 der Vater
	//Ziel: Groesstes Element in die Spitze verschieben
	uint32_t temp;
	//Schleife von unten nach oben tauschen (Vater muss groesser sein als Kind)
	for(uint32_t i = arraysize; i > 1; i--){
		anzahlVergleiche ++;
		//Tausch wenn Vater nicht groesser ist
		if(*(sortarray+i/2-1) < *(sortarray+i-1)){
			temp = *(sortarray + i-1);
			*(sortarray + i-1) = *(sortarray + i/2-1);
			*(sortarray + i/2-1) = temp;
		}
	}
	//Schleife bis Baum komplett sortiert
	for(uint32_t j = arraysize; j > 1; j--){
		//Schleife von oben nach unten tauschen
		for(uint32_t i = 2; i <= j; i++){
			anzahlVergleiche ++;
			//Tausch wenn Vater nicht groesser ist
			if(*(sortarray+i/2-1) < *(sortarray+i-1)){
				temp = *(sortarray + i-1);
				*(sortarray + i-1) = *(sortarray + i/2-1);
				*(sortarray + i/2-1) = temp;
			}
		}
		//Tausch: Groesstes Element (in der Spitze) mit letztem Element des Baumes tauschen
		temp = *(sortarray+j-1);
		*(sortarray + j-1) = *sortarray;
		*sortarray = temp;
	}
	return anzahlVergleiche;
}
