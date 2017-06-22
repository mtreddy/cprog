#include <stdio.h>
#include <cdk_config.h>
#include <bmd_config.h>
#include <phy_config.h>
#include "insieme_enduro.h"

int insdiag_memtest_element(uint32_t *start_addr, uint32_t *end_addr, uint32_t pattern)
{

    uint32_t *cur_addr;
    int rc = 0;
    int errcnt = 0;
    uint32_t cli_interval=0x07FFFFFF;
    uint32_t region_end = 0;
    uint32_t diff_base = 0;
    uint32_t diff_val = 0;
    // Write the pattern
    printf("Pattern [0x%8x], Range:[0x%08x to 0x%08x]\n", 
           pattern, start_addr, end_addr);
    for (cur_addr = (uint32_t *)start_addr;cur_addr <= (uint32_t *)end_addr; cur_addr++)
    {
        if (!(((uint32_t)cur_addr) & cli_interval))
        {
           region_end = (uint32_t)cur_addr + cli_interval;
           if (region_end > (uint32_t)end_addr)
              region_end = (uint32_t)end_addr;
           printf("        Writing addr region:[0x%08x to 0x%08x]\n", (uint32_t)cur_addr, region_end);
           
        }
        *cur_addr = pattern;
    }

    for (cur_addr = (uint32_t *)start_addr;cur_addr <= (uint32_t *)end_addr; cur_addr++)
    {
        if (!(((uint32_t)cur_addr) & cli_interval))
        {
           region_end = (uint32_t)cur_addr + cli_interval;
           if (region_end > (uint32_t)end_addr)
              region_end = (uint32_t)end_addr;
           printf("      Verifying addr region:[0x%08x to 0x%08x]\n", (uint32_t)cur_addr, region_end);
        }
        *cur_addr = pattern;
        if (*cur_addr != pattern)
        {

           printf("Memory mismatch at 0x%08p: DDR3 Memory unit -", cur_addr);
           diff_base = ((uint32_t)cur_addr & 0x4) / 2; // Either 0 or 4
           diff_val = ((*cur_addr)^pattern);
           if (diff_val & 0xFF)
              printf("%d ", diff_base + 0);
           if (diff_val & 0xFF00)
              printf("%d ", diff_base + 1);
           if (diff_val & 0xFF0000)
              printf("%d ", diff_base + 2);
           if (diff_val & 0xFF000000)
              printf("%d ", diff_base + 3);
           printf("\n");
           rc = 1;
           errcnt++;
           if (errcnt >=16)
           {
              printf("Too many errors. Stopping the test...\n");
              return rc;
           }
        }
    }
    return rc;

}



int insdiag_mem_test_full(void)
{
    int rc = 0;
    printf("[ Running full memory march test on DDR3 ]\n");
    rc += insdiag_memtest_nor_inv((uint32_t *)0x01000000, (uint32_t *)0x7f000000, 0xdeadbeef);
    rc += insdiag_memtest_nor_inv((uint32_t *)0x80000000, (uint32_t *)0xb8000000, 0xdeadbeef);   
    printf("\n** Please reset the unit after memory test. Normal operation not guaranteed. **\n\n");
    if (rc == 0)
       printf("\n## PASS: DDR3MARCH\n\n");
    else
       printf("\n## FAIL: DDR3MARCH\n\n");
    return rc;
}
int insdiag_memtest_nor_inv(uint32_t *start_addr, uint32_t *end_addr, uint32_t pattern)
{
    uint32_t def_pattern = 0xdeadbeef;
    uint32_t inv_pattern = 0;
    int rc = 0;
    if (pattern == 0x0)
    {
       pattern = def_pattern;
       printf("No pattern assigned. Using default pattern [0x%08x]\n", pattern);
    }
    inv_pattern = ~def_pattern;

    printf("Pattern [0x%08x] and its inverse [0x%08x] will be used\n", 
           pattern, inv_pattern);

    rc = insdiag_memtest_element(start_addr, end_addr, pattern);
    if (rc != 0)
    {
       printf("Mem march failed with pattern 0x%08x\n", pattern);
       goto cleanup;
    }

    rc = insdiag_memtest_element(start_addr, end_addr, inv_pattern);
    if (rc != 0)
    {
       printf("Mem march failed with inversed pattern 0x%08x\n", inv_pattern);
       goto cleanup;
    }

cleanup:
    return rc;
}

int insdiag_mem_test_quick_check(void)
{
    //uint32_t reg_val, temp_buffer[16];
    uint32_t *reg_byte_ptr;
    uint8_t *reg_byte_ptr0;
    uint8_t *reg_byte_ptr1;
    uint8_t reg_byte0;
    uint8_t reg_byte1;
    uint32_t data_line_test_base = 0x200000;
    uint32_t addr_line_test_base = 0x2400000;
    int i = 0;
    int dlrc = 0;
    int alrc = 0;
#if 0
    mrvl_axp_reg_read(0x15b0, &reg_val)
    if (reg_val & (1<<30))
       printf("[INFO] ERROR occured during DDR3 memory training!\n");
    else
       printf("[INFO] No error during DDR3 memory training.\n");
#endif
    //
    // Simple DDR3 data line test: 
    //

    printf("[ Running quick memory address and data line check on DDR3 ]\n");
    printf("\nTesting DDR3 data lines....\n");
    for (i = 0; i <= 7; i++)
    {
        reg_byte_ptr0 = (uint8_t *)(data_line_test_base + (uint32_t)i);
        // Save original data
        reg_byte0 = *reg_byte_ptr0;
        // Test ff
        *reg_byte_ptr0 = 0xff;
        if (*reg_byte_ptr0 != 0xff)
        { 
           dlrc = -1;
           printf("Dataline test failure: address 0x%08x expected 0x%02x got 0x%02x\n", reg_byte_ptr, 0xff, *reg_byte_ptr);
        }
        *reg_byte_ptr0 = 0x00;
        if (*reg_byte_ptr0 != 0x00)
        { 
           dlrc = -1;
           printf("Dataline test failure: address 0x%08x expected 0x%02x got 0x%02x\n", reg_byte_ptr, 0x00, *reg_byte_ptr);
        }

        // Restore original data
        *reg_byte_ptr0 = reg_byte0;
    }
    if (dlrc == 0)
       printf("Data line test passed\n\n");
    else
       printf("Data line test FAILED\n\n");

    //
    // Simple DDR3 address line test   
    //
    printf("Testing DDR3 address lines...\n");
    for (i = 3; i <= 30;  i++)
    {
        // ptr0 with 0 on this ith line, and ptr1 with 1 on this ith line
        reg_byte_ptr0 = (uint8_t *)((addr_line_test_base & (~(1<<i))) | (0<<i));
        reg_byte_ptr1 = (uint8_t *)((addr_line_test_base & (~(1<<i))) | (1<<i));

        printf("Bit[%d], addr:0x%08p, park:0x%08p\n", i, reg_byte_ptr1, reg_byte_ptr0);

        // Save original value
        reg_byte0 = *reg_byte_ptr0;
        reg_byte1 = *reg_byte_ptr1;

        //Set test value
        *reg_byte_ptr0 = 0x00;
        *reg_byte_ptr1 = 0xff;
        if ((*reg_byte_ptr0 != 0x00)||(*reg_byte_ptr1 != 0xff))
        {
           alrc = -1;
           printf("Physical address bit [%d] is stuck. One of M_BA, M_A_column or M_A_row should be stuck to 0 or 1! \n", i);
        }

        // Restore original value
        *reg_byte_ptr0 = reg_byte0;
        *reg_byte_ptr1 = reg_byte1;
    }
    if (alrc == 0)
       printf("Address line test passed\n\n");
    else
       printf("Address line test FAILED\n\n");

    if ((alrc == 0) && (dlrc == 0))
       printf("## PASS: DDR3QUICK\n\n");
    else
       printf("## FAIL: DDR3QUICK\n\n");
    return (alrc + dlrc);      
}





