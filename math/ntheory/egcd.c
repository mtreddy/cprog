#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
 * FInding inverse modulof a gcd(n,m) == 1
 * P[i] = p[i-2] + p[i-1] * q , where q = n/m r = n%m
 * q = m; m =r
 * and keep going until r == 0 and q == 1
 */
int egcd(int n, int m)
{ 
  
	int p2 = 0, p1 = 1, p0=0;
	int im = m;
	int q = 0;
	int r = 2;

	if( m == 1)
		return 0;
	while( r > 1) {
		//printf("Before:p2=%d p1=%d p0=%d q=%d r=%d n=%d m=%d\n", p2, p1, p0, q, r, n, m);
		q = n/m;
		p2 = p0 - p1 * q;
		p0 = p1;
		p1 = p2;
		r = n%m;
		n = m;
		m = r;
		///printf("After:p2=%d p1=%d p0=%d q=%d r=%d n=%d m=%d\n", p2, p1, p0, q, r, n, m);
	}

	if( p2 < 0)
		p2 += im;
    return p2; 
} 

int main(int argc, char **argv)
{
   int m = 101;//15;//4620;
   int a = 4620; //26;//101;
   if(argc < 2 ) {
	   printf("You did not pass the arguments. We will pick random number\n");
	   printf(" if you want custm args : ./egcd <int-number>\n");
	   //srand(time(0));
	   a = rand();
   }
   printf("a valis %d and modulus is %d\n", a, m);
   printf("inv=%d\n", egcd(a,m));
}
