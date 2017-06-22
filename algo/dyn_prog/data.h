#include <iostream>
using namespace std;

unsigned int short_path[][6] = { 
                    { 2, 8, 6, 3, 5, 8},
                    { 5, 6, 5, 9, 7, 2},
                    { 7, 7, 2, 6, 12, 6},
                    { 4, 3, 6, 3, 14, 5},
                    { 5, 9, 3, 3, 4, 5},
                    { 6, 4, 9, 2, 6, 3},
                };
class spath {
    public:
    spath(int row, int cols);
    int spath::disp_paths(unsigned int (*path)[6]) 
    int find_short_path(unsigned int (*path)[6]);
};

spath::spath(int r, int c) {
    int rows = sizeof(short_path)/sizeof(short_path[0]);
    int cols = sizeof(short_path[0])/ sizeof(unsigned int); 
    cout << " \n ";
    cout <<"rows " << rows << " cols " << cols;
    cout << " \n ";
    cout <<"rows " << r << " cols " << c;
    cout << " \n ";
}

int spath::disp_paths(unsigned int (*path)[6]) 
{
    int col = 0, row = 0;
    int columns = 6;
    int rows = 6;

    for(row= 0; row < rows; row++) {
        for(col = 0; col < columns; col++) {
            cout << "  " <<  short_path[row][col];
        }
        cout << " \n ";
    }
}
int find_short_path(unsigned int (*path)[6])
{
}
