//
// Created by schut on 04.01.2018.
//

#include "date.h"
#include <stdlib.h>

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * Allocates memory for record structure
 */
Date* allocate_date(){
    return (Date*)malloc(sizeof(Date));
}

int countLeapYears(Date* date) {
    int years = date->year;

    if (date->month <= 2){
        years--;
    }

    return years / 4 - years / 100 + years / 400;
}

int getDays(Date* date) {
    long int days = date->year * 365 + date->day;

    int i;
    for (i = 0; i < date->month - 1; i++) {
        days += monthDays[i];
    }

    days += countLeapYears(date);
    return days;
}

int getDifference(Date* date1, Date* date2) {
    return (getDays(date2) - getDays(date1));
}

int date_comparator (const void * a, const void * b) {

    Date* dateA = (Date *)a;
    Date* dateB = (Date *)b;

    return ( getDays(dateA) - getDays(dateB) );
}

