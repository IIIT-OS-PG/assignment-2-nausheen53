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
#include<unistd.h>
#include<pthread.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include <openssl/sha.h>
#include<string>
using namespace std;
int last_val;
struct ser_add
{
   const char* ipa;
    int porta;
};

struct create_user
      {
        string uid;
        string passwd;  
      };

char** split_by_slash(char s[])
{
  char** ctr1 = new char*[20];

  char* temp=strtok(s, " ");
  int m=0;
  while(temp!=NULL)
  {
    //cout<<temp<<endl;
    ctr1[m] = temp;
    //cout<<ctr1[m]<<endl;
    //i++;
    m++;
    temp=strtok(NULL,"/");
  }
  ctr1[m] = NULL;
  last_val=m-1;
  return ctr1;
}

char** splits(char s[])
{ cout<<"inside input splits"<<endl;
  char** ctr1 = new char*[20];

  char* temp=strtok(s, " ");
  int m=0;
  while(temp!=NULL)
  {
    //cout<<temp<<endl;
    ctr1[m] = temp;
    //cout<<ctr1[m]<<endl;
    //i++;
    m++;
    temp=strtok(NULL," ");
  }
  ctr1[m] = NULL;
  return ctr1;
}

void *connection_handler(void *cli)
{
    cout<<"inside handler"<<endl;
    int sock = *(int*)cli;
    int read_size;
    char *message , client_message[2000];
     int k=1;

     const char* argv="/home/nausheen/Documents/new_k";
     //string s = /home/nausheen/Documents/new_k;
    FILE* fp = fopen(argv,"wb");
    k++;
    char buff[512];
    int file_size;
    int n;
    recv(sock,&file_size,sizeof(file_size),0);
    printf("%d",file_size);
    while((n=recv(sock,buff,512,0))>0 && file_size>0)
    {
        fwrite(buff,sizeof(char),n,fp);
        memset(buff,'\0',512);
        file_size=file_size-n;
    } 
      fclose(fp);  
      //return 0;
 }

void *myclient(void* arg)
{
	int client_sockfd;
	cout<<"hey!,client here sending some file"<<endl;
  
	if((client_sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		 printf(" Socket creation error"); 
        	exit(EXIT_FAILURE); 
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( 8802);
  serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

if(connect ( client_sockfd  , (struct sockaddr*)&serv_addr  , sizeof(serv_addr) )<0)
{
	perror("failed");
}



while(1)
  { cout<<"inside while"<<endl;
    string s;
    getline(cin,s);
    //scout<<s<<endl;
    int flag;
    char cstr[s.size() + 1];
    strcpy(cstr,s.c_str());
    char** input_split = new char*[100];
    input_split= splits(cstr);
    char* uid;
    vector<string>hash;
    char* x = new char[512];
    int x1;
    if(strcmp(input_split[0],"create_user")==0)
    {
      

      struct create_user ct;
      ct.uid = input_split[1];
      ct.uid = input_split[2];
      int n;
      int flag=0;
      //uid=input_split[1];
      cout<<"input split 0 "<<input_split[0]<<endl;
      cout<<"input split 1 "<<input_split[1]<<endl;
      cout<<"input split 2 "<<input_split[2]<<endl;
      // cout<<"---"<<string(input_split[0]).size();
      
     n= send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
      cout<<"n 1 "<<n<<endl;
      recv(client_sockfd,x,512,0);
      cout<<endl;
      memset(x,'\0',512);
    n= send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
       recv(client_sockfd,x,512,0);
       cout<<endl;
       cout<<"n 2 "<<n<<endl;
       memset(x,'\0',512);
     n= send(client_sockfd,input_split[2],sizeof(string(input_split[2])),0);
       //recv(client_sockfd,x,512,0);
       cout<<endl;
       cout<<"n 3 "<<n<<endl;
       memset(x,'\0',512);
    }
    if(strcmp(input_split[0],"login")==0)
    {
     
       //int x1;
      int n;
      int valread2;
      uid = input_split[1];
      n= send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
      cout<<"n 1 "<<n<<endl;
      recv(client_sockfd,x,512,0);
      cout<<endl;

      memset(x,'\0',512);
      send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
      cout<<"n 2 "<<n<<endl;
      recv(client_sockfd,x,512,0);
      cout<<endl;
      memset(x,'\0',512);
      send(client_sockfd,input_split[2],sizeof(string(input_split[2])),0);
      cout<<"n 3 "<<n<<endl;
      //read(client_sockfd,x,512);
      //cout<<endl;
      //cout<<"x"<<
      //memset(x,'\0',512);
      
          flag =1;
      

    }
   // if(flag ==1)
    //{
      if(strcmp(input_split[0],"create_group")==0)
        { 
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
        }
        if(strcmp(input_split[0],"join_group")==0)
        {
          int ip_of_client = x1;
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          recv(client_sockfd,&x1,sizeof(x1),0);
          cout<<"port"<<x1<<endl;
         
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          memset(x,'\0',512);
          recv(client_sockfd,x,512,0);
          cout<<"ip "<<x<<endl;
          char* port_of_client = x;
          memset(x,'\0',512);
        }
        if(strcmp(input_split[0],"leave_group")==0)
        {
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
           recv(client_sockfd,x,512,0);
           memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
           recv(client_sockfd,x,512,0);
           memset(x,'\0',512);
           send(client_sockfd,"ok",sizeof("ok"),0);
          //recv(client_sockfd,x,512,0);
          cout<<x<<endl;
          memset(x,'\0',512);

        }
        if(strcmp(input_split[0],"list_request")==0)
        {
          int size;
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          recv(client_sockfd,&size,sizeof(size),0);
          cout<<x<<endl;
          send(client_sockfd,"ok",sizeof("ok"),0);
          for(int i=0;i<size;i++)
          {
            char* abcd1 =new char[512];
            memset(abcd1,'\0',512);
            recv(client_sockfd,abcd1,512,0);
            cout<<endl;
            cout<<"list request "<<abcd1 <<endl;
            send(client_sockfd,"ok",sizeof("ok"),0);

          }
          memset(x,'\0',512);
         // send(client_sockfd,"ok",sizeof("ok"),0);
          

        }
        if(strcmp(input_split[0],"accept_request")==0)
        {
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          recv(client_sockfd,x,512,0);
          cout<<x<<endl;
          memset(x,'\0',512);
        }
        if(strcmp(input_split[0],"list_groups")==0)
        {
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          recv(client_sockfd,x,512,0);
          cout<<x<<endl;
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          int size;
          recv(client_sockfd,&size,sizeof(size),0);
          send(client_sockfd,"ok",sizeof("ok"),0);
          for(int i=0;i<size;i++)
          {
            int x=0;
            char* buff1 = new char[512];
            char* buffer4 = new char[512];
            memset(buff1,'\0',512);
            memset(buffer4,'\0',512);
            recv(client_sockfd,buff1,512,0);
            cout<<endl;
            cout<<"group id is "<<buff1<<endl;
            send(client_sockfd,&x,sizeof(x),0);
            recv(client_sockfd,buffer4,512,0);
            cout<<endl;
            cout<<"owner is "<<buffer4<<endl;
          }
          cout<<x<<endl;
          memset(x,'\0',512);
        }
        if(strcmp(input_split[0],"list_files")==0)
        {
          int sz=0;
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          recv(client_sockfd,&sz,sizeof(sz),0);
          send(client_sockfd,"ok",sizeof("ok"),0);
          cout<<x<<endl;
          for(int i=0;i<sz;i++)
          {
            char* buffer4 = new char[512];
            memset(buffer4,'\0',512);
            recv(client_sockfd,buffer4,512,0);
            cout<<endl;
            cout<<"files"<<buffer4<<endl;
            send(client_sockfd,"ok",sizeof("ok"),0);
          }
          memset(x,'\0',512);
        }
        if(strcmp(input_split[0],"upload")==0)
        {
          struct upload_file
          {
            char* filepath;
            string gid;
          };
          
          upload_file uf;
          uf.filepath=input_split[1];
          uf.gid=input_split[2];
          char** file_split = new char*[100];
          file_split= split_by_slash(input_split[1]);
          //##################################################################
          FILE *fp;
  if ( !(fp = fopen ( "/home/nausheen/swansong.mp3" , "rb" )))
    {
        perror("sorry");
        //return ;
    }
     fseek ( fp , 0 ,SEEK_END);
    int size = ftell ( fp );
    cout<<"size "<<size<<endl;
    rewind ( fp );
     char buff[512*1024];
    int n;
    

     while((n=fread(buff,sizeof(char),512*1024,fp))>0 && size>0)
    {  
      unsigned char digest[SHA_DIGEST_LENGTH];
      char mdString[SHA_DIGEST_LENGTH*2];
      memset(digest,0x0,SHA_DIGEST_LENGTH);
      SHA1((unsigned char*)buff, strlen(buff),digest);  
      int i;  
      for( i = 0; i < SHA_DIGEST_LENGTH; i++)
      {
        sprintf((char*)&mdString[i*2], "%02x",digest[i]);
      }
      string something(mdString);
      string some=something.substr(0,20);
      hash.push_back(some);
      cout<<something<<endl;
      mdString[i]='\0';
      memset(buff,'\0',512*1024);
      size = size -n;
     }
     //####################################################
     vector<string> :: iterator itr;
     itr=hash.begin();
     char buff1[21];
     char mdString1[SHA_DIGEST_LENGTH*2];
     while(itr!=hash.end())
     {
      strcpy(buff1,(*itr).c_str());
      unsigned char digest[SHA_DIGEST_LENGTH];
      memset(digest,0x0,SHA_DIGEST_LENGTH);
      SHA1((unsigned char*)buff1, strlen(buff),digest);  
      int i;  
      for( i = 0; i < SHA_DIGEST_LENGTH; i++)
      {
        sprintf((char*)&mdString1[i*2], "%02x",digest[i]);
      }
      mdString1[i]='\0';
      memset(buff,'\0',21);
      itr++;
     }
     string something1(mdString1);

    // cout<<endl;
     //################################################
    // cout<<endl;
    fclose(fp);
          //##################################################################
          //split_by_slash(input_split[1]);
          send(client_sockfd,input_split[0],sizeof(string(input_split[0])),0); //upload
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof(string(input_split[1])),0); //filepath
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[2],sizeof(string(input_split[2])),0); //groupid
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,file_split[last_val],sizeof(string(file_split[last_val])),0); //filename
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,&size,sizeof((size)),0); //filesize
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          int nn = hash.size();
          send(client_sockfd,&nn,sizeof((nn)),0);
          recv(client_sockfd,x,512,0);
         // send(client_sockfd,hash,sizeof((hash)),0); //hash
          for(int j=0;j<hash.size();j++)
          {
            string s= hash[j];
            char c[s.size() +1];
            strcpy(c,s.c_str());
            cout<<"owvo "<<c<<endl;
            send(client_sockfd,c,sizeof(21),0);//hash send krra
            recv(client_sockfd,&x,sizeof(x),0);
            memset(x,'\0',512);
          }
          send(client_sockfd,&something1,sizeof(something1),0);
        }

        if(strcmp(input_split[0],"download_files")==0)
        {
          struct download
          {     
                string gid;
                string filename;
                char* destpath;
          };
    
          download dwld;
          dwld.gid = input_split[1];
          dwld.filename = input_split[2];
          dwld.destpath=input_split[3];
    
          send(client_sockfd,input_split[0],sizeof((input_split[0])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[1],sizeof((input_split[1])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[2],sizeof((input_split[2])),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,input_split[3],sizeof((input_split[3])),0);
        }
    
        if(strcmp(input_split[0],"logout")==0)
        {
         send(client_sockfd,input_split[0],sizeof((input_split[0])),0);
         recv(client_sockfd,x,512,0);
         memset(x,'\0',512);
         send(client_sockfd,"ok",sizeof("ok"),0);
          recv(client_sockfd,x,512,0);
          memset(x,'\0',512);
          send(client_sockfd,"ok",sizeof("ok"),0);
          char* buffer111 = new char[512];
         recv(client_sockfd,buffer111,512,0) ;
         if(strcmp(buffer111,"logged out!!")==0)
          flag =0;
        }
    
        if(strcmp(input_split[0],"show_downloads")==0)
        {
    
        }
    
        if(strcmp(input_split[0],"stop_share")==0)
        {
    
        }
      }
  


 //  FILE *fp = fopen ( "/home/nausheen/heart.jpg" , "rb" );
	// fseek ( fp , 0 , SEEK_END);
 //  	int size = ftell ( fp );
 //  	rewind ( fp );
 //  	int file_size;
 //  	send(client_sockfd,&size,sizeof(file_size),0);
 //  	char buff[512];
 //  	int n;
 //  	while((n=fread(buff,sizeof(char),512,fp))>0 && size>0)
 //  	{
 //  		send(client_sockfd,buff,n,0);
 //  		memset(buff,'\0',512);
 //  		size = size -n;
 //  	}

 //  	fclose(fp);
	close(client_sockfd);

}


void* myserver(void* arg)
{
	int serv_sockfd=socket(AF_INET,SOCK_STREAM,0);
    int c;
    //cout<<"inside server prog"<<endl;
    if(serv_sockfd==0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    ser_add* sra = (ser_add*)arg;
    int port111=sra->porta;
    const char* ip111=sra->ipa;

    struct sockaddr_in sock_address;
    sock_address.sin_family = AF_INET; 
    sock_address.sin_addr.s_addr = inet_addr(ip111); 
    sock_address.sin_port = htons(port111);
    // sock_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    //  sock_address.sin_port = htons(8084);
    int addrlen = sizeof(sock_address);
    cout<<"after structure definition"<<endl;
    if(bind(serv_sockfd,(struct sockaddr*)&sock_address,sizeof(sock_address))<0)
    {

        perror("bind failed"); 
        //exit(EXIT_FAILURE); 
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

    int client_sock;
    int i=4;
    while(i--)
    {
        cout<<i<<endl;
        client_sock = accept(serv_sockfd, (struct sockaddr*)&sock_address,(socklen_t*)&addrlen) ;
        printf("\nConnection accepted\n");
            if (client_sock < 0)
            {
                perror("accept failed");
                //return 1;
            }
            cout<<"server here,accepting some file,at peer"<<endl;
        if( pthread_create( &thread_id[i] , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            //return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        
        puts("Handler assigned");
    }
     int j=4;
     while(j--)
     {  cout<<"j"<<j<<endl;
        pthread_join( thread_id[j] , NULL);
     }
 
    
/*
 * This will handle connection for each client
 * */

  close(client_sock);
  close(serv_sockfd);
   
}


int main(int argc,char const *argv[])
{
	 pthread_t thread_id[2];
	 cout<<"inside main of peer"<<endl;
   ser_add* sr;
   sr=(ser_add*)malloc(sizeof(struct ser_add));
   // char* ip_address1 =inet_ntoa(argv[1]);
   // int port_addr1=ntohs(argv[2]);
 const  char* ip_address1 =(argv[1]);

    int port_addr1=atoi(argv[2]);
   sr->ipa = ip_address1;
   sr->porta = port_addr1;
	 pthread_create( &thread_id[0] , NULL ,  myclient , NULL);
	 pthread_create( &thread_id[1] , NULL ,  myserver , (void*)sr);

	 int j=2;
     while(j--)
     {  //cout<<"j"<<j<<endl;
        pthread_join( thread_id[j] , NULL);
     }
 	return 0;
}