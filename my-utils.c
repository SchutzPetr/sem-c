//
// Created by schut on 06.01.2018.
//

#include "my-utils.h"
#include <stdio.h>

Vertex* binary_search(int size, struct Vertex *array[size], int id){
    int first = 0;
    int last = size;
    int middle = (first+last)/2;
    while (first <= last) {
        if (array[middle]->id < id)
            first = middle + 1;
        else if (array[middle]->id == id) {
            return array[middle];
        }
        else
            last = middle - 1;

        middle = (first + last)/2;
    }
    return NULL;
}

void bubbleSort_vertex(int size, struct Vertex *array[size]){
    int i;
    int j;

    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            if(array[j+1]->id < array[j]->id){
                Vertex* tmp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tmp;
            }
        }
    }
}

void bubbleSort_date(int size, struct Date *array[size]){
    int i;
    int j;

    for(i = 0; i < size - 1; i++){
        for(j = 0; j < size - i - 1; j++){
            if(getDays(array[j+1]) < getDays(array[j])){
                Date* tmp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = tmp;
            }
        }
    }
}
