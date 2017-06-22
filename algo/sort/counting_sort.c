/*
 * gcc.c4.2.1-p4a.x86_64 -g3 counting_sort.c  -o counting_sort 
 * Counting sort 
 *
 * Is a technique based on keys between specific range.
 * It works by counting the number of object having distinct key values(kind of hashing)
 * Then doing some arithemetic to calculate the position of each object in the output
 * sequence.
 * For simplicity, consider the data in the range 0 to 9. 
 *  Input data: 1, 4, 1, 2, 7, 5, 2
 *    1) Take a count array to store the count of each unique object.
 *    Index:     0  1  2  3  4  5  6  7  8  9
 *    Count:     0  2  2  0   1  1  0  1  0  0

 *    2) Modify the count array such that each element at each index 
 *    stores the sum of previous counts. 
 *    Index:     0  1  2  3  4  5  6  7  8  9
 *    Count:     0  2  4  4  5  6  6  7  7  7

 *  The modified count array indicates the position of each object in 
 *  the output sequence.
 *   
 *    3) Output each object from the input sequence followed by 
 *    decreasing its count by 1.
 *    Process the input data: 1, 4, 1, 2, 7, 5, 2. Position of 1 is 2.
 *    Put data 1 at index 2 in output. Decrease count by 1 to place 
 *    next data 1 at an index 1 smaller than this index.
 */
/* end is the last index + 1 */
void csort(int array[], const int end, const int max, const int min)
{
  int i;
  const int range = max-min+1;
  int count[range+1],
      scratch[end];

  for(i=0; i<range+1; i++)
    count[i] = 0;

  /* Set the value of count[i] to the number of
   * elements in array with value i+min-1. */
  for(i=0; i<end; i++) {
    int c = array[i]+1-min;
    count[c]++;
  }

  /* Update count[i] to be the number of
   * elements with value less than i+min. */
  for(i=1; i<range; i++)
    count[i] + = count[i-1];

  /* Copy the elements of array into scratch in
   * stable sorted order. */
  for(i=(end-1); i>=0; i--) {
    int c = array[i]-min;
    int s = count[c];
    scratch[s] = array[i];
    /* Increment count so that the next element
     * with the same value as the current element
     * is placed into its own position in scratch. */
    count[c]++;
  }

  for(i=0; i<end; i++)
    array[i] = scratch[i];
}
