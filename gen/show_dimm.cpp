/****************************************************************
 * 
 * File: show_dimm.c
 * Name: Tirumala Marri mareddy@cisco.com
 *
 * Description:
 *  Commong utility to control voltage margins.
 * Copyright (c) 1985-2012 by Cisco , Inc.
 *  All rights reserved.
 **************************************************************/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <sys/mman.h>
#include "../../common/mmap/mmap_intf.h"
#include "../common/brd_acc/board_intf.h"
#include "../common/brd_acc/brd_ctrl.h"
#include "../common/fpga_sup/io_fpga.h"
//#include "tor_regdef.h"
//#include "tor_fpga_def.h"
/*
 * argv[1] == dump
 * argv[2] == DIMM-0/DIMM-1
 * 
 * argv[1] == read/write
 * argv[2] == dev-identifier 0x50&0x52/0x30&0x32/0x18&0x1a spd/cmd/temp-sensor
 * argv[3] == reg-offset
 *
 */
extern "C" unsigned int pch_smb_rd( const unsigned int bus, const unsigned int dev_addr,
        const unsigned int offset, const unsigned int asize, const unsigned int dsize,
        const unsigned int num_bytes, unsigned char * rdata);
extern "C" uint32 pch_smb_wr( const uint32 bus, const uint32 dev_addr,  const uint32 offset,
        const uint32 asize, const uint32 dsize, const uint32 num_bytes, const uint8*  wdata);
diag_board_type_t board_type = BOARD_TYPE_NULL;

void dump_spd(int inst)
{
    int i = 0;
    uchar val = 0;
    uint32 dev_addr = 0;
    if(inst == 0)
        dev_addr = 0x50;
    else
        dev_addr = 0x52;

    for(i; i <= 149; i++) {
        pch_smb_rd(0, dev_addr, i, 1, 1, 1, &val);
        //printf(" off:0x%03x val:0x%03x ", i, val);
        printf("%02x", val);
        if((i + 1)%4 == 0)
            printf("\n");
    }
    printf("If this output returned all zero make sure PCIe mem accesses enabled for SMB controlelr.\n"
            "Enable mem write by using:setpci -s 00:1f.3 4.b=6\n");
}

int main(int argc, char** argv)
{
        
    int dev_addr = 0;
    uchar val;
    int offset = 0;
    /*Enable mem writes to SMB ctlr*/
    system("setpci -s 00:1f.3 4.b=6");
                
    if(argc < 3)  {
        printf("show-dimm dump DIMM-0\n");
        printf("usage: show-dimm read <identifier> <offset>\n"
                            "Ex:show-dimm read 0x50 0x0\n");
        printf("usage: show-dimm write <identifier> <offset> <value>\n"
                            " Ex:show-dimm write 0x50 0x0 0x1\n");
        return 0;
    }

    diag_get_board_type(&board_type);
    if( (board_type == BOARD_TYPE_SOCHI)||
        (board_type == BOARD_TYPE_NAGANO)||
        (board_type == BOARD_TYPE_LKPLCD) ) {
        if(strcmp(argv[1], "dump") == 0 ) {
            if(strcmp(argv[2], "DIMM-0") == 0) {
                dump_spd(0);
            }
            else if(strcmp(argv[2], "DIMM-1") == 0) {
                dump_spd(1);
            } else {
                printf("show-dimm dump DIMM-0\n");
                printf("OR show-dimm dump DIMM-1\n");
            }
        } else if(strcmp(argv[1], "read") == 0) {
            if(argc < 4)  {
                printf("usage: show-dimm read <identifier> <offset>\n"
                        "Ex:show-dimm read 0x50 0x0\n");
                return 0;
            }
            dev_addr = strtoul(argv[2], NULL,0);
            offset = strtoul(argv[3], NULL,0);
            pch_smb_rd(0, dev_addr, offset, 1, 1, 1, &val);
            printf("addr 0x%x offset 0x%x val 0x%x\n", dev_addr, offset, val);
        } else if(strcmp(argv[1], "write") == 0) {
            if(argc < 5)  {
                printf("usage: show-dimm write <identifier> <offset> <value>\n"
                        " Ex:show-dimm write 0x50 0x0 0x1\n");
                return 0;
            }
            dev_addr = strtoul(argv[2], NULL,0);
            offset = strtoul(argv[3], NULL,0);
            val = (uchar)strtoul(argv[4], NULL,0);
            pch_smb_wr(0, dev_addr, offset, 1, 1, 1, &val);
            printf("Write:addr 0x%x val 0x%x\n", dev_addr, offset, val);
            pch_smb_rd(0, dev_addr, offset, 1, 1, 1, &val);
            printf("Readback:addr 0x%x val 0x%x\n", dev_addr, offset, val);
        }
    } else {
        printf("This is not supported on this platform....!!\n");
    }
}
