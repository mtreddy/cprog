#include <stdio.h>
#include <string.h>
#define C2F(_d) ((9*(_d)/5) + 32)

int main(int argc, char** argv)
{
    int t_hist = 1;
    int t_os = 1;
    int neg = 0;
    int temp = strtoul(argv[1], NULL, 0);

    printf("temp %d\n", temp);

    if(temp < 0)
        neg = -1;
    if(neg) {
        printf("Neg Temp:\n         %d Degrees Cel\n"
                " %d Degrees Fahreheit\n     Alarm Threshold %d\n"      
            "       Shutdown threshold %d\n", temp, C2F(temp), t_hist, t_os);
    } else
        printf("Temp:\n        %d Degrees Cel\n"
                "%d Degrees Fahreheit\n     Alarm Threshold %d\n"      
            "       Shutdown threshold %d\n", temp, C2F(temp), t_hist, t_os);
    if((temp > 100)) {
        printf("ERROR:Temperature seems to be out of range..!\n"
                "                   Expected range is between 100C to -5C\n");
        return -1;
    }
    /*If it was negative temperature it should not be less than -10C */
    if(neg) 
        if((temp < -10)) {
            printf("Warning: Temperature seems to be out of range..!\n"
                    "               Expected range is between 100C to -5C\n");
        }
}
