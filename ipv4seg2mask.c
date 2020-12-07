#include <stdio.h>
#include <math.h>

unsigned int ip2long(const char*ip_str)
{
    unsigned char x1=0,x2=0,x3=0,x4=0;
    sscanf(ip_str,"%hhu.%hhu.%hhu.%hhu",&x1,&x2,&x3,&x4);
    unsigned int  result  = x1*65536*256+x2*65536+x3*256+x4;
    //printf("%d,%d,%d,%d\n",x1,x2,x3,x4);
    return result;
}
void seg2mask(unsigned int start,unsigned int end)
{
    unsigned int seg = end-start+1;
    if(seg==1)
    {
        printf("%hhu.%hhu.%hhu/%hhu\n",start/65536,start%65536/256,start%256,32);
        return ;
    }
    int  mask = log(seg)/log(2);
    int mask_start = (start>>mask)<<mask;
    int used =  pow(2,mask)-1;
    int i;
    for(i=mask_start;i<=end;i+=used+1)
    {
        //printf("s-%d e-%d i-%d m-%d seg %d\n",start%256,end%256,i%256,mask,seg);
        if(i>=start&&i+used<=end)
        {
            printf("%d.%d.%d.%d/%d\n",i/(65536*256),i%(65536*256)/65536,i%65536/256,i%256,32-mask);
        }
        else if(i<start)
        {
            seg2mask(start,i+used);
        }
        else if(i+used+1>end)
        {
            seg2mask(i,end);
        }
        else 
        {
            printf("error \n");
        } 
    }
    /*
    printf("m-%lu\n",32-mask);
    printf("%d.%d.%d/%d\n",start/65536,start%65536/256,start%256,32-mask);
    */
   // if(seg-used>0)seg2mask(start+used,end);    
}
//36.128.0.0	36.192.107.255
int main(int argc,char**argv)
{
    char* ip_str_start = "36.128.10.0";
    char* ip_str_end   = "36.128.10.255";
//    if(argc!=3)
//    {
//        printf("useage:%s startip endip\n",argv[0]);
//        exit(0);
//    }
//    char* ip_str_start = argv[1];
//    char* ip_str_end   = argv[2];
    unsigned int start = ip2long(ip_str_start);
    unsigned int end   = ip2long(ip_str_end);
    seg2mask(start,end);
    //printf("x-%u %u\n",start,end);
    
}
