#include<stdio.h>
//g++  cut_rod.c -o cut_rod
int len[] = {1, 5, 8, 9, 10, 17,17, 20};
int max(int a, int b)
{
    return a > b ? a : b;
}

int cut_rod(int *price, int n)
{
    if(n <= 0)
        return 0;
    int max_val = 0;

    for (int i=0; i < n; i++) 
        max_val = max(max_val, price[i] + cut_rod(price, n-i-1));
    return max_val;
}

int mem_cut_rod_aux(int *price, int n, int *r)
{
	int q = -1;
	if (r[n] >= 0)
		return r[n];

	if (n < 0)
		q = 0;
	else {
		int i;
		q = -1;
		for(i=0; i <= n; i++){
			q = max(q, price[i]+mem_cut_rod_aux(price, n-i-1, r));
		}
	}
	r[n] = q;
	return q;
}
int mem_cut_rod_bup(int *p, int n)
{
	int r[sizeof(len)/sizeof(int)];
	int i, j, q = -1;
    for(int i=0; i <= n; i++) 
		r[i] = -1;
	for(j=0; j <= n; j++){
		q = -1;
		for(i=0; i <= j; i++){
			q = max(q, p[i]+r[j-i-1]);
		}
		r[j] = q;
	}
	return r[n];
}
int mem_cut_rod_bup_extnd(int *p, int n)
{
	int r[sizeof(len)/sizeof(int)];
	int s[sizeof(len)/sizeof(int)];
	int tmp = 0;
	int i, j, q = -1;
    for(int i=0; i <= n; i++) 
		r[i] = -1;
	for(j=0; j <= n; j++){
		q = -1;
		for(i=0; i <= j; i++){
			tmp = p[i]+r[j-i-1];
			if(q < tmp) {
				q = tmp;
				s[j] = i;
			}
		}
		r[j] = q;
	}
    for(int i=0; i <= n; i++) 
		printf("%d ", s[i]);
	printf("\n");
	return r[n];
}
int mem_cut_rod(int *price, int n)
{
	int r[sizeof(len)/sizeof(int)];
    for(int i=0; i <= n; i++) 
		r[i] = -1;
	return mem_cut_rod_aux(price, n, r);

}
int main ()
{
    int size = sizeof(len)/sizeof(len[0]);
//printf(" Maximum attainable value is %d\n", cut_rod(len, size));
//    printf(" Maximum attainable value is %d\n", mem_cut_rod(len, size-1));
//    printf(" Maximum attainable value is %d\n", mem_cut_rod_bup(len, size-1));
    printf(" Maximum attainable value is %d\n", mem_cut_rod_bup_extnd(len, size-1));

    return 0;
}
