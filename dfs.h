//
// Created by schut on 27.12.2017.
//

#ifndef SEM_DFS_H
#define SEM_DFS_H

struct Vertex {
    int id;
    struct Node* linkedList;
};
struct Node {
    struct Vertex* vertex;
    struct Node* nextNode;
};

typedef struct Vertex Vertex;
typedef struct Node Node;

/**
 * Creates a new vertex
 *
 * @param id
 * @return pointer to new vertex
 */
Vertex* create_vertex(int id);

/**
 * Connect vertex a and b as linked list
 *
 * @param a vertex a
 * @param b vertex b
 */
void connect(Vertex* a, Vertex* b);

#endif //SEM_DFS_H
