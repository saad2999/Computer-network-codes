// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8084
#define MAXLINE 1024 

// Driver code 
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
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *h =(char*)malloc(30*sizeof(char)); 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(1);

	}
	int n, len=sizeof(servaddr);
	//connect(sockfd,(struct sockaddr*) &servaddr,len);
;
	h = "Hello Server";
	send(sockfd, (const char *)h, strlen(h), 0);
	printf("\nWelcome Client's IP Address & Port Number= \n");
	n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	buffer[n] = '\0';
	write(1,buffer,strlen(buffer));
	n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	buffer[n] = '\0';
	sleep(0.5);
	printf("\n\n");
	//printf("\nWelcome Client's Port no = %s\n",buffer);
	write(1,buffer,strlen(buffer));		
	int f = 0;
	char*hello = (char*)malloc(100*sizeof(char));
	while(1)
	{
		printf("\nEnter String to Check:");
		fgets(hello,100,stdin);
		send(sockfd,(const char*)hello,strlen(hello),0);
		n=recv(sockfd,(char*)buffer,MAXLINE,0);
		buffer[n]='\0';
		write(1,buffer,strlen(buffer));
		sleep(0.5);
		printf("\n\n");
		
		n=recv(sockfd,(char*)buffer,MAXLINE,0);
		buffer[n]='\0';
		//printf("\n%s\n",buffer);
		
		write(1,buffer,strlen(buffer));

		/*char*ans=(char*)malloc(5*sizeof(char));
		scanf("%s",ans);
		send(sockfd,(const char*)ans,strlen(hello),0);
		char *y = (char*)malloc(5*sizeof(char));
		y = "Yes\0";
		if(compare(hello,y)==0)
			break;
		else
			printf("\n");*/
		sleep(0.5);		
		printf("\n\n");
	} 
	close(sockfd); 
	return 0; 
}


