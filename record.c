//
// Created by schut on 28.12.2017.
//

#include "record.h"
#include <stdlib.h>

/**
 * Allocates memory for record structure
 */
Record* allocate_record(){
    return (Record*)malloc(sizeof(Record));
}

/**
 * Creates a new record
 *
 * @param id1 id of first vertex
 * @param id2 id of second vertex
 * @param data record data
 *
 * @return pointer to record
 */
Record* create_record(int id1, int id2, Date *data){
    Record* record = (Record*)malloc(sizeof(Record));
    record->id1 = id1;
    record->id2 = id2;
    record->data = data;
    record->next = 0;
    return record;
}