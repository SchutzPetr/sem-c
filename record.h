//
// Created by schut on 28.12.2017.
//

#ifndef SEM_RECORD_H
#define SEM_RECORD_H

#include "date.h"

struct Record {
    int id1;
    int id2;
    Date *data;
    struct Record *next;
};

typedef struct Record Record;

/**
 * Allocates memory for record structure
 */
Record* allocate_record();

/**
 * Creates a new record
 *
 * @param id1 id of first vertex
 * @param id2 id of second vertex
 * @param data record data
 *
 * @return pointer to record
 */
Record* create_record(int id1, int id2, Date *data);

#endif //SEM_RECORD_H
