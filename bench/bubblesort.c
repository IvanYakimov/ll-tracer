void bubble_sort(int arr[], int array_size)
{
  int i, j, tmp;
  for (i = 0; i < (array_size - 1); ++i)
    {
      for (j = 0; j < array_size - 1 - i; ++j )
	{
	  if (arr[j] > arr[j+1])
	    {
	      tmp = arr[j+1];
	      arr[j+1] = arr[j];
	      arr[j] = tmp;
	    }
	}
    }
}   

int main() {
  int arr[] = {2,1,0};
  arr[0] = 1;
  arr[1] = 3;
  arr[2] = 5;
  bubble_sort(arr, 3);
}
