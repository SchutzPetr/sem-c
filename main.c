#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "record.h"
#include "dfs.h"
#include "date.h"


void print_result_vertex(ResultVertex* resultVertex, ResultNodeList* prevNode, int* count){
    ResultNode* node = resultVertex->list;
    (*count)++;
    while (node != 0) {
        if(node->mark != 0){
            if(node->resultVertex->list){
                printf ("%d-", node->resultVertex->vertex->id);
            }else{
                printf ("%d", node->resultVertex->vertex->id);
            }
            prevNode->next = new_result_node_list(node);
            print_result_vertex(node->resultVertex, prevNode->next, count);

            node->mark--;
            return;
        }else{
            node = node->next;
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

void print_result(ResultVertex* resultVertex){
    ResultNode* node = resultVertex->list;
    while (node != 0) {
        for (node->mark; node->mark > 0 ; node->mark--) {
            if(node->resultVertex->list){
                printf("%d-%d-", resultVertex->vertex->id, node->resultVertex->vertex->id);
            }else{
                printf("%d-%d", resultVertex->vertex->id, node->resultVertex->vertex->id);
            }
            int countOfNodes = 0;
            ResultNodeList* header = new_result_node_list(node);
            print_result_vertex(node->resultVertex, header, &countOfNodes);

            struct Date* dates[countOfNodes];

            int i = 0;
            printf(";");
            while (header != 0) {
                dates[i] = header->data->data->value;
                printf("%d-%d-%d", dates[i]->year, dates[i]->month, dates[i]->day);
                if(header->next){
                    printf(",");
                }
                i++;
                ResultNodeList* prev = header;
                header = header->next;
                free(prev);
            }
            printf(";");
            if(countOfNodes == 1){
                printf("0");
            }else{

                bubbleSort_date(countOfNodes, dates);

                int dif = getDifference(dates[0], dates[countOfNodes-1]);
                printf("%d", dif);
            }
            printf("\n");
        }

        node = node->next;
    }
}

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

void bubbleSort(int size, struct Vertex *array[size]){
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


int main() {
    FILE *stream = fopen("C:\\Users\\schut\\CLionProjects\\sem\\sw2017-02-data.csv", "r");

    Vector vector;
    create_vector(&vector, 1000);

    char line[1024];
    Record* head = NULL;
    Record* prev_record = NULL;
    while (fgets(line, 1024, stream)) {
        char *tmp = strdup(line);

        Record* record = allocate_record();
        Date* date = allocate_date();
        sscanf(tmp, "%d;%d;%d-%d-%d", &record->id1, &record->id2, &date->year, &date->month, &date->day);
        record->data = date;
        record->next = 0;

        vector_append(&vector, record->id1);
        vector_append(&vector, record->id2);

        if(!head) {
            head = record;
        }else{
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

    //item = (int*) bsearch (&key, values, copy_vector.size-1, sizeof (Vertex), cmpfunc);

    Vertex *graph[copy_vector.size-1];

    int i;
    for (i = 0; i < copy_vector.size; i++) {
        graph[i] = new_vertex(copy_vector.data[i]);
    }

    int vertex_size = i-1;

    bubbleSort(vertex_size, graph);

    Record *rec = head;
    while (rec){
        connect(binary_search(vertex_size, graph, rec->id1), binary_search(vertex_size, graph, rec->id2), rec->data);
        rec = rec->next;
    }

    ResultVertex* resultVertex = dfs (graph, vertex_size, binary_search(vertex_size, graph, 1), binary_search(vertex_size, graph, 7985));
    printf ("DFS: \n");
    print_result(resultVertex);

    vector_free(&vector);
    vector_free(&copy_vector);
    return 0;
}