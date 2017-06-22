#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
	int val;
	FILE *file, *file1;
	char str[10];

	file = fopen("num.txt", "r");
	file = fopen("out.txt", "w");
	while(!feof(file)) {
		fgets(str, 10, file);
		val = strtoul(str, NULL, 0);
		fwrite(&val, 4, 1, file1);	
	}
fclose(file);
fclose(file1);
}
