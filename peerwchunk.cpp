#include<stdio.h>
#include <netinet/in.h> 
#include <string.h> 
#include <stdlib.h>
#include<sys/socket.h>
#include <netdb.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unordered_map>
#include<string>
#include<pthread.h>
#include<unistd.h>
#include<iostream>
#define chunk 512*1024
using namespace std;
    struct fdnfile
    {
        int client_sock_fd;
        FILE* fp1;
        int k;
    };
void *connection_handler(void *stru)
{   
    fdnfile ff1 = *(fdnfile*)stru;
    cout<<"inside handler"<<endl;
    int sock = ff1.client_sock_fd;
    cout<<"socket fd recieved"<<sock<<endl;
    FILE* fp2 = ff1.fp1;
    int t=ff1.k;
    char buff[chunk];
    int file_size;
    int n;
    fseek ( fp2 , t*chunk , SEEK_SET);
    recv(sock,&file_size,sizeof(file_size),0);
    //printf("%d",file_size);
    int abc=0;
    while((n=recv(sock,buff,chunk,0))>0 && file_size>0 && abc <((t+1)*512*1024))
    {
        fwrite(buff,sizeof(char),n,fp2);
        memset(buff,'\0',chunk);
        file_size=file_size-n;
         abc=abc+n;
    }

    close(sock);
    //close(serv_sockfd);
    fclose(fp2);
 }

void *myclient(void* arg)
{   
    int a;
    cin>>a;
    cout<<"hey client here at peer1 sending you some file"<<endl;
	int client_sockfd;
	if((client_sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		 printf(" Socket creation error"); 
        	exit(EXIT_FAILURE); 
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( 8085 );
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

if(connect ( client_sockfd  , (struct sockaddr*)&serv_addr  , sizeof(serv_addr) )<0)
{
	perror("failed");
}
cout<<"client here,sending you file"<<endl;
//kaam kaaj
FILE *fp = fopen ( "/home/nausheen/abcd.png" , "rb" );

    fseek ( fp , 0 , SEEK_END);
    int size = ftell ( fp );
    rewind ( fp );
    int file_size;
    send(client_sockfd,&size,sizeof(file_size),0);
    char buff[512];
    int n;
    while((n=fread(buff,sizeof(char),512,fp))>0 && size>0)
    {
        send(client_sockfd,buff,n,0);
        memset(buff,'\0',512);
        size = size -n;
    }

    fclose(fp);
    close(client_sockfd);

}


void* myserver(void* arg)
{   
    cout<<"hey server here at peer1 accepting some files"<<endl;
	int serv_sockfd=socket(AF_INET,SOCK_STREAM,0);
    int c;
    //cout<<"inside server prog"<<endl;
    if(serv_sockfd==0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sock_address;
    sock_address.sin_family = AF_INET; 
    sock_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    sock_address.sin_port = htons(8087);
    int addrlen = sizeof(sock_address);
    cout<<"after structure definition"<<endl;
    if(bind(serv_sockfd,(struct sockaddr*)&sock_address,sizeof(sock_address))<0)
    {

        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    }

    if (listen(serv_sockfd, 3) < 0) 
    { 
        perror("listen failed"); 
        exit(EXIT_FAILURE); 
    } 

      //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id[4];
            FILE* fp[3];
            // int file_size;
            // int n;
            // char buff[512];
            // n=recv(cliernt_sock,&file_size,sizeof(file_size),0);
            for(int i=0;i<3;i++)
            {
                fp[i]= fopen("/home/nausheen/Desktop/newfile","w+t");
            }

    int client_sock;
    int i=0;
    while(i<3)
    {
        //cout<<i<<endl;i
        
        client_sock = accept(serv_sockfd, (struct sockaddr*)&sock_address,(socklen_t*)&addrlen) ;
        printf("\nConnection accepted\n");
            if (client_sock < 0)
            {
                perror("accept failed");
                //return 1;
            }
            fdnfile ff;
            ff.client_sock_fd =client_sock;
            cout<<"client fd sent "<<client_sock<<endl;
            ff.fp1 = fp[i];
            ff.k=i;
            i++;
        if( pthread_create( &thread_id[i] , NULL ,  connection_handler , (void*) &ff) < 0)
        {
            perror("could not create thread");
            //return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        
        puts("Handler assigned");
    }
     int j=4;
     while(j--)
     {  //cout<<"j"<<j<<endl;
        pthread_join( thread_id[j] , NULL);
     }
 
    
/*
 * This will handle connection for each client
 * */

  close(client_sock);
    close(serv_sockfd);
   
}

int main()
{
	 pthread_t thread_id[2];
     cout<<"inside main of peer1"<<endl;
	 pthread_create( &thread_id[0] , NULL ,  myclient , NULL);
	 pthread_create( &thread_id[1] , NULL ,  myserver , NULL);

     int j=2;
     while(j--)
     {  //cout<<"j"<<j<<endl;
        pthread_join( thread_id[j] , NULL);
     }

     return 0;
}