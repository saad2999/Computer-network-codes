// Server side implementation of TCP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8084
#define MAXLINE 1024 

int sockfd;
struct info
{
	char* ip;
	int port;
	int newfd;
};
int compare(char a[], char b[])
{
   int c = 0;
 
   while (a[c] == b[c]) {
      if (a[c] == '\0' || b[c] == '\0')
         break;
      c++;
   }
   
   if (a[c] == '\0' && b[c] == '\0')
      return 1;
   else
      return 0;
}
int checkpalindrome(char* str)
{
	int length = strlen(str),a[26]={-1},o=0;
	int count=0;
	for(int i=0;i<length;i++)
	{
		for(int j=0;j<length;j++)
			if(str[j]==str[i])
				count++;
		a[i]=count;
	}
	for(int i=0;i<26;i++)
		if(a[i]%2!=0)
			o++;
	if(o == 1 || o == 0)
		return 1;
	else
		return 0;
}

void *function(void *data)
{
	struct info *clientinfo =(struct info*)data;
	char buffer[MAXLINE];
	int len = recv(clientinfo->newfd, buffer, sizeof(buffer), 0);
	buffer[len] = '\0';
	send(clientinfo->newfd, clientinfo->ip, strlen(clientinfo->ip), 0);
	
	sprintf(buffer, "%d\n",clientinfo->port);
	send(clientinfo->newfd,buffer, strlen(buffer), 0);

	while(1)
	{
		int n=recv(clientinfo->newfd,(char*)buffer, MAXLINE,0);
		buffer[n]='\0';
		if(checkpalindrome(buffer) == 1)
		{
			int len = strlen(buffer);
			char *arr = (char*)malloc(len*sizeof(char));
			int reversecount = len-1;
			int startcount = 0;
			int mid = len/2;
			for(int i=0;i<len;i++)
			{
				int samecount = 0;
				for(int j=i+1;j<len;j++)
				{
					if(buffer[i] == buffer[j])
					{
						samecount++;
						if(samecount > 1)
						{
							arr[mid];
						}
						else
						{
							arr[startcount] = buffer[i];
							arr[reversecount] = buffer[j];
							startcount++;
							reversecount++;
						}
					}
				}
			}
		//char *arr = (char*)malloc(40*sizeof(char)); 
		//arr = "Yes The Given String can be Plaindrome";
		send(clientinfo->newfd, arr, strlen(arr), 0);
		}
		else
		{
			char *arr = (char*)malloc(40*sizeof(char)); 
			arr ="No The Given String can't be Plaindrome";
			send(clientinfo->newfd, arr, strlen(arr), 0);
		}

		char *arr = (char*)malloc(40*sizeof(char)); 
		arr = "Enter Yes to check any other word";
		send(clientinfo->newfd, arr, strlen(arr), 0);
		/*n=recv(clientinfo->newfd,(char*)buffer, MAXLINE,0);
		buffer[n]='\0';
		char *y = (char*)malloc(5*sizeof(char));		
		y = "Yes\0";
		if(compare(buffer,y)==0)
		{
			close(clientinfo->newfd);	
			break;
		}*/
		
	}
}

// Driver code 
int main() { 
	
	struct sockaddr_in servaddr, cliaddr; 
	
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	listen(sockfd, 10);

	int len=sizeof(cliaddr); 
	int n;
	int newsockfd;
	pthread_t tid;
	printf("\n Server is Running \n");
	while (1)
	{
		// printf("\n Server is Running \n");
		len = sizeof(cliaddr);
		newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &len);
		struct info* i = malloc(sizeof(struct info));
		i->ip = inet_ntoa(cliaddr.sin_addr);
		i->port = ntohs(cliaddr.sin_port);
		i->newfd = newsockfd;
		int status = pthread_create(&tid, NULL, function, (void*)i);
		printf("Thread successfully created.\n");
		
	}
	pthread_exit(&tid);
	return 0; 
} 
