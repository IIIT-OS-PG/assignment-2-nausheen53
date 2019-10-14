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
#include<string>
#include <openssl/sha.h>
//#include<dir.h>
using namespace std;

int main()
{
	FILE *fp;
  if ( !(fp = fopen ( "/home/nausheen/swansong.mp3" , "rb" )))
    {
        perror("sorry");
        return 1;
    }
     fseek ( fp , 0 ,SEEK_END);
  	int size = ftell ( fp );
    //cout<<"size "<<size<<endl;
  	rewind ( fp );
	   char buff[512*1024];
  	int n;
  	
  	vector<string>hash;
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
      cout<<some<<endl;
    	mdString[i]='\0';
    	memset(buff,'\0',512*1024);
  		size = size -n;
  	 }
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
      
      //string some=something.substr(0,20);
      //hash.push_back(some);
      
      mdString1[i]='\0';
      memset(buff,'\0',21);
      itr++;
     }
     string something1(mdString1);
cout<<"new   "<<something1<<endl;
    cout<<endl;
  	fclose(fp);
  	return 0;
}
