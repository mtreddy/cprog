#include <stdio.h>
typedef int uint32;
#define CMD_STS_START_RDY(val)  (val << 31) 
#define CMD_STS_RD_CURR_REG(val) (val << 30) 
#define CMD_STS_NBYTES_TO_RD(val) (val << 25)
#define CMD_STS_NBYTES_TO_WR(val) ((val & 0x3) << 25) /* max 4 bytes can be written*/
#define CMD_STS_NACK_ERR(val)   (val << 24)
#define CMD_STS_DEV_ADDR(val)   (val << 17)
#define CMD_STS_RD_WR(val)  (val << 16)
#define CMD_STS_CMD_REG_ADDR(val)   (val << 8)
int main(void )
{
        
    uint32 dev_addr = 0xe6;
    uint32 offset = 0;
    uint32 nbyte=0;
    uint32 transac=0;
    uint32 tmp_data = 0, addr = 0, data_addr = 0, time_out = 0;
    uint32 result;

    /*tmp_data |= 0x1 << 31;*/
    tmp_data |= CMD_STS_START_RDY(1);
    /*tmp_data |= (nbyte & 0x3F) << 25;*/
    tmp_data |= CMD_STS_NBYTES_TO_RD((nbyte & 0x3F));
    /*tmp_data &= ~(0x1 << 24);*/
    tmp_data &= ~(CMD_STS_NACK_ERR(1));
    /*tmp_data |= dev_addr << 17;*/
    tmp_data |= CMD_STS_DEV_ADDR(dev_addr);
    /*tmp_data |= 0x1 << 16;*/
    tmp_data |= CMD_STS_RD_WR(1); /*Read*/
    /*tmp_data |= offset << 8;*/
    tmp_data |= CMD_STS_CMD_REG_ADDR(offset);
    printf("val 0x%x\n",tmp_data);
} 
