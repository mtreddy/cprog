#include <iostream>

//g++  cut_rod.cpp -o cut_rod_cpp
int len[] = {1, 5, 8, 9, 10, 17,17, 20};
class cut_rod {
    public:
    int max(int a, int b);
    int cut_rod_brute_force(int *pr, int n);
    int cut_rod_memoized(int *apr, int n);
    int cut_rod_memoized_aux(int *apr, int n, int *r);
    int cut_rod_bottom_up(int *apr, int n);
    int cut_rod_bottom_up_extended(int *apr, int n);
    
};

int cut_rod::max(int a, int b)
{
    return a > b ? a : b;
}
int cut_rod::cut_rod_brute_force(int *price, int n)
{
    if(n <= 0)
        return 0;
    int max_val = 0;

    for (int i=0; i < n; i++) 
        max_val = max(max_val, price[i] + cut_rod_brute_force(price, n-i-1));
    return max_val;
}
    
int cut_rod::cut_rod_memoized(int *apr, int n)
{
    int r[sizeof(len)/sizeof(len[0])];
    int i = 0;
    for(i = 0; i < n; i+=) {
        r[i] = 0;
        return(cut_rod_memoized_aux(apr, n, r));
    }
}
int cut_rod::cut_rod_memoized_aux(int *apr, int n, int *r)
{
    int q = 0;

    if (r[n] > 0)
        return r[n];
    if (n == 0 )
        q = 0;
    else {
        q = 0;
        for(int i = 0; i < n; i++ ){
            q = max(q, p[i] + cut_rod_memoized_aux(p, n-i, r));
        }
        r[n] = q;
    }
    return q;

}
    
int cut_rod::cut_rod_bottom_up(int *apr, int n)
{
    int i = 0, j = 0;
    int r[sizeof(len)/sizeof(len[0])];

    r[0];
    for(i = 0; i< n; i++) {
        for(j = 0; j< n; j++) {
            q = max(q, p[i] + r[j-i]);
            r[i] = q;
        }
    }
    return r[n];
}
int cut_rod::cut_rod_bottom_up_extended(int *apr, int n)
{
    int i = 0, j = 0;
    int r[sizeof(len)/sizeof(len[0])];
    int s[sizeof(len)/sizeof(len[0])];

    r[0];
    for(i = 0; i< n; i++) {
        for(j = 0; j< n; j++) {
            if(q < ()) {
                q =  p[i] + r[j-i];
                s[i] = i;
            }
            r[i] = q;
        }
    }
    //return (r[n];
    return 0;
}

int main()
{
    class cut_rod ct;
    int size = sizeof(len)/sizeof(len[0]);
    printf(" Maximum attainable value is %d\n", ct.cut_rod_brute_force(len, size));
}
