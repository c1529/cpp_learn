#include <49func.h>
int main(int argc, char *argv[])
{
    // ./0_gethostbyname www.baidu.com
    ARGS_CHECK(argc,2);
    // host+ent  host:主机   ent:entry,信息项
    struct hostent *phost=gethostbyname(argv[1]);
    if(phost==NULL){
        herror("gethostbyname");
        return -1;
    }
    printf("official name =%s\n",phost->h_name);
    printf("h_aliases:\n");
    for(int i=0;phost->h_aliases[i]!=NULL;i++){
        printf("%d : %s\n",i,phost->h_aliases[i]);
    }
    printf("ip 类型:%d\n",phost->h_addrtype);
    printf("ip 长度:%d\n",phost->h_length);
    printf("h_addr_list:\n");
    for(int i=0;phost->h_addr_list[i]!=NULL;i++){
        //printf("%d : %s\n",i,inet_ntoa(*(struct in_addr*)phost->h_addr_list[i]));
        char buf[1024]={0};
        inet_ntop(phost->h_addrtype,phost->h_addr_list[i],buf,1024);
        printf("ip = %s\n",buf);
    }
    return 0;
}
