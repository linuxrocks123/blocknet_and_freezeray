#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>

#include <netinet/in.h>
#include <dlfcn.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
     int (*real_connect)(int _sockfd,const struct sockaddr* _addr,socklen_t _addrlen) = dlsym(((void *) -1l),"connect");
     switch(addr->sa_family)
     {
     case AF_INET6:
          errno = EACCES; //we don't support this yet
          return -1;

     case AF_INET: ;
          char buf[16];
          struct sockaddr_in* saddr = (struct sockaddr_in*)(addr);
          inet_ntop(AF_INET,&(saddr->sin_addr),buf,16);
          if(!strcmp("127.0.0.1",buf))
          {
               return real_connect(sockfd,addr,addrlen);
          }
          else
          {
               errno = EACCES;
               return -1;
          }
     default:
          return real_connect(sockfd,addr,addrlen);
     }

     return -1;
}
