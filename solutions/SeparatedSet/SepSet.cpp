#include "SepSet.h"
#include "stdio.h"
#include <exception>

SepSet::SepSet() { }

SepSet::SepSet(int size_) {
  size = size_;
  sets = new int[size];
  h = new int[size];

  for (int i = 0; i < size; i++) {
    sets[i] = -1;
    h[i] = 0;
  }
}

void SepSet::add(int i) {
  if (i >= 0 && i < size)
    if (sets[i] == -1) {
      sets[i] = i;
      h[i] = 0;
    } else
      throw new std::exception("double union");
  else
    throw new std::exception("wrong index");
}

void SepSet::merge(int i, int j) {
  if (i >= 0 && i < size && j >= 0 && j < size)
    if (sets[i] != -1 && sets[j] != -1) {
      if (i != j) {
        int a = i;
        int b = j;
        while (sets[a] != a) 
          a = sets[a];
        while (sets[b] != b) 
          b = sets[b];
        if (a!=b)
          if (h[a] <= h[b]) {
            sets[a] = b;
            h[b] +=1;
          } else {
            sets[b] = a;
            h[a] +=1;
          }
      }
    } else
      throw new std::exception("double union");
  else
    throw new std::exception("wrong index");
}

int SepSet::whereI(int i) {
  if (i >= 0 && i < size) {
    if (sets[i] != -1) {
      while (sets[i] != i) 
        i = sets[i];
    }
    return sets[i];
  } else
    throw new std::exception("wrong index");
}

void SepSet::print() {
  printf("sets = ");
  for (int i = 0; i < size; i++) 
    printf("%4i ", sets[i]);
  printf("\n");
  printf("h    = ");
  for (int i = 0; i < size; i++) 
    printf("%4i ", h[i]);
  printf("\n");
}

void SepSet::clear() {
  for (int i = 0; i < size; i++) {
    sets[i] = -1;
    h[i] = 0;
  }
}

SepSet::~SepSet() {
  delete[] sets;
  delete[] h;
}