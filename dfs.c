//
// Created by schut on 27.12.2017.
//

#include "dfs.h"
#include <stdlib.h>


/**
 * Creates a new vertex
 *
 * @param id
 * @return pointer to new vertex
 */
Vertex* create_vertex(int id){
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    vertex->id = id;
    vertex->linkedList = 0;
    return vertex;
}

/**
 * Connect vertex a and b as linked list
 *
 * @param a vertex a
 * @param b vertex b
 */
void connect(Vertex* a, Vertex* b) {
    Node* node_a = (Node*)malloc(sizeof(Node));
    Node* node_b = (Node*)malloc(sizeof(Node));

    node_a->vertex = b;
    node_b->vertex = a;

    node_a->nextNode = a->linkedList;
    node_b->nextNode = b->linkedList;

    a->linkedList = node_a;
    b->linkedList = node_b;
}