#include<unistd.h>
#include<stdio.h>
#include <netinet/in.h> 
#include <string.h> 
#include <stdlib.h>
#include<sys/socket.h>
#include <netdb.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define chunk 512*1024
int main()
{
	int client_sockfd;
	if((client_sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		 printf(" Socket creation error"); 
        	exit(EXIT_FAILURE); 
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( 8087 );
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

if(connect ( client_sockfd  , (struct sockaddr*)&serv_addr  , sizeof(serv_addr) )<0)
{
	perror("failed");
}

FILE *fp = fopen ( "/home/nausheen/Desktop/tsetfile11.txt" , "r+t" );

	  fseek ( fp , 0 , SEEK_END);
  	int size = ftell ( fp );
  	rewind ( fp );
  	int file_size;
  	send(client_sockfd,&size,sizeof(file_size),0);
  	char buff[512*1024];
  	int n;
    int abc =0;
  	while((n=fread(buff,sizeof(char),512*1024,fp))>0 && size>0 && abc <(512*1024))
  	{
  		send(client_sockfd,buff,n,0);
  		memset(buff,'\0',512*1024);
  		size = size -n;
      abc=abc+n;
  	}

  	fclose(fp);
  	close(client_sockfd);
}