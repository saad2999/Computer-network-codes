#include<stdio.h>
#include <pthread.h>
#include<stdlib.h>
#include<string.h>
struct data{
	char*reg;
	char*name;
};
void*print(void * ptr)
{
	struct data s = *(struct data*)ptr;
	printf("\nMy Name is %s\nMy Registration Number is %s\n",s.name,s.reg);
	//return NULL;
}
int main()
{
	pthread_t tid;
	struct data s;	
	char*temp = (char*)malloc(100*sizeof(char));
	printf("Enter name:");
	fgets(temp,100,stdin);
	s.name = (char*)malloc(strlen(temp)*sizeof(char));
	strcpy(s.name,temp);
	printf("Enter Reg no:");
	scanf("%s",temp);
	s.reg = (char*)malloc(strlen(temp)*sizeof(char));
	strcpy(s.reg,temp);
	free(temp);

	pthread_create(&tid,NULL,&print,(void*)&s);
	pthread_exit(NULL);
return 0;
}
