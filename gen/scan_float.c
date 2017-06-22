#include <stdio.h>

int main(int argc, char** argv)
{
    float val = 0;



    sscanf(argv[1],"%f", &val);

    printf("val=%f argv[1] %s \n",val,argv[1]);

    val = (val * 100)/75;
    printf("val=%f argv[1] %s \n",val,argv[1]);

}
