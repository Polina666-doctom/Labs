#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int Socket(int domain, int type, int protocol)
{
int res = socket(domain,type,protocol);
if (res == -1)
{
perror("socket failed");
exit(EXIT_FAILURE);
}
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
int res = bind (sockfd,addr,addrlen);
if (res == -1)
{
perror("bind failed");
exit(EXIT_FAILURE);
}
}

int Listen (int sockfd, int backlog)
{
int res = listen (sockfd, backlog);
if (res == -1)
{
perror("Listen failed");
exit (EXIT_FAILURE);
}
}

int Accept (int sockfd, struct sockaddr *addr , socklen_t *addrlen)
{
int res = accept ( sockfd, addr , addrlen);
if (res == -1)
{
perror("Accept failed");
exit (EXIT_FAILURE);
}
}

int Execvp (const char *path , char *const argv[] )
{
int res = execvp(path, argv);
if (res ==-1)
{
perror ("Run failed");
exit(EXIT_FAILURE);
}
}

int main( )
{
int err_exec;
int server = Socket(AF_INET, SOCK_STREAM, 0);//Create Socket
struct sockaddr_in adr = {0};//ZADAEM ADRES PO IPv4
adr.sin_family = AF_INET;//Create adress family
adr.sin_port = htons(3334);
Bind (server, (struct sockaddr*) &adr, sizeof adr);//Bind Socket and adress
Listen(server, 5);//Stream network server and 5 accepted clients
socklen_t adrlen = sizeof adr; // Memory size adress
int fd = Accept(server, (struct sockaddr*) &adr, &adrlen);//Accepted client
ssize_t nread; //Create read variable
char *buf[256]; // Buffer

nread = read(fd, buf, 256);//Receive data
if (nread ==-1)
{
perror("Read failed");
exit(EXIT_FAILURE);
}
if (nread == 0)
{
printf("END OF FILE");
}
write(STDOUT_FILENO, buf, nread);
int fdout=open("dataread.sh",O_WRONLY|O_CREAT|O_TRUNC,00777);
//dup2(fdout, STDOUT_FILENO);
write(fdout,buf,256);close(fdout);
system("~/dataread.sh");



// close(listen);
//system("~/LR3")
return 0;
}