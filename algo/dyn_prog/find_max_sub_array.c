#include<stdio.h>

int arr[16] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};


void find_max_cross_sub_array(int arr[], int l, int m, int h, int *low, int *hi, int *tsum) 
{
	int lsum = -65536;
	int rsum = -65536;
	int sum = 0;
	int i=0,j=0;
	int lmax = 0, rmax = 0; /*indices*/

	for(i=m; i >= l; i--){
		sum = sum + arr[i];
		if(sum > lsum) {
			lsum = sum;
			lmax = i;
		}
	}
	sum = 0;
	for(j=m+1; j <=h; j++){
		sum = sum + arr[j];
		if(sum > rsum){
			rsum = sum;
			rmax = j;
		}
	}
	*low = lmax;
	*hi = rmax;
	*tsum = lsum + rsum; 
	printf("\ncross low=%d hi=%d sum=%d\n", *low, *hi, *tsum);
}

void find_max_sub_array(int arr[], int l, int h, int *low, int *hi, int *sum) 
{
	int m, ll, lh, rl, rh, cl, ch, lsum, rsum, csum ;

	if (l == h) {
		*low = l;
		*hi = h;
		*sum=arr[l];
	} else {
		m = (l + h)/2;
		find_max_sub_array(arr, l, m, &ll, &lh, &lsum);
		find_max_sub_array(arr, m+1, h, &rl, &rh, &rsum);
		find_max_cross_sub_array(arr, l, m, h, &cl, &ch, &csum);
		if ((lsum >= rsum) && (lsum >= csum)) {
			*low = ll;
			*hi = lh;
			*sum = lsum;
		} else if ((rsum >= lsum) && (rsum >= csum)) {
			*low =rl;
			*hi = rh;
			*sum = rsum;
		} else {
			*low = cl;
			*hi = ch;
			*sum = csum;
		}
	}
		
	//printf("low=%d hi=%d sum=%d \n",*low, *hi, *sum);
	return;
}

int main()
{
	int low, hi, sum = 0;

	find_max_sub_array(arr, 0, 15, &low, &hi, &sum);
	printf("\nlow=%d hi=%d sum=%d\n", low, hi, sum);
}

