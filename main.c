#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "sort.h"
#include "functions.h"

#define IMAIN UserinterfaceMain
#define IRANGE UserinterfaceRange
#define ISORTS UserinterfaceSorts
#define IARRAY UserinterfaceArrayOut
#define ICOMP UserinterfaceComparison
#define ILIST UserinterfaceList
#define CLEAR system("cls")

struct infos{
char name[50];
uint32_t time;
uint64_t comparisons;
};

uint32_t * sortedarray;
uint32_t * unsortedarray;
uint32_t arraysize = 0;

void swapstruct(struct infos * A, struct infos * B){            //eventuell Auslagern in functions.c
    struct infos Aold = *A;
    *A = *B;
    *B = Aold;
}

void IMAIN(){
    printf       ("\n1) Array - Groesse festlegen          2) Zahlenbereich waehlen\n"
                    "3) Zahlen von Tastatur einlesen       4) Zufallszahlen erzeugen\n"
                    "5) Array ausgeben                     6) Array sortieren mit...\n"
                    "7) Vergleich mehrerer Sorts           8) Programm beenden\n");
}

void IRANGE(){
    printf      ("\n1) Minimum festlegen         2) Maximum festlegen\n"
                   "3) Untermenue verlassen\n");
}

void ISORTS(){
    printf      ("\n1) Bubblesort          2) Insertionsort\n"
                   "3) Selectionsort       4) Mergesort\n"
                   "5) Quicksort           6) Heapsort\n"
                   "7) Shellsort           8) Cocktailsort\n"
                   "9) Radixsort           10) Untermenue verlassen\n");
}

void IARRAY(){
    printf      ("\n1) sortiertes Array          2) unsortiertes Array\n"
                   "3) Untermenue verlassen\n");
}

void ICOMP(){
    printf      ("\n1) alle aktivieren         2) alle deaktivieren\n"
                   "3) Vergleich starten       4) Sort hinzufuegen\n"
                   "5) Sort entfernen          6) Untermenue verlassen\n");
}

void ILIST(){
    printf      ("\n1) Liste nach Alphabet sortieren               2) Liste nach Zeit sortieren\n"
                   "3) Liste nach Vergleichen sortieren            4) Untermenue verlassen\n");
}



int main() {

    SYSTEMTIME before;          //Zeitmarke vor der jeweiligen Funktion
    SYSTEMTIME later;           //Zeitmarke nach der jeweiligen Funktion
    int64_t diffms;             //Differenz beider Zeitmarken umgerechnet in ms
    uint64_t comparisons = 0;   //Anzahl der Vergleiche eines Sorts (Ausgangswert jedes Sorts)
    uint16_t input = 0, inputArr = 0, inputSorts = 0, inputRan = 0, inputComp = 0, inputList = 0, inputArrSwi = 0;              //Eingabe des Nutzers für Optionenwahl
    uint32_t max = 1000;        //MAX und MIN Werte für den Zahlenbereich
    uint32_t min = 1;
    uint16_t BubSwitch = 0, InsSwitch = 0, SelSwitch = 0, MerSwitch = 0, QuiSwitch = 0, HeaSwitch = 0, SheSwitch = 0, CocSwitch = 0, RadSwitch = 0;    //Switches für Vergleich
    uint16_t SortsCount = 0;
    uint16_t stocked = 0;           //Probe ob das Array bestückt ist
    uint16_t sorted = 0;            //Probe ob das Array sortiert ist
    struct infos Sorts[9];

    strcpy(Sorts[0].name, "Bubblesort");
    strcpy(Sorts[1].name, "Insertionsort");
    strcpy(Sorts[2].name, "Selectionsort");
    strcpy(Sorts[3].name, "Mergesort");
    strcpy(Sorts[4].name, "Quicksort");
    strcpy(Sorts[5].name, "Heapsort");
    strcpy(Sorts[6].name, "Shellsort");
    strcpy(Sorts[7].name, "Cocktailsort");
    strcpy(Sorts[8].name, "Radixsort");

    while(input != 8){

        IMAIN();

        input = 0;                  //Falls ein ungültiges Zeichen eingegeben wird, soll die Variable nicht den vorherigen Wert haben und in ein Untermenue springen
        scanf("%hu", &input);
        getchar();                  //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)

        /////////////////////////////////////////Array - Groesse festlegen
        if(input == 1){
            CLEAR;
            printf("Geben sie die Anzahl der Elemente an, die sortiert werden sollen.\n");
            scanf("%u", &arraysize);
            sortedarray = (uint32_t*) malloc(arraysize * sizeof(uint32_t));
            unsortedarray = (uint32_t*) malloc(arraysize * sizeof(uint32_t));
            stocked = 0;
            sorted = 0;
            CLEAR;
            printf("--Die Anzahl der Elemente betraegt nun: %u", arraysize);
        }
        ///////////////////////////////////////////////////////////

        /////////////////////////////////////////Zahlenbereich waehlen
        else if(input == 2){
            uint32_t mintest;
            uint32_t maxtest;
            CLEAR;
            inputRan = 0;
            while(inputRan != 3){
                printf("Derzeitig min: %u   Derzeitiges max: %u", min, max);
                IRANGE();
                inputRan = 0;
                scanf("%hu", &inputRan);
                getchar();                      //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)
                if(inputRan == 1){
                    CLEAR;
                    printf("Geben sie ihr gewuenschtes Minimum ein:");
                    scanf("%u", &mintest);
                    if(mintest <= max){
                        min = mintest;
                        CLEAR;
                    }
                    else{
                        CLEAR;
                        printf("--Das Minimum muss kleiner als, oder gleich dem Maximum gewaehlt werden!\n");
                    }
                }
                else if(inputRan == 2){
                    CLEAR;
                    printf("Geben sie ihr gewuenschtes Maximum ein:");
                    scanf("%u", &maxtest);
                    if(maxtest >= min){
                        max = maxtest;
                        CLEAR;
                    }
                    else{
                        CLEAR;
                        printf("--Das Maximum muss groesser als, oder gleich dem Minimum gewaehlt werden!\n");
                    }
                }
                else{
                    CLEAR;
                }
            }
        }
        ///////////////////////////////////////////////////////////

        /////////////////////////////////////////////Zahlen von Tastatur einlesen
        else if(input == 3){
            CLEAR;
            uint32_t i = 1;
            uint32_t value;
            if(arraysize != 0){
                printf("Geben sie die Elemente des Arrays ein (%u <= Groesse <= %u)\n", min, max);
                while (i <= arraysize) {
                    printf("%u. Element: ", i);
                    scanf("%u", &value);
                    if(value >= min && value <= max) {
                        sortedarray[i - 1] = unsortedarray[i - 1] = value;
                        i++;
                    }
                    else{
                        CLEAR;
                        printf("--Beachten sie die Einschraenkung der Groesse!\n");
                    }
                }
                stocked = 1;
                sorted = 0;
                CLEAR;
                printf("--Sie haben alle Elemente eingegeben.");
            }
            else{
                CLEAR;
                printf("--Legen sie vorerst die Array - Groesse fest!");
            }
        }
        ///////////////////////////////////////////////////////////

        ////////////////////////////////////////////Zufallszahlen erzeugen
        else if(input == 4){
            CLEAR;
            if(arraysize != 0) {
                uint32_t random;
                srand((uint32_t) time(NULL));                                    //Zeit wird benutzt um Zufälligkeit zu gewährleisten
                for (uint32_t j = 0; j < arraysize; j++) {
                    random = (uint32_t) rand();
                    sortedarray[j] = unsortedarray[j] = (random % (max - min + 1)) + min;
                    printf("%u. Element: %u\n", j+1, sortedarray[j]);
                }
                stocked = 1;
                sorted = 0;
            }
            else{
                printf("--Legen sie vorerst die Array - Groesse fest!");
            }
        }
        ///////////////////////////////////////////////////////////

        /////////////////////////////////////////////Array ausgeben
        else if(input == 5){
            CLEAR;
            inputArr = 0;
            if(arraysize != 0){
                if(stocked == 1){
                    while(inputArr != 3){
                        IARRAY();
                        inputArr = 0;
                        scanf("%hu", &inputArr);
                        getchar();                  //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)
                        if(inputArr == 1){
                            CLEAR;
                            if(sorted == 1){
                                for(uint16_t j = 0; j < arraysize; j++){
                                    printf("%u. Element: %u\n", j+1, sortedarray[j]);
                                }
                            }
                            else{
                                printf("Ihr Array wurde noch nicht sortiert!");
                            }
                        }
                        else if(inputArr == 2){
                            CLEAR;
                            for(uint16_t j = 0; j < arraysize; j++){
                                printf("%u. Element: %u\n", j+1, unsortedarray[j]);
                            }
                        }
                    else{
                        CLEAR;
                    }
                    }
                    CLEAR;
                }
                else{
                    printf("--Ihrem Array sind noch keine Werte zugewiesen worden!");
                }
            }
            else{
                printf("--Legen sie erst die Array Groesse fest und setzen sie die Werte!");
            }
        }
        ///////////////////////////////////////////////////////////

        ///////////////////////////////////////////////Array sortieren mit...
        else if(input == 6){
            CLEAR;
            inputSorts = 0;
            if(arraysize != 0){
                if(stocked == 1){
                    while(inputSorts != 10){
                        ISORTS();
                        inputSorts = 0;
                        scanf("%hu", &inputSorts);
                        getchar();       //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)

                        if(inputSorts == 1){    //Bubblesort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = BubbleSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Bubblesort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 2){    //Insertionsort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = InsertionSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Insertionsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 3){    //Selectionsort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = SelectionSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Selectionsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 4){    //Mergesort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = MergeSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Mergesort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 5){    //Quicksort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            //comparisons = QuickSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Quicksort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 6){    //Heapsort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            //comparisons = HeapSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Heapsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 7){    //Shellsort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            //comparisons = ShellSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Shellsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 8){    //Cocktailsort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = CocktailSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Cocktailsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 9){    //Radixsort
                            CLEAR;
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = RadixSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("\nArray durch Radixsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }
                        else{
                            CLEAR;
                        }
                    }
                    CLEAR;
                }
                else{
                    printf("--Ihrem Array sind noch keine Werte zugewiesen worden!");
                }
            }
            else{
                printf("--Legen sie erst die Array Groesse fest und setzen sie die Werte!");
            }

        }
        ///////////////////////////////////////////////////////////

        //////////////////////////////////////////////Vergleich mehrerer Sorts
        else if(input == 7){
            CLEAR;
            inputComp = 0;
            SortsCount = 0;
            if(arraysize != 0){
                if(stocked == 1){
                    while(inputComp != 6){
                        printf("Derzeit aktivierte Sorts: ");
                        if(BubSwitch == 1){
                            printf("Bubble | ");
                        }
                        if(InsSwitch == 1){
                            printf("Insertion | ");
                        }
                        if(SelSwitch == 1){
                            printf("Selection | ");
                        }
                        if(MerSwitch == 1){
                            printf("Merge | ");
                        }
                        if(QuiSwitch == 1){
                            printf("Quick | ");
                        }
                        if(HeaSwitch == 1){
                            printf("Heap | ");
                        }
                        if(SheSwitch == 1){
                            printf("Shell | ");
                        }
                        if(CocSwitch == 1){
                            printf("Cocktail | ");
                        }
                        if(RadSwitch == 1){
                            printf("Radix | ");
                        }
                        ICOMP();
                        inputComp = 0;
                        scanf("%hu", &inputComp);
                        getchar();              //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)
                        if(inputComp == 1){
                            CLEAR;
                            BubSwitch = InsSwitch = SelSwitch = MerSwitch = QuiSwitch = 1;
                            HeaSwitch = SheSwitch = CocSwitch = RadSwitch = 1;
                        }
                        else if(inputComp == 2){
                            CLEAR;
                            BubSwitch = InsSwitch = SelSwitch = MerSwitch = QuiSwitch = 0;
                            HeaSwitch = SheSwitch = CocSwitch = RadSwitch = 0;
                        }
                        else if(inputComp == 3){
                            CLEAR;
                            SortsCount = 0;
                            inputList = 0;
                            if((BubSwitch + InsSwitch + SelSwitch + MerSwitch + QuiSwitch + HeaSwitch + SheSwitch + CocSwitch + RadSwitch) >= 1){
                            printf("Vergleich der Sorts wird durchgefuehrt...\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.");
                                if(BubSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    Sorts[SortsCount].comparisons = BubbleSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Bubblesort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(InsSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    Sorts[SortsCount].comparisons = InsertionSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Insertionsort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(SelSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    Sorts[SortsCount].comparisons = SelectionSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Selectionsort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(MerSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    Sorts[SortsCount].comparisons = MergeSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Mergesort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(QuiSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    //Sorts[SortsCount].comparisons = QuickSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Quicksort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(HeaSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    //Sorts[SortsCount].comparisons = HeapSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Heapsort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(SheSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    //Sorts[SortsCount].comparisons = ShellSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Shellsort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(CocSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    Sorts[SortsCount].comparisons = CocktailSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Cocktailsort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                if(RadSwitch == 1){
                                    for(uint32_t n = 0; n < arraysize; n++){
                                        sortedarray[n] = unsortedarray[n];
                                    }
                                    GetSystemTime(&before);
                                    Sorts[SortsCount].comparisons = RadixSort(sortedarray, arraysize);
                                    GetSystemTime(&later);
                                    Sorts[SortsCount].time = (uint32_t) ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                                    strcpy(Sorts[SortsCount].name, "Radixsort");
                                    SortsCount++;
                                    sorted = 1;
                                }
                                while(inputList != 4){
                                    CLEAR;
                                    for(uint16_t i = 0; i < SortsCount; i++){
                                        printf("%u. %s    Zeit:%ums    Vergleiche: %llu\n", i+1, Sorts[i].name, Sorts[i].time, Sorts[i].comparisons);
                                    }
                                    printf("\n");
                                    ILIST();
                                    inputList = 0;
                                    scanf("%hu", &inputList);
                                    getchar();                  //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)
                                    if(inputList == 1){                          //Sortieren nach Alphabet mit Bubblesort
                                        for(uint32_t n = SortsCount; n > 1; n--){
                                            for(uint32_t m = 0; m < n - 1; m++){
                                                if(Sorts[m].name[0] >= Sorts[m+1].name[0]){
                                                    if(Sorts[m].name[0] == Sorts[m+1].name[0]){
                                                        if(Sorts[m].name[1] > Sorts[m+1].name[1]){
                                                            swapstruct(&Sorts[m], &Sorts[m+1]);
                                                        }
                                                    }
                                                    else{
                                                        swapstruct(&Sorts[m], &Sorts[m+1]);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    if(inputList == 2){                                               //Sortieren nach Zeit mit Bubblesort
                                        for(uint32_t n = SortsCount; n > 1; n--){
                                            for(uint32_t m = 0; m < n - 1; m++){
                                                if(Sorts[m].time > Sorts[m+1].time){
                                                    swapstruct(&Sorts[m], &Sorts[m+1]);
                                                }
                                            }
                                        }
                                    }
                                    if(inputList == 3){                                               //Sortieren nach Vergleichen mit Bubblesort
                                        for(uint32_t n = SortsCount; n > 1; n--){
                                            for(uint32_t m = 0; m < n - 1; m++){
                                                if(Sorts[m].comparisons > Sorts[m+1].comparisons){
                                                    swapstruct(&Sorts[m], &Sorts[m+1]);
                                                }
                                            }
                                        }
                                    }
                                }
                                CLEAR;

                            }
                            else{
                                printf("Es muss mindestens ein Sort ausgewaehlt sein!\n");
                            }
                        }
                        else if(inputComp == 4){
                            inputArrSwi = 0;
                            while(inputArrSwi != 10){
                                CLEAR;
                                printf("Fuegen sie die gewuenschten Sorts zu dem Vergleich hinzu.\nDerzeit aktivierte Sorts: ");
                                if(BubSwitch == 1){
                                    printf("Bubble | ");
                                }
                                if(InsSwitch == 1){
                                    printf("Insertion | ");
                                }
                                if(SelSwitch == 1){
                                    printf("Selection | ");
                                }
                                if(MerSwitch == 1){
                                    printf("Merge | ");
                                }
                                if(QuiSwitch == 1){
                                    printf("Quick | ");
                                }
                                if(HeaSwitch == 1){
                                    printf("Heap | ");
                                }
                                if(SheSwitch == 1){
                                    printf("Shell | ");
                                }
                                if(CocSwitch == 1){
                                    printf("Cocktail | ");
                                }
                                if(RadSwitch == 1){
                                    printf("Radix | ");
                                }
                                ISORTS();
                                inputArrSwi = 0;
                                scanf("%hu", &inputArrSwi);
                                getchar();              //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)
                                if(inputArrSwi == 1){
                                    BubSwitch = 1;
                                }
                                if(inputArrSwi == 2){
                                    InsSwitch = 1;
                                }
                                if(inputArrSwi == 3){
                                    SelSwitch = 1;
                                }
                                if(inputArrSwi == 4){
                                    MerSwitch = 1;
                                }
                                if(inputArrSwi == 5){
                                    QuiSwitch = 1;
                                }
                                if(inputArrSwi == 6){
                                    HeaSwitch = 1;
                                }
                                if(inputArrSwi == 7){
                                    SheSwitch = 1;
                                }
                                if(inputArrSwi == 8){
                                    CocSwitch = 1;
                                }
                                if(inputArrSwi == 9){
                                    RadSwitch = 1;
                                }
                            }
                            CLEAR;
                        }
                        else if(inputComp == 5){
                            inputArrSwi = 0;
                            while(inputArrSwi != 10){
                                CLEAR;
                                printf("Entfernen sie die gewuenschten Sorts aus dem Vergleich.\nDerzeit aktivierte Sorts: ");
                                if(BubSwitch == 1){
                                    printf("Bubble | ");
                                }
                                if(InsSwitch == 1){
                                    printf("Insertion | ");
                                }
                                if(SelSwitch == 1){
                                    printf("Selection | ");
                                }
                                if(MerSwitch == 1){
                                    printf("Merge | ");
                                }
                                if(QuiSwitch == 1){
                                    printf("Quick | ");
                                }
                                if(HeaSwitch == 1){
                                    printf("Heap | ");
                                }
                                if(SheSwitch == 1){
                                    printf("Shell | ");
                                }
                                if(CocSwitch == 1){
                                    printf("Cocktail | ");
                                }
                                if(RadSwitch == 1){
                                    printf("Radix | ");
                                }
                                ISORTS();
                                inputArrSwi = 0;
                                scanf("%hu", &inputArrSwi);
                                getchar();              //getchar verhindert, dass Programm sich aufhängt, wenn eine Zeichenkette (bzw. Buchstaben eingegeben werden)
                                if(inputArrSwi == 1){
                                    BubSwitch = 0;
                                }
                                if(inputArrSwi == 2){
                                    InsSwitch = 0;
                                }
                                if(inputArrSwi == 3){
                                    SelSwitch = 0;
                                }
                                if(inputArrSwi == 4){
                                    MerSwitch = 0;
                                }
                                if(inputArrSwi == 5){
                                    QuiSwitch = 0;
                                }
                                if(inputArrSwi == 6){
                                    HeaSwitch = 0;
                                }
                                if(inputArrSwi == 7){
                                    SheSwitch = 0;
                                }
                                if(inputArrSwi == 8){
                                    CocSwitch = 0;
                                }
                                if(inputArrSwi == 9){
                                    RadSwitch = 0;
                                }
                            }
                            CLEAR;
                        }
                        else{
                            CLEAR;
                        }
                    }
                    CLEAR;
                }
                else{
                    printf("--Ihrem Array sind noch keine Werte zugewiesen worden!");
                }
            }
            else{
                printf("--Legen sie erst die Array Groesse fest und setzen sie die Werte!");
            }
        }
        ///////////////////////////////////////////////

        ////////////////////////////////////////////////Programm beenden
        else if(input == 8){
            CLEAR;
            //Programm wird beendet
        }
        ////////////////////////////////////////////////

        ////////////////////////////////////////////////
        else{
            CLEAR;
            printf("--Beachten sie die Eingabemoeglichkeiten!");
        }
        ////////////////////////////////////////////////////
    }

    printf("Programm beendet.");

    return 0;
}
