/****************************************************************
 * 
 * File: volt_margin.cpp
 * Name: Tirumala Marri mareddy@cisco.com
 *
 * Description:
 *  Commong utility to control voltage margines.
 * Copyright (c) 1985-2012 by Cisco , Inc.
 *  All rights reserved.
 **************************************************************/
#include <stdio.h>
typedef unsigned int uint32;


#define vmargin_help "HELP: vmargin <psu_name> <set/get> [val]\n"
int psu_read(uint32 offset, uint32 *val);
int psu_write(uint32 offset, uint32 val);

enum {BOARD_TYPE_TOR = 0, BOARD_TYPE_ALTA};
struct brd_psu_acc {
    int (*fn_read)();
    int (*fn_write)();
};
struct brd_psu_info {
    char psu_name[15];
    struct brd_psu_acc acc;
    float  margin[16]; /* max number of sesttings*/
};

struct brd_psu_info sc[3] = {
            {"vdd_core", {psu_read, psu_write},
                    {0, 0 , 0 ,0 , 0, 0, 0, 0, 0, 2.5, 5, 0, 0, 0, 0, 0}}, 
            {"vdd_cpu", {psu_read, psu_write},
                    {0, 0 , 0 ,0 , 0, 0, 0, 0, 0, 0, 0, -5, -2.5, 0, 2.5, 5}},
            {"mrvl_dc", {psu_read, psu_write},
                    {0, 0 , 0 ,0 , 0, 0, 0, 0, -10, -7.5, -5, -2.5, 2.5, 5, 7.5, 10}},
};

struct brd_psu_info tor[2] = {
            {"pwm_trim1", {psu_read, psu_write},
                    {0, 0 , 0 ,0 , 0, 0, 0, 0, -10, -7.5, -5, -2.5, 2.5, 5, 7.5, 10}},
            {"pwm_trim2", {psu_read, psu_write},
                    {0, 0 , 0 ,0 , 0, 0, 0, 0, -10, -7.5, -5, -2.5, 2.5, 5, 7.5, 10}},
};

//static diag_board_type_t board_type = BOARD_TYPE_NULL;
static int board_type ;
int diag_get_board_type(void)
{
    //return BOARD_TYPE_TOR;
    return BOARD_TYPE_ALTA;
}
int psu_read(uint32 offset, uint32 *val)
{
    printf("Function %s called\n", __func__);
    return 0;
}
int psu_write(uint32 offset, uint32 val)
{
    printf("Function %s called\n", __func__);
    return 0;
}
int board_get_vmargin(int inst)
{
    int i = 0, j = 0;
    if(board_type == BOARD_TYPE_ALTA) {
        sc[inst].acc.fn_read(i, &j);
        printf("called SC psu_read\n");
    } else if(board_type == BOARD_TYPE_TOR)  {
        tor[inst].acc.fn_read(i, &j);
        printf("called TOR psu_read\n");
    } else
        printf("Invalid board\n");
    printf("board vmargin is 2.5\n");
}
    
int board_set_vmargin(int val, int inst)
{
    int i = 0, j = 0;
    if(board_type == BOARD_TYPE_ALTA) {
        sc[inst].acc.fn_write(i, j);
        printf("called SC psu_write\n");
    } else if(board_type == BOARD_TYPE_TOR)  {
        tor[inst].acc.fn_write(i, j);
        printf("called TOR psu_write\n");
    } else
        printf("Invalid board\n");
    printf("board vmargin set to %d\n", val);
}
int main(int argc, char** argv)
{
    int get_set = 0;
                
    int i = 0;
    /*
     * vmargin <psu_name> <set/get> [val]
     */

    board_type = diag_get_board_type();
    if(argc < 3){
        printf(vmargin_help);
    } else if(argv[2]) {
        if(strcmp(argv[2], "set") == 0)  {
            get_set = 1;
        } else {
            get_set = 0;
        }
        //diag_get_board_type(&board_type);
        if(board_type == BOARD_TYPE_ALTA) {
            if(strcmp(argv[1], sc[0].psu_name) == 0) {
                printf("psu names %s\n",sc[0].psu_name );
                if(get_set == 1) {
                    board_set_vmargin(atoi(argv[3]), 0);
                } else
                    board_get_vmargin(0);
            } else if(strcmp(argv[1], sc[1].psu_name) == 0) {
                printf("psu names %s\n",sc[1].psu_name );
                if(get_set == 1) {
                    board_set_vmargin(atoi(argv[3]), 1);
                } else
                    board_get_vmargin(1);
            } else if(strcmp(argv[1], sc[2].psu_name) == 0) {
                printf("psu names %s\n",sc[2].psu_name );
                if(get_set == 1) {
                    board_set_vmargin(atoi(argv[3]), 2);
                } else
                    board_get_vmargin(2);
            } else {
                printf("Invalid PSU name. Here is the list of valid PSUs\n");
                for(i = 0; i < 3; i++)
                    printf("Valied PSU names are - %s \n",sc[i].psu_name);
            }
        }   else if(board_type == BOARD_TYPE_TOR) {
            if(strcmp(argv[1], tor[0].psu_name) == 0) {
                    printf("psu name %s\n",tor[0].psu_name );
                if(get_set == 1) {
                    board_set_vmargin(atoi(argv[3]), 0);
                } else
                    board_get_vmargin(0);
            } else if(strcmp(argv[1], tor[1].psu_name) == 0) {
                printf("psu name %s\n",tor[1].psu_name );
                if(get_set == 1) {
                    board_set_vmargin(atoi(argv[3]), 1);
                } else
                    board_get_vmargin(1);
            } else {
                printf("Invalid PSU name. Here is the list of valid PSUs\n");
                for(i = 0; i < 2; i++)
                    printf("Valied PSU names are - %s \n",tor[i].psu_name);
            }
        } else { 
            printf("Unspported board\n");
            return 0;
        }

    }
     else {
         printf(vmargin_help);
     }
}

