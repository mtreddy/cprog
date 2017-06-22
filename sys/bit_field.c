//gcc.c4.7.0-p1.x86_64 bit_field.c  -o bit_field
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32;

typedef struct _qsf2sfp_i2c_ctrl_reg_s {
#if defined(__BIG_ENDIAN_BITFIELD)
    uint32          start:1; /**< [31]      wr 1 to start/rd 0 complete  */
    uint32   repeat_start:1; /**< [30]      for read: 1:no repeat start, 0 repeat start*/
    uint32         unused:3; /**< [29-27]   unused*/
    uint32         n_byte:2; /**< [26-25]   [26-25]=x, read x+1 bytes, x=0-3*/
    uint32       nack_err:1; /**< [24]      NACK error occured           */
    uint32    device_addr:7; /**< [23-17]   dev_addr*/
    uint32        command:1; /**< [16]      1-rd 0-wr                   */
    uint32       reg_addr:8; /**< [15-8]    cmd/offset                   */
    uint32         rwdata:8; /**< [7-0]       read only: 1: 16b addr mode, 0: 8b addr mode */
#else
    uint32        rwdata:8; /**< [7:0]     unused              */
    uint32       reg_addr:8; /**< [15-8]    cmd/offset                   */
    uint32        command:1; /**< [16]      1-rd 0-wr                   */
    uint32    device_addr:7; /**< [23-17]   dev_addr*/
    uint32       nack_err:1; /**< [24]      NACK error occured           */
    uint32         n_byte:2; /**< [26-25]   [26-25]=x, read x+1 bytes, x=0-3*/
    uint32         unused:3; /**< [29-27]   unused*/
    uint32   repeat_start:1; /**< [30]      for read: 1:no repeat start, 0 repeat start*/
    uint32          start:1; /**< [31]      wr 1 to start/rd 0 complete  */
#endif
} qsf2sfp_i2c_ctrl_reg_t;

int i2c_read(uint32 i2c_addr, uint32 offset) {
    qsf2sfp_i2c_ctrl_reg_t    i2c_ctrl_reg;
    uint32 reg_val;
    printf("i2c_addr=0x%x\n", i2c_addr);
    printf("%s  i2c_ctrl_reg=0x%x\n", __func__, i2c_ctrl_reg);
    *(uint32 *)&i2c_ctrl_reg = 0;
    i2c_ctrl_reg.command = 1;   // I2C_READ
    printf("%s  i2c_ctrl_reg.command=0x%x\n", __func__, i2c_ctrl_reg);
    i2c_ctrl_reg.device_addr = (uint32)(i2c_addr );
    printf("%s  i2c_ctrl_reg.device_addr=0x%x\n", __func__, i2c_ctrl_reg);
    i2c_ctrl_reg.reg_addr = offset;
    printf("%s  i2c_ctrl_reg.reg_addr=0x%x\n", __func__, i2c_ctrl_reg);
    i2c_ctrl_reg.n_byte = 0;
    i2c_ctrl_reg.repeat_start = 0;
    i2c_ctrl_reg.start = 1;
    i2c_ctrl_reg.rwdata= 0xbe;
    printf("%s  i2c_ctrl_reg.start=0x%x\n", __func__, i2c_ctrl_reg);

    reg_val = *((uint32 *)&i2c_ctrl_reg);
    printf("%s  reg_val=0x%x\n", __func__, reg_val);

    return 0;

}

int main(void)
{
    i2c_read(0x50, 0x30);
}
