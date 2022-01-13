#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>

int main(void)
{
    int fd;
    int len,len2;
    int guck;

    struct sockaddr_in sa;
    struct hostent *he;

    fd = socket(PF_INET, SOCK_STREAM, getprotobyname("TCP")->p_proto);
    
    sa.sin_family = AF_INET;
    sa.sin_port = htons(22);
    
    he = gethostbyname("antares.math.rwth-aachen.de");

    memcpy(&(sa.sin_addr.s_addr),he->h_addr_list[0],he->h_length);

    len = he->h_length;

    len2 = sizeof(struct sockaddr_in);

    guck = connect(fd, (struct sockaddr *)(&sa), len2);

    printf("%d %d %d %d %d\n",fd, len, guck, len2, errno);
    return 0;
}