//
// Created by schut on 26.12.2017.
//
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

void create_vector(Vector *vector, int initial_capacity) {
    vector->size = 0;
    vector->capacity = initial_capacity;
    vector->data = malloc(sizeof(int) * vector->capacity);
}

void vector_append(Vector *vector, int value) {
    vector_expand_capacity(vector);
    vector->data[vector->size++] = value;
}

int vector_get(Vector *vector, int index) {
    if (index >= vector->size || index < 0) {
        printf("Array out of bounds exception: Index %d, Vector size %d\n", index, vector->size);
        exit(1);
    }
    return vector->data[index];
}

void vector_set(Vector *vector, int index, int value) {
    while (index >= vector->size) {
        vector_append(vector, 0);
    }
    vector->data[index] = value;
}

void vector_expand_capacity(Vector *vector) {
    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, sizeof(int) * vector->capacity);
    }
}

int comparator (const void * a, const void * b) {
    int aa = *(const int *)a;
    int bb = *(const int *)b;
    return aa - bb;
}

/**
 * Create copy of original vector without duplicities
 *
 * @param original original vector - MUST BE SORTED ASC
 * @param copy pointer to new vector
 */
void vector_copy_without_duplicities(Vector *original, Vector *copy){
    int i;
    int lastRecord = original->data[0];
    vector_append(copy, lastRecord);
    for(i = 1; i < original->size; i++){
        if(lastRecord == original->data[i]){
            continue;
        }
        lastRecord = original->data[i];
        vector_append(copy, lastRecord);
    }
}

void vector_sort(Vector *vector){
    qsort(vector->data, (size_t)vector->size, sizeof(int), comparator);
}

void vector_free(Vector *vector) {
    free(vector->data);
}