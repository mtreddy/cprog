#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h> 
//#define OBFL_TOR_BASE_ADDR 0xCC000000
#define MAP_SIZE    0x1000000
#define MAP_MASK (MAP_SIZE - 1)
#define FATAL do { fprintf(stderr, "Error at line %d, file %s (%d) [%s]\n", \
        __LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

typedef unsigned char uchar;
typedef u_int8_t  uint8;
typedef u_int16_t uint16;
typedef u_int32_t uint32;
typedef u_int64_t uint64;
void *map_base;

static uint8 reg_read8(uint32 off)
{
    return(*(volatile uint8 *)(map_base + off)); 
}

static void reg_write8(uint32 off, uint8 val)
{
   *(volatile uint8*)(map_base + off) = (uint8)val;
}

static uint16 reg_read16(uint32 off)
{
    return(*(volatile uint16 *)(map_base + off)); 
}

static void reg_write16(uint32 off, uint16 val)
{
   *(volatile uint16*)(map_base + off) = (uint16)val;
}

static uint32 reg_read32(uint32 off)
{
    return(*(volatile uint32 *)(map_base + off)); 
}

static void reg_write32(uint32 off, uint32 val)
{
   *(volatile uint32*)((uchar *)map_base + off) = (uint32)val;
}

int main(int argc, char** argv)
{
    int year = 0, month = 0, date = 0, hour = 0, min = 0, sec = 0;
    char getset[10] = "get";
    int fd;
    unsigned long phys_addr = 0;
    uint32 val = 0;
    uint32 offset = 0;
    if(argc < 4) {
        printf("iordwr <mapp-addr> <size 1/2/4> <rd/wr> <offset> [<val>]\n"
               "iordwr <mapp-addr> <size 1/2/4> <dump> <size> \n"
                "Ex wr: iordwr.cxxbin_static 0xcc000000 2 wr 0xAAA 0x90\n"
                "iordwr.cxxbin_static 0xcc000000 2 rd 0 \n");
        return 0;
    }

    /*Base always hex*/
    sscanf(argv[1],"0x%x",&phys_addr);
    if(!phys_addr) {
        printf("Invalid Phys address\n");
        return -1;
    }
    /*offset always hex*/
    sscanf(argv[4],"0x%x",&offset);


    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) FATAL;
    printf("/dev/mem opened.\n");
    
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, phys_addr & ~MAP_MASK);

    if(strcmp(argv[3], "rd") == 0) {
        printf("phys addr %s virt addr 0x%x  size %s  acc %s offset 0x%x\n",
                argv[1], map_base, argv[2], argv[3], offset);

        if(strcmp(argv[2], "1") == 0)
            printf("Val = 0x%x\n", reg_read8((offset)));
        else if(strcmp(argv[2], "2") == 0)
            printf("Val = 0x%x\n", reg_read16((offset)));
        else if(strcmp(argv[2], "4") == 0)
            printf("Val = 0x%x\n", reg_read32((offset)));
        else 
            printf("Invalide size type");
    } else if(strcmp(argv[3], "wr") == 0) {
        /* Value could be hex or decimal so make sure you read it right*/
        sscanf(argv[5],"0x%x",&val);
        if(val == 0)
            val = atoi(argv[5]);
        printf("phys addr %s virt addr 0x%x size %s acc=%s  offset = 0x%x val %s\n",
                argv[1], map_base, argv[2], argv[3], offset, argv[5]);
        if(strcmp(argv[2], "1") == 0)
                reg_write8((offset), val);
        else if(strcmp(argv[2], "2") == 0)
                reg_write16((offset), val);
        else if(strcmp(argv[2], "4") == 0)
                reg_write32((offset), val);
        else 
            printf("Invalide size type");
    } else if(strcmp(argv[3], "dump") == 0) {
        int size = offset;
        int count = 0;
        unsigned int start_offset = phys_addr & MAP_MASK;
        for(count = 0; count <= size; count+=4) {
            printf("addr 0x%llx Val = 0x%x\n", (unsigned long long)map_base + start_offset + count, reg_read32((start_offset + count)));
        }
        
        
    }

    if(munmap(map_base, MAP_SIZE) == -1) FATAL; 
    close(fd);
}
