#define memtest(ulong start, ulong end, char test_type)

struct range_t range[2];
int main()
{
    
    prepare_mem_range(&range[0]);

    if((!memtest(range[0].start, range[0].end, addr_line)) && (!memtest(range[1].start, range[1].end, addr_line))){
        printf("Address line test PASSED for range 0x%lx - 0x%lx and 0x%lx - 0x%x\n",range[0].start. range[0].end,
                range[1].start. range[1].end);
    } else {
        printf("Address line test FAILED for range 0x%lx - 0x%lx and 0x%lx - 0x%x\n",range[0].start. range[0].end,
                range[1].start. range[1].end);
        return -1;
    }

    if((!memtest(range[0].start, range[0].end, data_line)) && (!memtest(range[1].start, range[1].end, data_line))){
        printf("Data line test PASSED for range 0x%lx - 0x%lx and 0x%lx - 0x%lx \n",range[0].start. range[0].end,
                range[1].start. range[1].end);
    } else {
        printf("Data line test FAILED for range 0x%lx - 0x%lx and 0x%lx - 0x%lx \n",range[0].start. range[0].end,
                range[1].start. range[1].end);
        return -1;
    }

    for(start = rang[0].start; (start + 256MB) <= (range[0].end+ 256mb); start+=512MB) {
        if(memest(start, start + 16MB, fill, 0) != 0){
            printf("Memory fill test FAILED for range 0x%lx - 0x%lx \n",range[0].start. range[0].end);
            return -1;
        }
    } 
    for(start = rang[1].start; (start + 256MB) <= (range[1].end+ 256mb); start+=512MB) {
        if(memest(start, start + 16MB, fill, 0) != 0) {
            printf("Memory fill test FAILED for range 0x%lx - 0x%lx \n",range[1].start. range[1].end);
            return -1;
        }
    }
    printf("Memory fill test PASSED for range 0x%lx - 0x%lx and 0x%lx - 0x%lx \n",range[0].start. range[0].end,
                range[1].start. range[1].end);

}
