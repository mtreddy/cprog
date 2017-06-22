/*
// Returns count of subsequences of S that match T 
// m is length of T and n is length of S
subsequenceCount(S, T, n, m)

   // An empty string is subsequence of all.
   1) If length of T is 0, return 1.

   // Else no string can be a sequence of empty S.
   2) Else if S is empty, return 0.
    
   3) Else if last characters of S and T don't match,
      remove last character of S and recur for remaining
        return subsequenceCount(S, T, n-1, m)

   4) Else (Last characters match), the result is sum
      of two counts.
        
        // Remove last character of S and recur.
        a) subsequenceCount(S, T, n-1, m) + 

        // Remove last characters of S and T, and recur.
        b) subsequenceCount(S, T, n-1, m-1)        
*/
/* C/C++ program to count number of times S appears
   as a subsequence in T */
#include <bits/stdc++.h>
using namespace std;
 
int findSubsequenceCount(string S, string T)
{
    int m = T.length(), n = S.length();
 
    // T can't appear as a subsequence in S
    if (m > n)
        return 0;
 
    // mat[i][j] stores the count of occurrences of
    // T(1..i) in S(1..j).
    int mat[m + 1][n + 1];
 
    // Initializing first column with all 0s. An empty
    // string can't have another string as suhsequence
    for (int i = 1; i <= m; i++)
        mat[i][0] = 0;
 
    // Initializing first row with all 1s. An empty
    // string is subsequence of all.
    for (int j = 0; j <= n; j++)
        mat[0][j] = 1;
 
    // Fill mat[][] in bottom up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // If last characters don't match, then value
            // is same as the value without last character
            // in S.
            if (T[i - 1] != S[j - 1])
                mat[i][j] = mat[i][j - 1];
 
            // Else value is obtained considering two cases.
            // a) All substrings without last character in S
            // b) All substrings without last characters in
            //    both.
            else
                mat[i][j] = mat[i][j - 1] + mat[i - 1][j - 1];
        }
    }
 
    /* uncomment this to print matrix mat
    for (int i = 1; i <= m; i++, cout << endl)
        for (int j = 1; j <= n; j++)
            cout << mat[i][j] << " ";  */
    return mat[m][n] ;
}
 
//  Driver code to check above method
int main()
{
    string T = "ge";
    string S = "geeksforgeeks";
    cout << findSubsequenceCount(S, T) << endl;
    return 0;
}
