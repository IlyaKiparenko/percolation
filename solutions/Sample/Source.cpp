#include "SepSet.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>


int main() {
  int EXP_SIZE = 100;
  int n = 3;
  int m = 3;
  int size = n*m + 2*n;
  int* t = new int[size];
  SepSet set(size);
  int count;
  int coord;
  bool f;
  srand(time(0));
  double result = 0;
  int x;
  int y;
  for (int cc = 0; cc < EXP_SIZE; cc++) {
    set.clear();
    f = false;
    count = 0;
    for (int j = 0; j < m; j++) 
      for (int i = 0; i < n; i++) 
        t[i + (j + 1)*n] = 0;
    for (int i = 0; i < n; i++) {
      t[i] = 1;
      t[size - i - 1] = 1;
      set.add(i);
      set.add(size - i - 1);
    }
    for (int i = 1; i < n; i++) {
      set.merge(0, i);
      set.merge(size - 1, size - i - 1);
    } 
    while (!f && count < n*m) {
      do {
        x = rand() % n;
        y = rand() % m;
      } while (t[x + (y+1)*n] == 1);
      count++;
      coord = x + (y+1)*n;
      t[coord] = 1;
      set.add(coord);
      if (x > 0)
        if (t[coord - 1] == 1)
          set.merge(coord, coord - 1);
      if (t[coord - n] == 1)
        set.merge(coord, coord - n);
      if (x < n - 1)
        if (t[coord + 1] == 1)
          set.merge(coord, coord + 1);
      if (t[coord + n] == 1)
        set.merge(coord, coord + n);
      f = (set.whereI(0) == set.whereI(size - 1));
      /*
      for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
          printf("%i ", t[i + (j + 1)*n]);
        }
        printf(" | ");
        for (int i = 0; i < n; i++) {
          printf("%2i ", set.sets[i + (j + 1)*n]);
        }
        printf("\n");
      }
      printf("\n");
      */
    }
    result += count*1.0/n/m;
  }
  printf("percentage = %f\n",result/EXP_SIZE);
}