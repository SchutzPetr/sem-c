//
// Created by schut on 27.12.2017.
//

#include "dfs.h"
#include "date.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Connect vertex a and b as linked list
 *
 * @param a vertex a
 * @param b vertex b
 * @param data
 */
void connect(Vertex* a, Vertex* b, Date *value) {
    Node* node_a = (Node*)malloc(sizeof(Node));
    Node* node_b = (Node*)malloc(sizeof(Node));

    node_a->vertex = b;
    node_b->vertex = a;

    node_a->value = value;
    node_b->value = value;

    node_a->next = a->list;
    node_b->next = b->list;

    a->list = node_a;
    b->list = node_b;
}

Vertex* new_vertex(int id) {
    Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
    vertex->id = id;
    vertex->mark = 0;
    vertex->list = 0;
    vertex->next = 0;

    return vertex;
}

int count_result_mark(ResultVertex* vertex){
    int res = 0;

    ResultNode* node = vertex->list;
    while (node != 0) {
        res+= node->mark;
        node = node->next;
    }
    return res == 0 ? 1 : res;
}

ResultVertex* new_result_vertex(Vertex* vertex) {
    ResultVertex* rv = (ResultVertex*)malloc(sizeof(ResultVertex));
    rv->vertex = vertex;
    rv->list = 0;
    rv->listSize = 0;
    return rv;
}

ResultNode* new_result_node(ResultVertex* a, ResultVertex* b, Node* node) {
    ResultNode* resultNode = (ResultNode*)malloc(sizeof(ResultNode));
    resultNode->resultVertex = b;
    resultNode->data = node;
    resultNode->next = a->list;
    resultNode->mark = count_result_mark(b);
    a->list = resultNode;
    a->listSize++;
    return resultNode;
}

ResultNodeList* new_result_node_list(ResultNode* node){
    ResultNodeList* resultNodeList = (ResultNodeList*)malloc(sizeof(ResultNodeList));
    resultNodeList->data = node;
    resultNodeList->next = 0;
    return resultNodeList;
}

ResultVertex* do_dfs(Vertex *vertex, int* count, Vertex *dest) {
    Node* p = vertex->list;
    if(vertex == dest){
        return new_result_vertex(vertex);
    }
    ResultVertex *a = NULL;
    vertex->mark = ++(*count);
    while (p != 0) {
        if (!p->vertex->mark) {
            ResultVertex* b = do_dfs (p->vertex, count, dest);
            if(b){
                if(!a){
                    a = new_result_vertex(vertex);
                }
                new_result_node(a, b, p);
            }
        }
        p = p->next;
    }
    return a;
}

ResultVertex* dfs(Vertex *graph[], int size, Vertex *start, Vertex *dest) {
    int i;
    int count = 0;
    for (i = 0; i < size; i ++) {
        graph[i]->mark = 0;
    }
    ResultVertex* resultVertex = do_dfs(start, &count, dest);
    return resultVertex;
}