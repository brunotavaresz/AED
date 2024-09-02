#include "PersonSet.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Person.h"
#include "Date.h"


// Definition of the structure
struct _PersonSet_ {
  int capacity;    // the current capacity of the array
  int size;        // the number of elements currently stored
  Person **array;  // points to an array of pointers to persons
};

#define INITIAL_CAPACITY 4

// Create a PersonSet.
PersonSet *PersonSetCreate() {
  // Allocate space for the struct and the array with INITIAL_CAPACITY elements.
  PersonSet *ps = (PersonSet *)malloc(sizeof(PersonSet));
  if (ps == NULL) {
    return NULL; // Memory allocation failed.
  }

  ps->capacity = INITIAL_CAPACITY;
  ps->size = 0;
  ps->array = (Person **)malloc(sizeof(Person *) * ps->capacity);
  if (ps->array == NULL) {
    free(ps); // Clean up and return NULL if memory allocation fails.
    return NULL;
  }

  return ps;
}

// Destroy PersonSet *pps
void PersonSetDestroy(PersonSet **pps) {
  assert(*pps != NULL);

  // Free the array and the struct, and set the pointer to NULL.
  for (int i = 0; i < (*pps)->size; i++) {
    free((*pps)->array[i]);
  }
  free((*pps)->array);
  free(*pps);
  *pps = NULL;
}

int PersonSetSize(const PersonSet *ps) {
  return ps->size;
}

int PersonSetIsEmpty(const PersonSet *ps) {
  return ps->size == 0;
}

void PersonSetPrint(const PersonSet *ps) {
  printf("{\n");
  for (int i = 0; i < ps->size; i++) {
    Person *p = ps->array[i];
    PersonPrintf(p, ";\n");
  }
  printf("}(size=%d, capacity=%d)\n", ps->size, ps->capacity);
}

// Find index in ps->array of person with given id.
// (INTERNAL function.)
static int search(const PersonSet *ps, int id) {
  for (int i = 0; i < ps->size; i++) {
    if (PersonGetId(ps->array[i]) == id) {
      return i; // Person with the given ID found at index i.
    }
  }
  return -1; // Person not found in the set.
}

// Append person *p to *ps, without verifying presence.
// Use only when sure that *p is not contained in *ps!
// (INTERNAL function.)
static void append(PersonSet *ps, Person *p) {
  // If the array is full, double its capacity.
  if (ps->size >= ps->capacity) {
    ps->capacity *= 2;
    ps->array = (Person **)realloc(ps->array, sizeof(Person *) * ps->capacity);
    if (ps->array == NULL) {
      // Memory reallocation failed.
      exit(1); // You can handle this error more gracefully.
    }
  }

  ps->array[ps->size] = p;
  ps->size++;
}

// Add person *p to *ps.
// Do nothing if *ps already contains a person with the same id.
void PersonSetAdd(PersonSet *ps, Person *p) {
  int id = PersonGetId(p);
  if (search(ps, id) == -1) {
    append(ps, p);
  }
}

// Pop one person out of *ps.
Person *PersonSetPop(PersonSet *ps) {
  assert(!PersonSetIsEmpty(ps));
  // Pop and return the person in the last position.
  ps->size--;
  return ps->array[ps->size];
}

// Remove the person with the given id from *ps, and return it.
// If no such person is found, return NULL and leave set untouched.
Person *PersonSetRemove(PersonSet *ps, int id) {
  int index = search(ps, id);
  if (index != -1) {
    Person *removedPerson = ps->array[index];
    ps->size--;

    // Fill the gap in the array by moving the last person to the removed position.
    ps->array[index] = ps->array[ps->size];

    return removedPerson;
  }
  return NULL;
}

// Get the person with the given id of *ps.
// Return NULL if it is not in the set.
Person *PersonSetGet(const PersonSet *ps, int id) {
  int index = search(ps, id);
  if (index != -1) {
    return ps->array[index];
  }
  return NULL;
}

// Return true (!= 0) if set contains a person with the given id, false otherwise.
int PersonSetContains(const PersonSet *ps, int id) {
  return search(ps, id) >= 0;
}

// Return a NEW PersonSet with the union of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated. Client must call PersonSetDestroy!
PersonSet *PersonSetUnion(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) {
    return NULL; // Memory allocation failed.
  }

  for (int i = 0; i < ps1->size; i++) {
    append(ps, ps1->array[i]);
  }

  for (int i = 0; i < ps2->size; i++) {
    Person *person = ps2->array[i];
    if (!PersonSetContains(ps, PersonGetId(person))) {
      append(ps, person);
    }
  }

  return ps;
}

// Return a NEW PersonSet with the intersection of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated. Client must call PersonSetDestroy!
PersonSet *PersonSetIntersection(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) {
    return NULL; // Memory allocation failed.
  }

  for (int i = 0; i < ps1->size; i++) {
    Person *person = ps1->array[i];
    if (PersonSetContains(ps2, PersonGetId(person))) {
      append(ps, person);
    }
  }

  return ps;
}

// Return a NEW PersonSet with the set difference of *ps1 and *ps2.
// Return NULL if allocation fails.
// NOTE: memory is allocated. Client must call PersonSetDestroy!
PersonSet *PersonSetDifference(const PersonSet *ps1, const PersonSet *ps2) {
  PersonSet *ps = PersonSetCreate();
  if (ps == NULL) {
    return NULL; // Memory allocation failed.
  }

  for (int i = 0; i < ps1->size; i++) {
    Person *person = ps1->array[i];
    if (!PersonSetContains(ps2, PersonGetId(person))) {
      append(ps, person);
    }
  }

  return ps;
}

// Return true if *ps1 is a subset of *ps2.
int PersonSetIsSubset(const PersonSet *ps1, const PersonSet *ps2) {
  for (int i = 0; i < ps1->size; i++) {
    Person *person = ps1->array[i];
    if (!PersonSetContains(ps2, PersonGetId(person))) {
      return 0;
    }
  }
  return 1;
}

// Return true if the two sets contain exactly the same elements.
int PersonSetEquals(const PersonSet *ps1, const PersonSet *ps2) {
  return PersonSetIsSubset(ps1, ps2) && PersonSetIsSubset(ps2, ps1);
}
