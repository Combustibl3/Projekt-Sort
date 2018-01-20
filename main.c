#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "sort.h"                   //Einbindung der Sortieralgorithmen
#include "functions.h"              //Einbindung zusätzlicher Funktionen

#define IMAIN UserinterfaceMain
#define IRANGE UserinterfaceRange
#define ISORTS UserinterfaceSorts
#define IARRAY UserinterfaceArrayOut
#define ICOMP UserinterfaceComparison
#define ILIST UserinterfaceList
#define CLEAR system("cls")         //system("cls") dient dazu das normale Windows Terminal zu clearen (Bei Unix Systemen oder anderen Terminals funktioniert
                                    //dies eventuell nicht oder nicht einwandfrei
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

void IMAIN(){       //Hauptmenue. IRANGE, ISORTS, ICOMP und IARRAY sind hierüber zugänglich.
    printf       ("\n1) Array - Groesse festlegen          2) Zahlenbereich waehlen\n"
                    "3) Zahlen von Tastatur einlesen       4) Zufallszahlen erzeugen\n"
                    "5) Array ausgeben                     6) Array sortieren mit...\n"
                    "7) Vergleich mehrerer Sorts           8) Programm beenden\n");
}

void IRANGE(){      //Untermenue. Zum Festlegen der Grenzwerte der Werte.
    printf      ("\n1) Minimum festlegen         2) Maximum festlegen\n"
                   "3) Untermenue verlassen\n");
}

void ISORTS(){      //Untermenue. Zum einzelnen Sortieren mit Sorts.
    printf      ("\n1) Bubblesort          2) Insertionsort\n"
                   "3) Selectionsort       4) Mergesort\n"
                   "5) Quicksort           6) Heapsort\n"
                   "7) Shellsort           8) Cocktailsort\n"
                   "9) Radixsort           10) Untermenue verlassen\n");
}

void IARRAY(){      //Untermenue. Zum Ausgeben des Arrays (sortiert oder unsortiert).
    printf      ("\n1) sortiertes Array          2) unsortiertes Array\n"
                   "3) Untermenue verlassen\n");
}

void ICOMP(){       //Untermenue. Zum Vergleich mehrerer Sorts. ILIST ist hierüber zugänglich.
    printf      ("\n1) alle aktivieren         2) alle deaktivieren\n"
                   "3) Vergleich starten       4) Sort hinzufuegen\n"
                   "5) Sort entfernen          6) Untermenue verlassen\n");
}

void ILIST(){       //Untermenue von ICOMP. Zum Sortieren der Vergleichsergebnisse.
    printf      ("\n1) Liste nach Alphabet sortieren               2) Liste nach Zeit sortieren\n"
                   "3) Liste nach Vergleichen sortieren            4) Untermenue verlassen\n");
}



int main() {


    SYSTEMTIME before;          //Zeitmarke vor der jeweiligen Funktion
    SYSTEMTIME later;           //Zeitmarke nach der jeweiligen Funktion
    int64_t diffms;             //Differenz beider Zeitmarken umgerechnet in ms
    uint64_t comparisons = 0;   //Anzahl der Vergleiche eines Sorts (Ausgangswert jeder Sortfunktion)
    uint16_t input = 0, inputArr = 0, inputSorts = 0, inputRan = 0, inputComp = 0, inputList = 0, inputArrSwi = 0;      //Eingabe des Nutzers für Optionenwahl in verschiedenen Menüs
    uint32_t max = 1000;        //MAXIMAL Wert für den Zahlenbereich
    uint32_t min = 1;           //MINIMAL Wert für den Zahlenbereich
    uint16_t BubSwitch = 0, InsSwitch = 0, SelSwitch = 0, MerSwitch = 0, QuiSwitch = 0, HeaSwitch = 0, SheSwitch = 0, CocSwitch = 0, RadSwitch = 0;    //Switches für Vergleich
    uint16_t SortsCount = 0;    //Zählt wie viele Sorts beim Vergleich aktiviert wurden
    uint16_t stocked = 0;       //Probe ob das Array bestückt ist
    uint16_t sorted = 0;        //Probe ob das Array sortiert ist
    struct infos Sorts[9];      //speichert Ergebnisse des Vergleichs


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
            sortedarray = (uint32_t*) malloc(arraysize * sizeof(uint32_t));     //es wird Speicher für zwei Arrays reserviert
            unsortedarray = (uint32_t*) malloc(arraysize * sizeof(uint32_t));   //"unsortedarray" wird nicht an Funktionen übergeben, "unsortedarray" dient dazu die ursprünglichen Werte zu speichern und
            stocked = 0;                                                        //diese "sortedarray" vor einem Sort zu übergeben
            sorted = 0;
            CLEAR;
            printf("--Die Anzahl der Elemente betraegt nun: %u", arraysize);
        }
        ///////////////////////////////////////////////////////////

        /////////////////////////////////////////Zahlenbereich waehlen
        else if(input == 2){
            uint32_t mintest;       //mintest dient dazu zu prüfen, ob das Minimum kleiner als das Maximum gewählt wurde
            uint32_t maxtest;       //maxtest dient dazu zu prüfen, ob das Maximum größer als das Minimum gewählt wurde
            CLEAR;
            inputRan = 0;
            while(inputRan != 3){
                printf("Derzeitig min: %u   Derzeitiges max: %u", min, max);
                IRANGE();
                inputRan = 0;
                scanf("%hu", &inputRan);
                getchar();
                if(inputRan == 1){
                    CLEAR;
                    printf("Geben sie ihr gewuenschtes Minimum ein:");
                    scanf("%u", &mintest);
                    if(mintest <= max){     //Minimum muss kleiner gleich Maximum gewählt werden
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
                    if(maxtest >= min){     //Maximum muss größer gleich Minimum gewählt werden
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
                printf("Geben sie die Elemente des Arrays ein (%u <= Groesse <= %u, %u um zu unterbrechen)\n", min, max, max+1);
                while (i <= arraysize) {
                    printf("%u. Element: ", i);
                    value = max + 2;        //verhindert, dass Fehler beim eingeben von buchstaben auftreten
                    scanf("%u", &value);
                    getchar();
                    if(value >= min && value <= max) {                      //Nutzer gibt manuell alle Werte des Arrays ein
                        sortedarray[i - 1] = unsortedarray[i - 1] = value;  //Werte werden auf gültigkeit überprüft
                        i++;
                    }
                    else if(value == max + 1){          //Mit max+1 kann die Eingabe unterbrochen werden
                    i = arraysize + 1;
                    }
                    else{
                        printf("--Beachten sie die Einschraenkung der Groesse!\n");
                    }
                }
                if(value != max + 1){
                    stocked = 1;
                }
                sorted = 0;
                CLEAR;
                if(value != max + 1){
                    printf("--Sie haben alle Elemente eingegeben.");
                }
                else{
                    printf("--Sie haben die manuelle Eingabe unterbrochen.");
                }
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
                srand((uint32_t) time(NULL));                 //Zeit wird genutzt, um Zufälligkeit zu gewährleisten
                for (uint32_t j = 0; j < arraysize; j++) {
                    random = (uint32_t) rand();
                    sortedarray[j] = unsortedarray[j] = (random % (max - min + 1)) + min;   //Zufallszahlen werden im Bereich des festgelegten Zahlenbereichs generiert
                    //printf("%u. Element: %u\n", j+1, sortedarray[j]);
                }
                stocked = 1;
                sorted = 0;
                printf("--Das Array wurde mit Zufallszahlen gefuellt");
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
                        getchar();
                        if(inputArr == 1){
                            CLEAR;
                            if(sorted == 1){        //sortedarray wird lediglich ausgegeben, wenn es schon sortiert wurde
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
                        scanf("%hu", &inputSorts);  //Nutzer kann manuell wählen, welchen Sort er benutzen will
                        getchar();

                        if(inputSorts == 1){    //Bubblesort
                            CLEAR;
                            printf("Array wird mit Bubblesort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){    //Werte von "unsortedarray" werden auf "sortarray" übertragen
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);         //Zeit vor Start des Sorts wird gespeichert
                            comparisons = BubbleSort(sortedarray, arraysize);
                            GetSystemTime(&later);          //Zeit nach Ende des Sorts wird gespeichert und Differenz wird gebildet
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            /*for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }*/
                            printf("Array durch Bubblesort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);     //Benötigte Vergleichtsschritte werden ausgegeben
                            printf("Benoetigte Zeit:        %lldms\n", diffms);        //Benötigte Zeit wird ausgegeben
                        }

                        else if(inputSorts == 2){    //Insertionsort
                            CLEAR;
                            printf("Array wird mit Insertionsort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = InsertionSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            /*for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }*/
                            printf("Array durch Insertionsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 3){    //Selectionsort
                            CLEAR;
                            printf("Array wird mit Selectionsort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = SelectionSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            /*for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }*/
                            printf("Array durch Selectionsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 4){    //Mergesort
                            CLEAR;
                            printf("Array wird mit Mergesort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = MergeSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            /*for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }*/
                            printf("Array durch Mergesort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 5){    //Quicksort
                            CLEAR;
                            printf("Array wird mit Quicksort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            //comparisons = QuickSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            for(uint32_t j = 0; j < arraysize; j++){            //////////NOCH NICHT AUSKOMMENTIERT
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("Array durch Quicksort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 6){    //Heapsort
                            CLEAR;
                            printf("Array wird mit Heapsort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            //comparisons = HeapSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            for(uint32_t j = 0; j < arraysize; j++){            //////////NOCH NICHT AUSKOMMENTIERT
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("Array durch Heapsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 7){    //Shellsort
                            CLEAR;
                            printf("Array wird mit Shellsort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            //comparisons = ShellSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            for(uint32_t j = 0; j < arraysize; j++){            //////////NOCH NICHT AUSKOMMENTIERT
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }
                            printf("Array durch Shellsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 8){    //Cocktailsort
                            CLEAR;
                            printf("Array wird mit Cocktailsort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = CocktailSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            /*for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }*/
                            printf("Array durch Cocktailsort sortiert.\n");
                            printf("Benoetigte Vergleiche:  %llu\n", comparisons);
                            printf("Benoetigte Zeit:        %lldms\n", diffms);
                        }

                        else if(inputSorts == 9){    //Radixsort
                            CLEAR;
                            printf("Array wird mit Radixsort sortiert... (%u. Elemente)\nJe nach Groesse des gewaehlten Arrays kann dies etwas dauern.", arraysize);
                            for(uint32_t n = 0; n < arraysize; n++){
                                sortedarray[n] = unsortedarray[n];
                            }
                            GetSystemTime(&before);
                            comparisons = RadixSort(sortedarray, arraysize);
                            GetSystemTime(&later);
                            diffms = ((later.wHour - before.wHour)*3600000) + ((later.wMinute - before.wMinute)*60000) +((later.wSecond - before.wSecond)*1000) +((later.wMilliseconds - before.wMilliseconds));
                            sorted = 1;
                            CLEAR;
                            /*for(uint32_t j = 0; j < arraysize; j++){
                                printf("%u. %u\n", j+1, sortedarray[j]);
                            }*/
                            printf("Array durch Radixsort sortiert.\n");
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
                        printf("Derzeit aktivierte Sorts: ");   //Switches entweder 1 (ein) oder 0 (aus)
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
                        getchar();
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
                                if(BubSwitch == 1){                          //Ausgewählte Sorts werden hintereinander ausgeführt
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
                                    for(uint16_t i = 0; i < SortsCount; i++){   //Ergebnisse ausgewählter Sorts werden ab "Anfang" in das Array geschrieben
                                        printf("%u. %s    Zeit:%ums    Vergleiche: %llu\n", i+1, Sorts[i].name, Sorts[i].time, Sorts[i].comparisons);
                                    }
                                    printf("\n");
                                    ILIST();
                                    inputList = 0;
                                    scanf("%hu", &inputList);
                                    getchar();
                                    if(inputList == 1){                                         //Sortieren nach Alphabet mit Bubblesort
                                        for(uint32_t n = SortsCount; n > 1; n--){
                                            for(uint32_t m = 0; m < n - 1; m++){
                                                if(Sorts[m].name[0] >= Sorts[m+1].name[0]){     //Anfangsbuchstaben werden verglichen
                                                    if(Sorts[m].name[0] == Sorts[m+1].name[0]){
                                                        if(Sorts[m].name[1] > Sorts[m+1].name[1]){  //zweite Buchstaben werden verglichen (wegen shell und selection)
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
                                    if(inputList == 2){                                         //Sortieren nach Zeit mit Bubblesort
                                        for(uint32_t n = SortsCount; n > 1; n--){
                                            for(uint32_t m = 0; m < n - 1; m++){
                                                if(Sorts[m].time > Sorts[m+1].time){
                                                    swapstruct(&Sorts[m], &Sorts[m+1]);
                                                }
                                            }
                                        }
                                    }
                                    if(inputList == 3){                                         //Sortieren nach Vergleichen mit Bubblesort
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
                                getchar();
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
