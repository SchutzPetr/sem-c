#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include "vector.h"
#include "record.h"
#include "dfs.h"
#include "my-utils.h"


void print_result_vertex(ResultVertex *resultVertex, ResultNodeList *prevNode, int *count) {
    ResultNode *node = resultVertex->list;
    (*count)++;
    while (node != 0) {
        if (node->mark != 0) {
            if (node->resultVertex->list) {
                printf("%d-", node->resultVertex->vertex->id);
            } else {
                printf("%d", node->resultVertex->vertex->id);
            }
            prevNode->next = new_result_node_list(node);
            print_result_vertex(node->resultVertex, prevNode->next, count);

            node->mark--;
            return;
        } else {
            node = node->next;
        }
    }
}

void print_result(ResultVertex *resultVertex) {
    ResultNode *node = resultVertex->list;
    while (node != 0) {
        for (node->mark; node->mark > 0; node->mark--) {
            if (node->resultVertex->list) {
                printf("%d-%d-", resultVertex->vertex->id, node->resultVertex->vertex->id);
            } else {
                printf("%d-%d", resultVertex->vertex->id, node->resultVertex->vertex->id);
            }
            int countOfNodes = 0;
            ResultNodeList *header = new_result_node_list(node);
            print_result_vertex(node->resultVertex, header, &countOfNodes);

            struct Date *dates[countOfNodes];

            int i = 0;
            printf(";");
            while (header != 0) {
                dates[i] = header->data->data->value;
                printf("%d-%d-%d", dates[i]->year, dates[i]->month, dates[i]->day);
                if (header->next) {
                    printf(",");
                }
                i++;
                ResultNodeList *prev = header;
                header = header->next;
                free(prev);
            }
            printf(";");
            if (countOfNodes == 1) {
                printf("0");
            } else {

                bubbleSort_date(countOfNodes, dates);

                int dif = getDifference(dates[0], dates[countOfNodes - 1]);
                printf("%d", dif);
            }
            printf("\n");
        }

        node = node->next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Chybný počet argumentů. Zadejte dfs.exe <soubor-grafu> <id1> <id2> <maxD>");
        return 0;
    }

    char *filename = argv[1];

    if (access(filename, F_OK) == -1) {
        printf("Vstupní soubor nenalezen!");
        return 0;
    }

    int id1 = atoi(argv[2]);

    if (id1 == 0) {
        printf("ID1 musí být celé číslo!");
        return 0;
    }

    int id2 = atoi(argv[3]);

    if (id2 == 0) {
        printf("ID2 musí být celé číslo!");
        return 0;
    }

    FILE *stream = fopen(filename, "r");

    Vector vector;
    create_vector(&vector, 1000);

    char line[1024];
    Record *head = NULL;
    Record *prev_record = NULL;
    while (fgets(line, 1024, stream)) {
        char *tmp = strdup(line);

        Record *record = allocate_record();
        Date *date = allocate_date();
        sscanf(tmp, "%d;%d;%d-%d-%d", &record->id1, &record->id2, &date->year, &date->month, &date->day);
        record->data = date;
        record->next = 0;

        vector_append(&vector, record->id1);
        vector_append(&vector, record->id2);

        if (!head) {
            head = record;
        } else {
            prev_record->next = record;
        }

        free(tmp);
        prev_record = record;
    }
    fclose(stream);

    Vector copy_vector;
    create_vector(&copy_vector, 1000);

    vector_sort(&vector);
    vector_copy_without_duplicities(&vector, &copy_vector);
    vector_free(&vector);

    Vertex *graph[copy_vector.size - 1];

    int i;
    for (i = 0; i < copy_vector.size; i++) {
        graph[i] = new_vertex(copy_vector.data[i]);
    }
    vector_free(&copy_vector);

    int vertex_size = i - 1;

    bubbleSort_vertex(vertex_size, graph);

    Record *rec = head;
    while (rec) {
        connect(binary_search(vertex_size, graph, rec->id1), binary_search(vertex_size, graph, rec->id2), rec->data);
        rec = rec->next;
    }

    ResultVertex *resultVertex = dfs(graph, vertex_size, binary_search(vertex_size, graph, id1),
                                     binary_search(vertex_size, graph, id2));
    print_result(resultVertex);
    return 0;
}