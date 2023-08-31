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
using namespace std;
#define PORT 8080
int main(int argc,char *argv[])
{
int sock = 0, valread, client_fd;
struct sockaddr_in serv_addr;
struct hostent * server;
char buffer[1024] = { 0 };
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0) {
cout<<"Socket creation error"<<endl;
return -1;
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
server=gethostbyname(argv[1]);
if(server==NULL)
{
cout<<"No Such Host"<<endl;
}
bcopy((char*) server->h_addr, (char *)
&serv_addr.sin_addr.s_addr, server->h_length);
client_fd = connect(sock, (struct sockaddr*)&serv_addr,

sizeof(serv_addr));

if (client_fd< 0) {
cout<<"Connection Failed "<<endl;

return -1;
}
while(true)
{
cout << "Enter the message: ";
fflush(stdin);
fgets(buffer,256,stdin);
write(sock, buffer, strlen(buffer));
if(strncmp(buffer,"exit",4)==0)
{
close(sock);
exit(0);
}

read(sock, buffer, 1024);
cout << "Recieved from the server :" << buffer << endl;
}


}