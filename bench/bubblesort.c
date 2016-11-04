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
  const int array_size = 10;
  int arr[array_size] = {9,8,7,6,5,4,3,2,1,0};
  bubble_sort(arr, array_size);
}
