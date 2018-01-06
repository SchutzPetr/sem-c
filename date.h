//
// Created by schut on 04.01.2018.
//

#ifndef UNTITLED_DATE_H
#define UNTITLED_DATE_H

struct Date {
    int day;
    int month;
    int year;
};
typedef struct Date Date;

/**
 * Allocates memory for record structure
 */
Date* allocate_date();

int getDays(Date* date);
int countLeapYears(Date* date);
int getDifference(Date* date1, Date* date2);
int date_comparator (const void * a, const void * b);

#endif //UNTITLED_DATE_H
