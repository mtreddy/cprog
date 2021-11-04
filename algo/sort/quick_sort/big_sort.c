#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max(a, b) a > b ? a : b

int num_comp(char *a, char  *b) {
	/*If string len of a is greatr than b, obciosly a larger*/
	int alen = strlen(a);
	int blen = strlen(b);
	if(alen > blen)
		return 1;
	else if (blen > alen)
		return 0;
	/* if stren is same we need to loope trhough variables and compare each charecter starting from left to right*/
	int i = 0;
 	while(i<alen) {	
		if(a[i] == b[i]) {
			i++;
			continue;
		}
		if(a[i] > b[i])
			return 1;
		else
			return 0;
	}
	/* Either equal or less*/
	return 0;
}

void num_swap(char **a, char **b){
	char *tmp = *a;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
int partition(char **A, int a, int b){
	int lo = a-1;
	char *pv  = A[b];
	int ind = 0;
	for(ind=a; ind< b; ind++){
	   if(!num_comp(A[ind], pv)){
	      lo++;
	      num_swap(&A[ind], &A[lo]);
	   }
	}
	num_swap(&A[lo+1], &A[b]);
	return (lo+1);
}
void str_qsort(char **A, int p, int q){
	int pivot = 0;
	if(p < q) { 
		pivot = partition(A, p, q);
		str_qsort(A, p, pivot-1);
		str_qsort(A, pivot+1, q);
	}
}
void bubble_sort(char *A[], int len) {
    /*
     * A[0] checked against A[1] to A[len-1]
     * swap if it is less than current element.
     * All the large elements will be placed at the end of thelist
     */
     int i, j ;
     for(i=0; i<len; i++){
	for(j=i+1; j<len; j++){
	   if(num_comp(A[i], A[j])){
		//printf("To Swap A[%d]=%s A[%d]=%s\n", i, A[i], j, A[j]);
	       num_swap(&A[i],&A[j]);
		//printf("After Swap A[%d]=%s A[%d]=%s\n", i, A[i], j, A[j]);
	   }
	}
     }
}
char **Ar;
char** str_sort(char *A[], int len) {
   /*input strings can eb of different *
    * size lets create array with same str size*/
    int ind = 0;
    int slen = 0;
    int tlen = 0;
    for(ind = 0; ind < len; ind++){
       tlen = strlen(A[ind]);
       if(slen < tlen)
	       slen = tlen;
    }
    Ar = (char **)malloc(len * sizeof(char *));
    for(ind = 0; ind < len; ind++) {
      Ar[ind] = (char *)malloc(slen * sizeof(char));
      strcpy(Ar[ind], A[ind]);
    }
    str_qsort(Ar, 0, len-1);
    //bubble_sort(Ar, len);
    printf("Sorted\n");
    for(ind=0; ind<7; ind++)
	printf("%s\n", Ar[ind]);
    return Ar;
}
int main(){
#if 0
	char a[] = "12345";
	char b[] = "abcde";
	if(num_comp(a,b)) 
		printf("a=%s is larger than b=%s\n", a, b);
	else
		printf("a=%s is equal or less han b=%s\n", a, b);
	
	printf("Before swap\n a=%s \n b=%s\n", a, b);
	num_swap(a, b);
	printf("After swap\n a=%s \n b=%s\n", a, b);
#else
	int i = 0;
	//char *A[6] = {"A5","A1", "A3", "A7", "A4", "A2"};
	char *A[] = {"6",
		"31415926535897932384626433832795",
			"1",
			"3",
			"10",
			"3",
			"5"};
	printf("Un Sorted\n");
	for(i=0; i<6; i++)
		printf("%s\n", A[i]);
	char **res = str_sort(&A[0], 7);
	printf("Sorted\n");
	for(i=0; i<6; i++)
		printf("%s\n", res[i]);
#endif
}
