#include<stdio.h>
#include "../sort_common.h"

int data[] = {3,2,1,4,5};
int g_comp = 0;
//swap
void swap1( int *array, int low, int high )
{
  int temp;

  temp = array[low];
  array[low] = array[high];
  array[high] = temp;

}
int partition( int *array, int low, int high )
{
  int left, right;
  int pivot;

  left = low;
  right = high;
  pivot = array[low];

  while ( left < right )
  {
    while ( array[right] > pivot )
      right--;

    while ( (left < right) && (array[left] <= pivot) )
      left++;

    if ( left < right )
     swap(&array[left], &array[right] );
    g_comp += 1;
  }

  array[low] = array[right];
  array[right] = pivot;

  return right;
}
//medain as pivot
int median( int *array, int low, int high )
{
	int middle = (low+high)/2, upper = low, lower = high, temp;

	if ( array[low] > array[middle] )
		swap( &array[middle], &array[low] );
	if ( array[low] > array[high] )
		swap( &array[low], &array[high] );
	if ( array[middle] > array[high] )
		swap( &array[high], &array[middle] );

	swap(&array[middle], &array[low]);

	return partition(array, low, high);	
}

//quicksort
void quickSort1( int *array, int low, int high )
{
  int pivotPosition;
  
	  if (low < high)
	  {
		  pivotPosition = median(array, low, high);
		  quickSort1(array, low, pivotPosition-1);
		  quickSort1(array, pivotPosition+1, high );
	  }

}

int main(){
	quickSort1(data, 0, sizeof(data)/(sizeof(int)) - 1);
	show_data(sizeof(data)/(sizeof(int)), data);
	printf("No of comparisions %d \n", g_comp);
}
