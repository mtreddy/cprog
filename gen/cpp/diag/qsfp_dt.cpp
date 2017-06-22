#include "qsfp_dt.h" 

int main(void)
{
  printf("qsfp.max_inst=%d\n", qsfp.max_qsfp);
  printf("qsfp->isr[0].pr_isr=0x%0x\n", qsfp.isr[0].pr_isr);
  printf("qsfp->isr[1].pr_isr=0x%0x\n", qsfp.isr[1].pr_isr);
  int i = 0;
  while(qsfp.isr[1].pr_isr != 0) {
    if(i == 3) break;
    printf("qsfp->isr[%d].pr_isr=0x%0x\n", i, qsfp.isr[i].pr_isr);
    ++i;
  }

}
