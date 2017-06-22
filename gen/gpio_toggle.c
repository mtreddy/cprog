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
    unsigned char val = 0, off;
    ioperm(0x533,3,1);
    ioperm(0x537,3,1);
    ioperm(0x53b,3,1);

    val = inb(0x533);
    printf("inb(0x533) = 0x%x\n",val);

    val = inb(0x537);
    printf("inb(0x537) = 0x%x\n",val);
    outb(0x537, 0x6);
    val = inb(0x537);
    printf("inb(0x537) = 0x%x\n",val);
    while(1) {
        val = inb(0x53b);
        printf("inb(0x53b) = 0x%x\n",val);
        sleep (1);
        //outb(0x53b, 245);
        val = inb(0x53b);
        printf("inb(0x53b) = 0x%x\n",val);
        sleep (1);
        //outb(0x53b, 244);
    }

}
