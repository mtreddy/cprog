/* Q: Given some dollar value in cents (e.g. 200 = 2 dollars, 1000 = 10 dollars),
      find the number of combinations of coins that make up the dollar value.
      There are only penny, nickel, dime, and quarter.
      (quarter = 25 cents, dime = 10 cents, nickel = 5 cents, penny = 1 cent) */
/* A:
Reference: http://andrew.neitsch.ca/publications/m496pres1.nb.pdf
f(n, k): number of ways of making change for n cents, using only the first
         k+1 types of coins.

          +- 0,                        n < 0 || k < 0
f(n, k) = |- 1,                        n == 0
          +- f(n, k-1) + f(n-C[k], k), else
 */

#include <iostream>
#include <vector>
using namespace std;

int C[] = {1, 5, 10, 25};

// Recursive: very slow, O(2^n)
int f(int n, int k)
{
    if (n < 0 || k < 0)
        return 0;

    if (n == 0)
        return 1;

    return f(n, k-1) + f(n-C[k], k); 
}

// Non-recursive: fast, but still O(nk)
int f_NonRec(int n, int k)
{
    vector<vector<int> > table(n+1, vector<int>(k+1, 1));

    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
        {
            if (i < 0 || j < 0) // Impossible, for illustration purpose
            {
                table[i][j] = 0;
            }
            else if (i == 0 || j == 0) // Very Important
            {
                table[i][j] = 1;
            }
            else
            {
                // The recursion. Be careful with the vector boundary
                table[i][j] = table[i][j-1] + 
                    (i < C[j] ? 0 : table[i-C[j]][j]);
            }
        }
    }

    return table[n][k];
}

int main()
{
    cout << f(100, 3) << ", " << f_NonRec(100, 3) << endl;
    cout << f(200, 3) << ", " << f_NonRec(200, 3) << endl;
    cout << f(1000, 3) << ", " << f_NonRec(1000, 3) << endl;

    return 0;
}

