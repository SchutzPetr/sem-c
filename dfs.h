//
// Created by schut on 27.12.2017.
//

#ifndef SEM_DFS_H
#define SEM_DFS_H

#include "date.h"

struct Vertex {
    int id;
    int mark;
    struct Node* list;
    struct Vertex* next;
};

struct Node {
    Date* value;
    struct Vertex* vertex;
    struct Node* next;
};

struct ResultNode{
    int mark;
    struct Node* data;
    struct ResultVertex* resultVertex;
    struct ResultNode* next;
};

struct ResultVertex{
    int listSize;
    struct Vertex* vertex;
    struct ResultNode* list;
};

struct ResultNodeList{
    struct ResultNode* data;
    struct ResultNodeList* next;
};

typedef struct Vertex Vertex;
typedef struct Node Node;
typedef struct ResultNode ResultNode;
typedef struct ResultNodeList ResultNodeList;
typedef struct ResultVertex ResultVertex;

Vertex* new_vertex(int id);

ResultVertex* new_result_vertex(Vertex* vertex);

ResultNode* new_result_node(ResultVertex* a, ResultVertex* b, Node* node);

ResultNodeList* new_result_node_list(ResultNode* node);

void connect(Vertex* a, Vertex* b, Date *value);

ResultVertex* do_dfs(Vertex *vertex, int* count, int length, int max_length, Vertex *dest);

ResultVertex* dfs(Vertex *graph[], int size, int max_length, Vertex *start, Vertex *dest);

ResultVertex* dfs_rec(Vertex *vertex, int* count, Vertex *dest);

void free_result(ResultVertex* resultVertex);

#endif //SEM_DFS_H
