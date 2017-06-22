/*
Number of permutation with K inversions
Given an array, an inversion is defined as a pair a[i], a[j] such that a[i] > a[j] and i < j. We are given two numbers N and k, we need to tell how many permutation of first N number have exactly K inversion.

Examples:

Input  : N = 3, K = 1
Output : 2
Explanation :  
Total Permutation of first N number,
123, 132, 213, 231, 312, 321
Permutation with 1 inversion : 132 and 213

Input  : N = 4, K = 2
Output : 2
We strongly recommend you to minimize your browser and try this yourself first.

A Naïve way to solve this problem is noting down all permutation then checking count of inversion in them but iterating through permutation itself will take O(N!) time, which is too large.
We can solve this problem using dynamic programming approach. Below is recursive formula.

If N is 0, Count(0, K) = 0

If K is 0, Count(N, 0) = 1 (Only sorted array)

In general case, 
If we have N number and require K inversion, 
Count(N, K) = Count(N - 1, K) + 
              Count(N – 1, K - 1) + 
              Count(N – 1, K – 2) + 
              .... + 
              Count(N – 1, 0)
How does above recursive formula work?
If we have N number and want to have K permutation and suppose all permutation of (N – 1) number are written somewhere, the new number (Nth number and largest) need to be placed in all permutation of (N – 1) number and those whose inversion count becomes K after adding this number should be added in our answer. Now take those set of permutation of (N – 1) number which has let (K – 3) inversion, now we can place this new largest number at position 3 from last, then inversion count will be K, so count(N – 1, K – 3) should be added to our answer, same argument can be given for other inversion also and we will reach to above recursion as final answer.

Below code is written following above recursion in memorization way.
*/

// C++ program to find number of permutation with
// K inversion using Memoization
#include <bits/stdc++.h>
using namespace std;
 
// Limit on N and K
const int M = 100
 
// 2D array memo for stopping solving same problem
// again
int memo[M][M];
 
// method recursively calculates permutation with
// K inversion
int numberOfPermWithKInversion(int N, int K)
{
    //  base cases
    if (N == 0)
        return 0;
    if (K == 0)
        return 1;
 
    //  if already solved then return result directly
    if (memo[N][K] != 0)
        return memo[N][K];
 
    // calling recursively all subproblem of
    // permutation size N - 1
    int sum = 0;
    for (int i = 0; i <= K; i++)
    {
        // Call recursively only if total inversion
        // to be made are less than size
        if (i <= N - 1)
            sum += numberOfPermWithKInversion(N-1, K-i);
    }
 
    //  store result into memo
    memo[N][K] = sum;
 
    return sum;
}
 
//  Driver code to test above methods
int main()
{
    int N = 4;
    int K = 2;
    cout << numberOfPermWithKInversion(N, K);
    return 0;
}


