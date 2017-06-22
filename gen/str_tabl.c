#include<stdio.h>

struct bcm_usd_retimer_info_t {
    int sno;
    char front_port_range[20];
    char rt_name[50];
    char tx_dir[5];
    char rx_dir[5];
    char ptype[5];
}bcm_usd_retimer_info_;

struct bcm_usd_retimer_info_t stockholm_rt_info[] = {
    {1,  "97-100", "BCM84328", "Tx", "Rx", "40G"},
    {2,  "98", "BCM84328", "Tx", "Rx", "40G"},
    {3,  "99", "BCM84328", "Tx", "Rx", "40G"},
    {4, "100", "BCM84328", "Tx", "Rx", "40G"},
    {5, "101", "BCM84328", "Tx", "Rx", "40G"},
    {6, "102", "BCM84328", "Tx", "Rx", "40G"},
    {7, "103", "BCM84328", "Tx", "Rx", "40G"},
    {8, "104", "BCM84328", "Tx", "Rx", "40G"},
    {}
};

void bcm_usd_display_rt_info(struct bcm_usd_retimer_info_t rt_info[], int len)
{
    int i = 0;
    printf("%1s %10s %10s %3s %3s %5s\n", "Sno", "Port", "RT Name", "Tx", "Rx", "Type"); 
    for(i=0;i<len;i++)
        printf("%3d %10s %10s %3s %3s %5s\n", rt_info[i].sno, rt_info[i].front_port_range, rt_info[i].rt_name, rt_info[i].tx_dir, rt_info[i].rx_dir, rt_info[i].ptype);
}   


int main(void)
{
    printf("size of bcm_usd_retimer_info_t  %d and stockholm_rt_info %d\n", sizeof(stockholm_rt_info), sizeof(struct bcm_usd_retimer_info_t));
    bcm_usd_display_rt_info(stockholm_rt_info, sizeof(stockholm_rt_info)/sizeof(struct bcm_usd_retimer_info_t));
}
