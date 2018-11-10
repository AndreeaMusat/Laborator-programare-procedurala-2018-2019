#include <stdio.h>

const int MAX_DIM = 1024;

int binary_search(int low, int high, int arr[], int key) {
  if (low > high)
    return -1;

  int mid = low + (high - low) / 2;

  if (arr[mid] == key)
    return mid;
  if (key < arr[mid])
    return binary_search(low, mid - 1, arr, key);
  else
    return binary_search(mid + 1, high, arr, key);
}

int main() {
  // Pentru simplitate, putem presupune ca vectorul nu are elemente
  // duplicat si intotdeauna vom citi x, y astfel incat x < y.

  int n, x, y;
  int arr[MAX_DIM];

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  scanf("%d %d", &x, &y);

  int pos_x = binary_search(0, n - 1, arr, x);

  for (int i = pos_x; i <= n; i++) {
    printf("%d ", arr[i]);
    if (arr[i] == y)
      break;
  }

  return 0;
}