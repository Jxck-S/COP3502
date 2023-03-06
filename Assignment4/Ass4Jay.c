#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tugBoat tugboat;

struct tugBoat {
  long long int x, y;
  long long int relocated_x, relocated_y;
  char name[20];
  long long int dot;
  long long int dist;
};

void initTug(tugboat *tug, int x, int y, int xs, int ys) {
  scanf("%lld %lld %s", &tug->x, &tug->y, tug->name);
  tug->relocated_x = tug->x - xs;
  tug->relocated_y = tug->y - ys;
  tug->dot = (tug->relocated_x * x) + (tug->relocated_y * y);
  xs = 0;
  ys = 0;
  tug->dist = (long)pow((tug->relocated_x - xs), 2) +
              (long)pow((tug->relocated_y - ys), 2);
}

void swapTugBoat(tugboat *arr, int i, int j) {
  tugboat *temp = (tugboat *)malloc(sizeof(tugboat));
  temp->x = arr[i].x;
  temp->y = arr[i].y;
  temp->relocated_x = arr[i].relocated_x;
  temp->relocated_y = arr[i].relocated_y;
  strcpy(temp->name, arr[i].name);
  temp->dot = arr[i].dot;
  temp->dist = arr[i].dist;

  arr[i].x = arr[j].x;
  arr[i].y = arr[j].y;
  arr[i].relocated_x = arr[j].relocated_x;
  arr[i].relocated_y = arr[j].relocated_y;
  strcpy(arr[i].name, arr[j].name);
  arr[i].dot = arr[j].dot;
  arr[i].dist = arr[j].dist;

  arr[j].x = temp->x;
  arr[j].y = temp->y;
  arr[j].relocated_x = temp->relocated_x;
  arr[j].relocated_y = temp->relocated_y;
  strcpy(arr[j].name, temp->name);
  arr[j].dot = temp->dot;
  arr[j].dist = temp->dist;
}

tugboat *merge(tugboat *first, int firstSize, tugboat *second, int secondSize) {
  int total = firstSize + secondSize;
  tugboat *result = (tugboat *)calloc(total, sizeof(tugboat));

  int firstPtr = 0;
  int secondPtr = 0;
  for (int i = 0; i < total; i++) {
    if (firstPtr == firstSize) {
      // Empty first array
      result[i] = second[secondPtr];
      secondPtr++;
    } else if (secondPtr == secondSize) {
      // Empty second array
      result[i] = first[firstPtr];
      firstPtr++;
    } else if (first[firstPtr].dot < second[secondPtr].dot) {
      // First is smaller
      result[i] = first[firstPtr];
      firstPtr++;
    } else if (first[firstPtr].dot == second[secondPtr].dot) {
      if (first[firstPtr].dist < second[secondPtr].dist) {
        result[i] = first[firstPtr];
        firstPtr++;
      } else if (first[firstPtr].dist == second[secondPtr].dist) {
        if (strcmp(first[firstPtr].name, second[secondPtr].name) < 0) {
          result[i] = first[firstPtr];

        } else {
          result[i] = second[secondPtr];
        }
      } else {
        result[i] = second[secondPtr];
        secondPtr++;
      }
    } else {
      // Second was equal or smaller
      result[i] = second[secondPtr];
      secondPtr++;
    }
  }

  return result;
}

void mergeSort(tugboat *arr, int size) {
  if (size <= 1)
    return;

  // Getting the sizes of the two halves
  int sizeLeft = size / 2;
  int sizeRight = size - sizeLeft;

  // Get the pointers into the two halves
  tugboat *leftArr = arr;
  tugboat *rightArr = &arr[sizeLeft];

  // Sort the left side
  mergeSort(leftArr, sizeLeft);

  // Sort the right side
  mergeSort(rightArr, sizeRight);

  tugboat *result = (tugboat *)malloc(sizeof(tugboat) * size);

  result = merge(leftArr, sizeLeft, rightArr, sizeRight);

  // Copy result into arr
  for (int i = 0; i < size; i++)
    arr[i] = result[i];

  // Clean up the memory from result
  free(result);
}

void printArray(tugboat *arr, int size) {
  printf("%d\n", size);
  for (int i = 0; i < size; i++) {
    printf("X: %lld\n", arr[i].x);
    printf("Y: %lld\n", arr[i].y);
    printf("Reloc Y: %lld\n", arr[i].relocated_x);
    printf("Reloc Y: %lld\n", arr[i].relocated_y);
    printf("Dot: %lld\n", arr[i].dot);
    printf("Dist: %lld\n", arr[i].dist);
    printf("Name: %s\n", arr[i].name);
  }
  printf("\n");
}

int main(void) {
  int xs, ys, xh, yh;
  scanf("%d %d %d %d", &xs, &ys, &xh, &yh);

  int n;
  scanf("%d", &n);
  tugboat arr[n];
  tugboat solved[n];
  for (int i = 0; i < n; i++) {
    initTug(&arr[i], (xh - xs), (yh - ys), xs, ys);
  }
  printArray(arr, n);

  mergeSort(arr, n);

  printArray(arr, n);

  tugboat prev;

  int j = 0;

  long long int main_vector_x = xh - xs;
  long long int main_vector_y = yh - ys;
  long long int dot_of_main_vector =
      (long)pow(main_vector_x, 2) + (long)pow(main_vector_y, 2);

  for (int i = 0; i < n; i++) {
    if (arr[i].dot <= 0) {
      prev = arr[i];
      continue;
    }
    if (arr[i].dot > dot_of_main_vector) {
      prev = arr[i];
      continue;
    }
    if (arr[i].dot == prev.dot && i != 0) {
      prev = arr[i];
      continue;
    }

    solved[j] = arr[i];
    j++;

    prev = arr[i];
  }

  printArray(solved, j);
  return 0;
}