#include<stdio.h>
//#include<sys/io.h>


static __inline unsigned char
inb (unsigned short int __port)
{
      unsigned char _v;
          
        __asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
          return _v;
}   

static __inline unsigned short int 
inw (unsigned short int __port)
{           
      unsigned short _v;
              
        __asm__ __volatile__ ("inw %w1,%0":"=a" (_v):"Nd" (__port));
          return _v;
}           
static __inline unsigned int
inl (unsigned short int __port)
{
      unsigned int _v;

        __asm__ __volatile__ ("inl %w1,%0":"=a" (_v):"Nd" (__port));
          return _v;
}

static __inline void
outb (unsigned char __value, unsigned short int __port)
{
      __asm__ __volatile__ ("outb %b0,%w1": :"a" (__value), "Nd" (__port));
}

static __inline void
outw (unsigned short int __value, unsigned short int __port)
{
      __asm__ __volatile__ ("outw %w0,%w1": :"a" (__value), "Nd" (__port));

}

static __inline void
outl (unsigned int __value, unsigned short int __port)
{
      __asm__ __volatile__ ("outl %0,%w1": :"a" (__value), "Nd" (__port));
}

int main(int argc, char **argv)
{
    unsigned int val = 0, off;
#if 1
    printf("inb(0x538) = 0x%x\n",val);
    ioperm(0x538,3,1);
    //iopl(5);
    val = inb(0x538);
    printf("inb(0x538) = 0x%x\n",val);
#else
    if(strcmp(argv[1], "rd") == 0) {
        sscanf(argv[2], "0x%x", &off);
        if(off == 0)
            off = atoi(argv[2]);
        printf("rd off= 0x%x \n", off);
        printf("val= 0%x\n", system(inb(0x539)));
        //printf("val= 0%x\n", inl(1337));
    }
    else if(strcmp(argv[1], "wr") == 0) {
        sscanf(argv[2], "0x%x", &off);
        if(off == 0)
            off = atoi(argv[2]);
        sscanf(argv[3], "0x%x", &val);
        if(val == 0)
            val = atoi(argv[3]);
        printf("wr: off= 0x%x val= 0%x\n", off, val);
        outb(val, off);
    }
    else
        printf("Invalid operation\n");
#endif
}
