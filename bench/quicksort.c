void swap(int* a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void qs(int* s_arr, int first, int last)
{
    int i = first, j = last, x = s_arr[(first + last) / 2];

    do {
        while (s_arr[i] < x) i++;
        while (s_arr[j] > x) j--;

        if(i <= j) {
            if (s_arr[i] > s_arr[j]) swap(&s_arr[i], &s_arr[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        qs(s_arr, i, last);
    if (first < j)
        qs(s_arr, first, j);
}

int main() {
  int a[] = {7,5,-28,101,9},
    n = sizeof(a) / sizeof(a[0]);
    qs(a, 0, n - 1);
}
