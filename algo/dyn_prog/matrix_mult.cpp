#include <iostream>
#define ROWS 3
#define COLS 3

int a[ROWS][COLS] = {{1,1,1},{1,1,1},{1,1,1}};
int b[ROWS][COLS] = {{1,1,1},{1,1,1},{1,1,1}};
int c[ROWS][COLS];

class matrix{
    public:
        int multiply_brute(int a[ROWS][COLS], int b[ROWS][COLS]);
};

int matrix::multiply_brute(int a[ROWS][COLS], int b[ROWS][COLS])
{
    int i = 0, j = 0, k = 0;

    for(i = 0; i < ROWS; i++  ) {
        for(j = 0; j < COLS; j++  ) {
            for(k = 0; k < COLS; k++  ) {
                c[i][j] += a[i][k] * b [k][j];
            }
        }
    }
}
void print_matrix(int a[ROWS][COLS])
{
    int i=0,j=0;

    for(i=0;i<ROWS;i++) {
        for(j=0;j<COLS;j++) {
            printf("%0d ", a[j][j]);
        }
            printf("\n");
    }
}
int main()
{
    class matrix mt;
    mt.multiply_brute(a,b);
    print_matrix(a);
    print_matrix(b);
    print_matrix(c);
}

