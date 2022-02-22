#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void swap(char *a, char *b){
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void permute(char *str, int l, int r){
	if(l == r) {
		printf("%s\n",str);
	} else {
		for(int i = l; i <= r; i++) {
			swap(&str[l], &str[i]);
			permute(str,l+1,r);
			swap(&str[l], &str[i]);
	
		}
	}
}

int main(int argc, char **argv){
	char *str = NULL;

	if(argc < 2) {
		printf("Help: str_pemute <input str>\n");
		return 0;
	}
	str = (char *)malloc(sizeof(strlen(argv[1])));
	str = argv[1];
	permute(str, 0, (strlen(str))-1);
}
