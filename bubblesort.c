#include <stdio.h>
#include <assert.h>

void print_array(const int *arr, int len) {
  int i;
  for (i=0; i<len; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

/* Sorts the first len elements of array in non-decreasing order */
void quicksort(int *array, int len) {
  int partition, left, right, tmp;
  if (len <= 1) return; /* step 3: handle base case */
  partition = array[0];

  /* partition the elements [1..len-1] */
  left = 1;
  right = len-1;
  while (1) {
    while ((right >= left) && array[right] >= partition) right--;
    while ((right >= left) && array[left] <= partition) left++;
    if (right < left) break;
    tmp = array[right];
    array[right] = array[left];
    array[left] = tmp;
  }
  array[0] = array[right];
  array[right] = partition;

  /* step 4: use the force */
  quicksort(array, right);
  quicksort(array+left, len-left);
}
  

/* Sorts the first len elements of array in non-decreasing order,
 * requires len elements of space to be passed along in scratch
 */
void msort(int *array, int *scratch, int len) {
  int leftsz = len/2;
  int l, r, i;
  if (len <= 1) return; /* step 3: handle base case */
  msort(array, scratch, leftsz); /* step 4: use force */
  msort(array+leftsz, scratch, len-leftsz); /* step 4: use force */
  /* step 5: recombine results */
  for (l=r=i=0;(l != leftsz) && (r != len-leftsz);i++) {
    if (array[l] < array[leftsz+r]) {
      scratch[i] = array[l++];
    } else {
      scratch[i] = array[leftsz+r];
      r++;
    }
  }
  for (;l < leftsz; l++, i++)
    scratch[i] = array[l];
  for (;r < len-leftsz; r++, i++)
    scratch[i] = array[leftsz+r];
  for (i=0; i<len; i++)
    array[i] = scratch[i];
}


int *linearsearch(int key, const int *array, int len) {
  int i;
  for (i=0; i<len; i++)
    if (key == array[i])
      return (int *)(array+i);
  return NULL;
}

int *binsearch(int key, const int *array, int len) {
  int left = 0;
  int right = len-1;
  int mid;
  /* at all points in this function, we expect to find key in array
   * at index between left and right inclusive
   */
  while (left <= right) {
    mid = (right+left)/2;
    printf("L %d R %d M %d\n", left, right, mid);
    if (array[mid] == key)
      return (int *)(array+mid);
    if (array[mid] < key)
      left = mid+1;
    else
      right = mid-1;
  }
  return NULL;
}

/* go through the array n times
 * i-th time through the array, we'll traverse the first n-i elements
 * compare each element so traversed with the next element
 * and if the next element is smaller, we swap
 */
void bubblesort(int *array, int len) {
  int i, j, tmp;
  for (i=0; i<len-1; i++) {
    for (j=0; j<len-i-1; j++) {
      if (array[j] > array[j+1]) {
	tmp = array[j];
	array[j] = array[j+1];
	array[j+1] = tmp;
      }
    }
  }
}

void insertsort(int *array, int len) {
  int i, j, sortme;
  for (i=1; i<len; i++) {
    /* PRE: first i elements are already sorted
     * POST: first i+1 elements are now sorted
     * How? take the i+1st element and put it in the "correct" location
     * among the first i+1, shifting over any values as needed
     */
    sortme = array[i];
    for (j=i-1; (j>=0) && (sortme < array[j]); j--) {
      array[j+1] = array[j];
    }
    array[j+1] = sortme;
  }
}

void validate(const int *arr, int len) {
  int i;
  for (i=0; i<len-1; i++)
    assert(arr[i] <= arr[i+1]);
}

#define LEN 16
int main() {
  /* DO NOT WORRY ABOUT THIS */
  FILE *fp = fopen("/dev/urandom", "r");
  int arr[LEN];
  int scr[LEN];
  int i;
  int n;
  for (i=0; i<LEN; i++)
    arr[i] = fgetc(fp);
  /* arr[0] = -1;*/
  print_array(arr, LEN);
  quicksort(arr, LEN);
  print_array(arr, LEN);
  validate(arr, LEN);
  scanf("%d", &n);
  printf("%p\n", binsearch(n, arr, LEN));
  return 0;
}
