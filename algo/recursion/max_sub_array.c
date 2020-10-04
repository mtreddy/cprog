#include<stdio.h>


struct ret_{
    int low;
    int high;
    int sum
}ret;

int arr[10] = {-2, -3, 4, -1, -2, 1, 5, -3};

struct ret max_sub_array_cross_mid(int low, int high, int arr[]){
   int left_sum = -100; /*Assuming never goes below this*/
   int right_sum = -100; /*Assuming never goes below this*/
   int left_max = low;
   int right_max = high;
   int sum = 0;
   struct ret;
   for(int i = high; i >= low; i--){
	sum += arr[i];
	if(sum > left_sum) {
	        left_sum = sum;
                left_max = i;
	}
   }
   sum = 0;
   for(int i = low+1; i <= high; i++){
        sum += arr[i];
        if(sum > right_sum) {
            right_sum = sum;
            right_max = i;
        }
   }
   ret.low = left_max;
   ret.high = right_max;
   ret.sum = left_sum + right_sum;
   return ret;
}

struct ret max_sub_array(int low, int high, int arr[]){
	if(low == high){
		struct ret;
		ret.low = low;
		ret.high = high;
		ret.sum = arr[ret.low];
		return ret;
	} else {
		struct lret, rret, cret;
		int mid = (low+high)/2;
		lret = max_sub_array(low, mid, arr);
		rret = max_sub_array(mid+1, right, arr);
		cret = max_sub_array_cross_mid(low, high, arr);
		if(lret.sum >= rret.sum && lret.sum >= cret.sum){
			return lret;
		}
		else if(rret.sum >= lret.sum && rret.sum >= cret.sum){
			return lret;
		}
		else 
			return cret;
	}
	return cret;
}

int main(){
	struct ret;
	ret = max_sub_array(0, sizeof(arr)/sizeof(int) -1, arr);
}
