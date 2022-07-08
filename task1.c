#include<stdio.h>
#include <pthread.h>
#include<stdlib.h>
void*print(void * ptr)
{
	printf("Name = Saad \nReg No:L1F19BSCS0549\n");
	//return NULL;
}
int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,&print,NULL);
	pthread_exit(NULL);
return 0;
}
