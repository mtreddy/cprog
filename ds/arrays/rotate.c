#include "array_inc.h"
#define A_LEN 10
int A [A_LEN] =  {0, 1,2,3,4,5,6,7,8,9};

void rotate(int A[], int len, int d){
    int D[d];
    for(int i=0; i<d; i++)
        D[i] = A[i];
    for(int i=0; i<len; i++) {
        if(i < (len -d ))
            A[i] = A[i+d];
        else
            A[i] = D[len -(i+d)] ;

    }

}

/*
 */
void rotate_method_2(int A[], int len, int n){
}
int main(){
    print_array(A, A_LEN);
   rotate(A, A_LEN, 1); 
    print_array(A, A_LEN);
   rotate(A, A_LEN, 1); 
    print_array(A, A_LEN);
    return 0;
}
