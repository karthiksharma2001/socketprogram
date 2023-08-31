#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string.h>
#include <netdb.h>
#include <string.h>

#define PORT 8080
using namespace std;

int main()
{


	int serverfd=socket(AF_INET,SOCK_STREAM,0),sockfd;
	struct sockaddr_in address;
        socklen_t address_length=sizeof(address);

	char arr[1024]={0};
	address.sin_family=AF_INET;
	address.sin_port=htons(PORT);
	address.sin_addr.s_addr=INADDR_ANY;

	if(serverfd<0)
	{
		perror("socket is faile");
                exit(-1);
	}
        
	if(bind(serverfd,(struct sockaddr *) &address,sizeof(address))<0){
                 perror("bind is failed");
                exit(-1);


	}


       if(listen(serverfd,1)<0)
       {
           perror("listen");
                exit(-1);       
       }


      if(sockfd=accept(serverfd,(struct sockaddr *) &address,&address_length)<0)
		      {

		       perror("accept");
                        exit(-1);

			}


      while(true)
      {

         int valread=read(sockfd,arr,1024);
          arr[valread] = '\0';

	   if(strncmp(arr,"exit",5)==0)
	   {
	      close(sockfd);
	      close(serverfd);
	      exit(0);


	   }   

   	 cout << arr << endl;  
        write(sockfd,arr,sizeof(arr));

      }


return 0;

}

























