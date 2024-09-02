// JMR, 2021

#include "Date.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

const Date DateMIN = {0, 1, 1};
const Date DateMAX = {9999, 12, 31};

int DateIsValid(int yy, int mm, int dd) {
  if (yy < DateMIN.year || yy > DateMAX.year)
    return 0;
  if (mm < 1 || mm > 12)
    return 0;
  if (dd < 1 || dd > DateDaysInMonth(yy, mm))
    return 0;
  return 1;
}

static int DateIsLeapYear(int yy) {
  return (yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0;
}

int DateDaysInMonth(int yy, int mm) {
  int isLeap = DateIsLeapYear(yy);
  static const int daysInMonth[2][12] = {
      {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
      {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
  return daysInMonth[isLeap][mm - 1];
}

Date* DateCreate(int yy, int mm, int dd) {
  if (DateIsValid(yy, mm, dd)) {
    Date* d = (Date*)malloc(sizeof(Date));
    if (d) {
      d->year = yy;
      d->month = mm;
      d->day = dd;
      return d;
    }
  }
  return NULL;
}

void DateDestroy(Date** pd) {
  if (*pd) {
    free(*pd);
    *pd = NULL;
  }
}

static const uint8_t monthLength[][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int DateDaysInMonth(int yy, int mm) {
  int isLeap = DateIsLeapYear(yy);
  return monthLength[isLeap][mm - 1];
}

int DateIsLeapYear(int yy) {
  return (yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0;
}

static char* fmts[] = {
    (char*)"%04d-%02d-%02d",        // YMD
    (char*)"%3$02d/%2$02d/%1$04d",  // DMY
    (char*)"%2$02d/%3$02d/%1$04d",  // MDY
};

static char strBuffer[64];

char* DateFormat(const Date* d, int FMT) {
  if (d == NULL)
    snprintf(strBuffer, sizeof(strBuffer), "NULL");
  else
    snprintf(strBuffer, sizeof(strBuffer), fmts[FMT], d->year, d->month,
             d->day);
  return strBuffer;
}

Date* DateParse1(const char* str, int FMT) {
  int yy, mm, dd;
  int n = sscanf(str, fmts[FMT], &yy, &mm, &dd);
  Date* d = NULL;
  if (n == 3 && DateIsValid(yy, mm, dd)) {
    d = DateCreate(yy, mm, dd);
  }
  return d;
}

int DateParse(Date* d, const char* str, int FMT) {
  int yy, mm, dd;
  int n = sscanf(str, fmts[FMT], &yy, &mm, &dd);
  if (n == 3 && DateIsValid(yy, mm, dd)) {
    d->year = yy;
    d->month = mm;
    d->day = dd;
    return 1;
  }
  return 0;
}

int DateCompare(const Date* a, const Date* b) {
  if (a->year != b->year) {
    return a->year - b->year;
  } else if (a->month != b->month) {
    return a->month - b->month;
  } else {
    return a->day - b->day;
  }
}

void DateIncr(Date* d) {
  assert(DateCompare(d, &DateMAX) < 0);
  d->day++;
  if (d->day > DateDaysInMonth(d->year, d->month)) {
    d->day = 1;
    d->month++;
    if (d->month > 12) {
      d->month = 1;
      d->year++;
    }
  }
  assert(invariant(d));
}

void DateDecr(Date* d) {
  assert(DateCompare(d, &DateMIN) > 0);
  d->day--;
  if (d->day < 1) {
    d->month--;
    if (d->month < 1) {
      d->month = 12;
      d->year--;
    }
    d->day = DateDaysInMonth(d->year, d->month);
  }
  assert(invariant(d));
}
