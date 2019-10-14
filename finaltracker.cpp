#include<unistd.h>
#include<stdio.h>
#include <netinet/in.h> 
#include <string.h> 
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<pthread.h>
#include<unordered_map>
#include<vector>
#include<algorithm>

//#include<dir.h>
using namespace std;
struct info
{
    char* ip4;
    int port_;
    int fd1;    
};

     struct group_info
    {
        char* owner;
        char* gid;
        vector<char*>files;
        vector<char*>uids;
    };
int flag =0;
struct uploadfile
{
    vector<string>sha;
    int filesize;
    vector<char*>user_idss;
    char* filepath;
    char* filename;
};
void *connection_handler(void *cli)
{   int p=0;
         char* buffer = new char[512];
         char* buffer1 = new char[512];
         char* buffer2 = new char[512];
         char* buffer3 = new char[512];
         char* buffer4 = new char[512];
         char* buffer5 = new char[512];
         char* buffer6 = new char[512];
         char* user_id = new char[512];
         char* ipv4_of_uid = new char[512];
        int valread,valread1,valread2,valread3,valread4,valread5,valread6;
        int port_of_uid ;
         unordered_map<char*,char*>listgroup;   //group name and owner name
         info *if2=(info*)cli;
        int sock = if2->fd1;
        char* ipv4_1 = if2->ip4;
        int port1 = if2->port_;
        unordered_map<char*,pair<char*,pair<char*,int> > >user_details;
        unordered_map<char*,pair<char*,pair<char*,int> > > :: iterator itr;
        unordered_map<string,struct uploadfile>upload_files;
        unordered_map<string,struct uploadfile> :: iterator it_up;
         unordered_map<char*,group_info>group_n_all;
        unordered_map<char*,group_info> :: iterator it;
        it = group_n_all.begin();
        vector<char*>list_requests;
    while(1)
    {
        cout<<"inside while "<<endl;
        ++p;
        cout<<"insidewhile ka p"<<p<<endl;
        int x;
         
            memset(buffer,'\0',512);
           memset(buffer1,'\0',512);
           memset(buffer2,'\0',512);
           memset(buffer3,'\0',512);
           memset(buffer4,'\0',512);
           memset(buffer5,'\0',512);
           memset(buffer6,'\0',512);
        valread=recv(sock,buffer,512,0);
        send(sock,"ok",sizeof("ok"),0);
        valread1=recv(sock,buffer1,512,0);
        send(sock,"ok",sizeof("ok"),0);
        valread2=recv(sock,buffer2,512,0);
        //send(sock,"ok",sizeof("ok"),0);
        cout<<"read val from user :"<<buffer<<endl;
        cout<<"read val from user :"<<buffer1<<endl;
        cout<<"read val from user :"<<buffer2<<endl;
       
        if(strcmp(buffer,"create_user")==0)
        {   cout<<"inside if"<<endl;
            user_details.insert(make_pair(buffer1,make_pair(buffer2,make_pair(ipv4_1,port1))));
            for(auto i = user_details.begin();i != user_details.end();i++)
            {
                cout<<"itr 1 "<<i->first<<endl;
                //cout<<"itr 1 "<<i->second<<endl;
            }
           // int x= send(sock,"ok",sizeof("ok"),0);
           // cout<<x<<endl;
        }
        if(strcmp(buffer,"login")==0)
        {
            const char* msg = "sorry,not a registered user";
            //for (auto i = create_user.begin(); i != create_user.end(); i++) 
             //cout << i->first << "  " << i->second<< endl;
            if(user_details.find(buffer1)==user_details.end())
            {
                send(sock,msg,sizeof(msg),0);
            }
            else 
            {
                flag =1;
                user_id=buffer1;
                ipv4_of_uid = if2->ip4;
                port_of_uid = if2->port_;
            }
    
        }
    
       
        
        if(flag ==1)
        {
            if(strcmp(buffer,"create_group")==0)
            {
                group_info gi;
                gi.owner = user_id;
                gi.gid = buffer1;
                gi.files.push_back(0);
                gi.uids.push_back(user_id);
                group_n_all.insert(make_pair(buffer1,gi));
                listgroup.insert(make_pair(buffer1,user_id));
                //listgroups.push_back(buffer1);
            }
    
            if(strcmp(buffer,"leave_group")==0)
            {
                it = group_n_all.find(buffer1);
                if(it!=group_n_all.end())
                {   
                    group_info gi1;
                    gi1 = it->second;
                    gi1.uids.erase(remove(gi1.uids.begin(), gi1.uids.end(),user_id), gi1.uids.end());
                }
            }
    
            if(strcmp(buffer,"join_group")==0)
            {
                it = group_n_all.find(buffer1);
                if(it != group_n_all.end())
                {
                    group_info gin;
                    gin = it->second;
                    char* owner_id = gin.owner;
                    itr = user_details.find(owner_id);
                    if(itr!=user_details.end())
                    {
                        pair<char*,int>socketa;
                        socketa=itr->second.second;
                        int port_11=socketa.second;
                        char* i_11=new char[512];
                        i_11=socketa.first;
                        send(sock,&port_11,sizeof(port_11),0);
                        recv(sock,&x,sizeof(x),0);
                        send(sock,i_11,sizeof(i_11),0);

                        char* user_req=new char[512];
                        user_req=user_id;
                        list_requests.push_back(user_req);
                        //client request accept karke group info update karne aayega.
                    }
                }
                else
                { 
                   const char* msg1 =new char[512];
                    msg1= "no such group exists";
                    send(sock,msg1,sizeof(msg1),0);

                }
            }
    
            if(strcmp(buffer,"list_groups")==0)
            {
                for (auto i = listgroup.begin(); i != listgroup.end(); i++) 
                    
                   { 
                        send(sock,i->first,sizeof(i->first),0);
                        recv(sock,&x,sizeof(x),0);
                        send(sock,i->second,sizeof(i->second),0);
                    }
            }
    
            if(strcmp(buffer,"list_files")==0)
            {
                it = group_n_all.find(buffer1);
                if(it != group_n_all.end())
                {
                    group_info gii;
                    gii = it->second;
                    vector<char*>v;
                    v= gii.files;
                    for(auto i =v.begin(); i != v.end();i++)
                    {
                        char* filen=new char[1024];
                        filen = *i;
                        send(sock,filen,sizeof(filen),0);
    
                    }
    
                }
            }
    
            if(strcmp(buffer,"list_requests")==0)
            {    
                char* abcd = new char[512];
                for(auto i = list_requests.begin();i != list_requests.end();i++ )
                {
                   
                    abcd = *i;
                    send(sock,abcd,sizeof(abcd),0);
                    recv(sock,&x,sizeof(x),0);
                }
            }
    
            if(strcmp(buffer,"accept_request")==0)
            {
                it = group_n_all.find(buffer1);
                if(it != group_n_all.end())
                {
                    group_info gin;
                    gin = it->second;
                    gin.uids.push_back(buffer2);
                    // list_requests se pop bhi karwao
                    
                }
                else
                { 
                   const char* msg1 =new char[512];
                    msg1= "no such group exists";
                    send(sock,msg1,sizeof(msg1),0);
                }
            }
    
            if(strcmp(buffer,"logout")==0)
            {
                flag =0;
                const char* msg = new char[512];
                msg="logged out!!";
                send(sock,msg,sizeof(msg),0);
            }
    
           if(strcmp(buffer,"upload")==0)
           {
                valread3 =recv(sock,buffer3,512,0);//filename
                send(sock,"ok",sizeof("ok"),0);
                valread4=recv(sock,buffer4,512,0);//filesize
                send(sock,"ok",sizeof("ok"),0);
                valread5=recv(sock,buffer5,512,0);//hash
                send(sock,"ok",sizeof("ok"),0);
                uploadfile uff;
                uff.sha.push_back(buffer5);
                uff.filesize=atoi(buffer4);
                uff.user_idss.push_back(user_id);
                uff.filepath=buffer1;
                uff.filename=buffer3;
                string hash = buffer6;
                //gid+filename
                string gid(buffer2);
                string flname(buffer3);
                string key = gid+flname;
                upload_files.insert(make_pair(key,uff));
    
           } 
    
        }
      }
}


    
int main()
{   

    int serv_sockfd=socket(AF_INET,SOCK_STREAM,0);
    int c;
    //cout<<"inside server prog"<<endl;
    if(serv_sockfd==0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    //ipv4 socket structure
    /*struct  in_addr
    {
        in_addr_t s_add; //ipv4 addr
    };*/    

    struct sockaddr_in sock_address;
    sock_address.sin_family = AF_INET; 
    sock_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    sock_address.sin_port = htons(8096);
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
     int abcd=addrlen;
     struct sockaddr_in sock_address_1;
      //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id[4];

    int client_sock;
    int i=50;
    while(i--)
    {
        cout<<i<<endl;
       

        client_sock = accept(serv_sockfd, (struct sockaddr*)&sock_address_1,(socklen_t*)&abcd) ;
        printf("\nConnection accepted\n");
            if (client_sock < 0)
            {
                perror("accept failed");
                return 1;
            }
            info *ifo ;
            ifo=(info*)malloc(sizeof(struct info));
            //ifo.ip4
            char* x=inet_ntoa(sock_address_1.sin_addr);
            int port11=ntohs(sock_address_1.sin_port);
            int fd11=client_sock;
         //   cout<<"ip bc "<<x<<endl;
           // cout<<"port bc "<<port11<<endl;
            //cout<<"fd bc "<<fd11<<endl;
            ifo->ip4=x;
          // cout<<"blah "<<ifo->ip4<<endl;
            ifo->port_=port11;
           // cout<<ifo->port_<<"port hai bhai\n";
            ifo->fd1=fd11;
            cout<<"socket"<<ifo->fd1<<endl;

        if( pthread_create( &thread_id[i] , NULL ,  connection_handler , (void*) ifo) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        
        puts("Handler assigned");
    }
     int j=50;
     while(j--)
     {  cout<<"j"<<j<<endl;
        pthread_join( thread_id[j] , NULL);
     }
 
    
/*
 * This will handle connection for each client
 * */

  close(client_sock);
    close(serv_sockfd);
   
     
     return 0; 
}
