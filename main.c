#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

const char *getfield(char *line, int num) {
    const char *tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n")) {
        if (!--num)
            return tok;
    }
    return NULL;
}

void fill_vector(Vector *vector, FILE *stream) {
    char line[1024];
    while (fgets(line, 1024, stream)) {
        char *tmp = strdup(line);

        const char *tok;
        int num = 2;
        for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
            vector_append(vector, atoi(tok));
            if (!--num) {
                break;
            }
        }
        free(tmp);
    }
}

int main() {
    FILE *stream = fopen("C:\\Users\\schut\\CLionProjects\\sem\\sw2017-02-data.csv", "r");

    Vector vector;
    create_vector(&vector, 1000);

    Vector copy_vector;
    create_vector(&copy_vector, 1000);

    fill_vector(&vector, stream);

    vector_sort(&vector);
    vector_copy_without_duplicities(&vector, &copy_vector);

    int n;
    for (n = 0; n < 100; n++) {
        printf("%d ", copy_vector.data[n]);
    }

    vector_free(&vector);
    vector_free(&copy_vector);
    return 0;
}