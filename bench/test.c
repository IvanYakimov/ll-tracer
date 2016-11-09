void change(int arr[], int idx, int val) {
  arr[idx] = val;
}

int main () {
  int arr[] = {1,2,3,4}; goto L;
 L:  change(arr, 0, 5);
  change(arr, 1, 6);
  change(arr, 2, 7);
  change(arr, 3, 8);
}
