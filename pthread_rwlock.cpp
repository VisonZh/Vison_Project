#include <stdio.h>
#include<pthread.h>
#include<iostream>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

using namespace std;
#define NUM 5

#define BUFF_MAX 1024

char work_buff[BUFF_MAX];
void* (*p[NUM])(void*);

pthread_rwlock_t rwlock;//

void * ReadThread(void *data)
{
	char* threadId = (char *)data;
	while(1)	
	{
		pthread_rwlock_rdlock(&rwlock);
		if(work_buff[0] == '\0')
		{
			cout << "Read Thread "<<threadId <<" work_buff is null" << endl;
			pthread_rwlock_unlock(&rwlock);
			sleep(rand()%5);
		}
		else
		{
			cout << "Read Thread "<< threadId <<" have  read:"<< work_buff<<endl;
			pthread_rwlock_unlock(&rwlock);
			sleep(rand()%5);
		}
	}

}

void * WriteThread(void* data)
{
	char* threadId = (char *)data;
	time_t now;
	struct tm * timenow;
	char strtmp[255];
	//time(&now);
	//stimenow= localtime(&now);
	while(1)	
	{
		time(&now);
		timenow= localtime(&now);
		pthread_rwlock_wrlock(&rwlock);
		if(work_buff[0] != '\0')
		{
			memset(work_buff , 0, BUFF_MAX);
			
			strcpy(work_buff, asctime(timenow));
			cout << "WriteThread "<< data <<" have  write:"<< work_buff<<endl;
			pthread_rwlock_unlock(&rwlock);
			sleep(rand()%5);
		}
		else
		{
			
			sprintf(work_buff, "Write thread %s ,write at time:%s\n", ((char *)data), asctime(timenow));
			//printf("WriteThread 1  write:%s", asctime(timenow));
			cout << "WriteThread "<< data <<" have  write:"<< work_buff<<endl;
			pthread_rwlock_unlock(&rwlock);
			sleep(rand()%2+3);

		}
	}
}

int main(int arc, char **arg)
{
	int bRet;
	void *ret;
	pthread_t pid[5];

	bRet = 	pthread_rwlock_init(&rwlock, NULL);
	if(0 != bRet)
	{
		perror("rwlock initialization failed");
		exit(EXIT_FAILURE);
	}



	bRet = pthread_create(&pid[0], NULL, WriteThread,(void*)"1");
	if(0 != bRet)
	{
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}

	bRet = pthread_create(&pid[1], NULL, ReadThread,(void*)"1");
	if(0 != bRet)
	{
		perror("Thread creation failed!");
		exit(EXIT_FAILURE);
	}


	for(int i = 0; i < 3; i++)
		pthread_join(pid[i],&ret);

	pthread_rwlock_destroy(&rwlock);

	return 0;
}
