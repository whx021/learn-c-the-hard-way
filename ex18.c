#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void die(const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }
  exit(1);
}

typedef int (*compare_cb)(int a, int b);
typedef int *(sort_cb)(int *numbers, int count, compare_cb cmp);

int *bubble_sort(int *numbers, int count, compare_cb cmp) {
  int temp = 0;

  int *target = (int *)malloc(sizeof(int) * count);
  if (!target)
    die("Memory error.");

  memcpy(target, numbers, sizeof(int) * count);

  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < count - 1; ++j) {
      if (cmp(target[j], target[j + 1]) > 0) {
        temp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = temp;
      }
    }
  }

  return (target);
}

int *selection_sort(int *numbers, int count, compare_cb cmp) {
  int temp, min_idx;

  int *target = (int *)malloc(sizeof(int) * count);
  if (!target)
    die("Memory error.");

  memcpy(target, numbers, sizeof(int) * count);

  // One by one move boundary of unsorted subarray
  for (int i = 0; i < count - 1; ++i) {
    // Find the minimum element in unsorted array
    min_idx = i;
    for (int j = i + 1; j < count; ++j) {
      if (cmp(target[min_idx], target[j]) > 0) {
        min_idx = j;
      }
    }
    // Swap the found minimum element with first element
    if (min_idx != i) {
      temp = target[i];
      target[i] = target[min_idx];
      target[min_idx] = temp;
    }
  }

  return (target);
}

int sorted_order(int a, int b) { return a - b; }

int reverse_order(int a, int b) { return b - a; }

int strange_order(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

int sorted_order_char(char a, char b) { return a - b; }

void test_sorting(int *numbers, int count, sort_cb sort, compare_cb cmp) {
  int *sorted = sort(numbers, count, cmp);
  if (!sorted)
    die("Failed to sort as requested.");

  for (int i = 0; i < count; ++i) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);

  unsigned char *data = (unsigned char *)cmp;
  for (int i = 0; i < 25; ++i) {
    printf("%02x:", data[i]);
  }

  printf("\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  char **inputs = argv + 1;

  int *numbers = (int *)malloc(sizeof(int) * count);
  if (!numbers)
    die("Memory error.");

  for (int i = 0; i < count; ++i) {
    numbers[i] = atoi(inputs[i]);
  }

  test_sorting(numbers, count, bubble_sort, sorted_order);
  test_sorting(numbers, count, bubble_sort, reverse_order);
  test_sorting(numbers, count, bubble_sort, strange_order);

  test_sorting(numbers, count, selection_sort, sorted_order);
  test_sorting(numbers, count, selection_sort, reverse_order);
  test_sorting(numbers, count, selection_sort, strange_order);

  // passing the wrong argument
  // incompatible function pointer types passing
  // test_sorting(numbers, count, sorted_order_char);

  // passing NULL
  // segmentation fault (core dumped)
  // jump to invalid address stated
  // test_sorting(numbers, count, NULL);

  free(numbers);

  return (0);
}
