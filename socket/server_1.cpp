#include<iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
using namespace std;
int main()
{
int serverfd=socket(AF_INET,SOCK_STREAM,0),newsocket;
struct sockaddr_in address;
//The above structure helps us to reference the socket elements as
/* struct sockaddr_in {
short int sin_family;It represents an address family.
unsigned short int sin_port;A 16-bit(2 bytes) port number in
Network byte order.

struct in_addr sin_addr;A 32-bit(4 bytes) IP address in
Network byte order.
unsigned char sin_zero[8];
}; This structure is used to hold the information about
address,port etc*/

char buffer[1024]={ 0 };
address.sin_family = AF_INET;//address family internet
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
socklen_t address_length=sizeof(address);
if(serverfd<0)
{
perror("socket failed");
exit(EXIT_FAILURE);
}
if (bind(serverfd, (struct sockaddr*)&address,sizeof(address))
< 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(serverfd, 1) < 0) {
perror("listen");
exit(EXIT_FAILURE);
}
if ((newsocket
= accept(serverfd, (struct sockaddr*)&address, &address_length))

< 0) {
perror("accept");
exit(EXIT_FAILURE);
}

while(true)
{
read(newsocket, buffer, 1024);
if(strncmp(buffer, "exit", 5)==0){

close(newsocket);
close(serverfd);
exit(0);
}
cout << "client: " << buffer << endl;
write(newsocket, buffer, strlen(buffer));
}
return 0;
}