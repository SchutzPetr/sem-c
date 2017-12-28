//
// Created by schut on 26.12.2017.
//

#ifndef SEM_VECTOR_H
#define SEM_VECTOR_H

typedef struct {
    int size;
    int capacity;
    int *data;
} Vector;

void create_vector(Vector *vector, int initial_capacity);

void vector_append(Vector *vector, int value);

int vector_get(Vector *vector, int index);

void vector_set(Vector *vector, int index, int value);

void vector_expand_capacity(Vector *vector);

void remove_duplicates(Vector *vector);

void vector_free(Vector *vector);

void vector_sort(Vector *vector);

/**
 * Create copy of original vector without duplicities
 *
 * @param original original vector - MUST BE SORTED ASC
 * @param copy pointer to new vector
 */
void vector_copy_without_duplicities(Vector *original, Vector *copy);

#endif //SEM_VECTOR_H
