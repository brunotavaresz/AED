// JMR, 2021

#include "Person.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int lastID = 0;

Person* PersonCreate(const char* fname, const char* lname, int yy, int mm, int dd) {
  if (fname && lname && DateIsValid(yy, mm, dd)) {
    Person* p = (Person*)malloc(sizeof(Person));
    if (p) {
      p->id = ++lastID;
      p->birthDate.year = yy;
      p->birthDate.month = mm;
      p->birthDate.day = dd;
      p->firstName = strdup(fname);
      p->lastName = strdup(lname);
      return p;
    }
  }
  return NULL;
}

void PersonDestroy(Person** pp) {
  if (*pp) {
    free((*pp)->firstName);
    free((*pp)->lastName);
    free(*pp);
    *pp = NULL;
  }
}

void PersonPrintf(Person* p, const char* suffix) {
  if (p == NULL)
    printf("NULL%s", suffix);
  else
    printf("(%d, %s, %s, %s)%s", p->id, p->lastName, p->firstName,
           DateFormat(&(p->birthDate), YMD), suffix);
}

int PersonCompareByBirth(const Person* p1, const Person* p2) {
  return DateCompare(&(p1->birthDate), &(p2->birthDate));
}

int PersonCompareByLastFirstName(const Person* p1, const Person* p2) {
  int lastNameCmp = strcmp(p1->lastName, p2->lastName);
  if (lastNameCmp != 0) {
    return lastNameCmp;
  }
  return strcmp(p1->firstName, p2->firstName);
}
