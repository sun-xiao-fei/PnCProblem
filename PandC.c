#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define Max 10
pthread_mutex_t the_mutex;
pthread_cond_t condConsumer;
pthread_cond_t condProducer;
int bufferSize = 2;
int buffer = 0;

void *producer1(void *ptr)
{
	printf("pro1\n");
	for(int i = 0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == bufferSize)
		{
			printf("Full!	Producer1 is waiting.\n");		
			pthread_cond_wait(&condProducer, &the_mutex);
		}
		buffer++;
		printf("Producer1 produced a toy......%d\n", i);
		sleep(4);
		pthread_cond_broadcast(&condConsumer);
		pthread_cond_broadcast(&condProducer);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *producer2(void *ptr)
{
	printf("pro2\n");
	for(int i = 0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == bufferSize)
		{
			printf("Full!	Producer2 is waiting.\n");
			pthread_cond_wait(&condProducer, &the_mutex);
		}
		buffer++;
		printf("Producer2 produced a toy......%d\n", i);
		sleep(4);
		pthread_cond_broadcast(&condConsumer);
		pthread_cond_broadcast(&condProducer);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *producer3(void *ptr)
{
	printf("pro3\n");
	for(int i = 0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == bufferSize)
		{
			printf("Full!	Producer3 is waiting.\n");
			pthread_cond_wait(&condProducer, &the_mutex);
		}
		buffer++;
		printf("Producer3 produced a toy......%d\n", i);
		sleep(4);
		pthread_cond_broadcast(&condConsumer);
		pthread_cond_broadcast(&condProducer);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *consumer1(void *ptr)
{
	printf("con1\n");
	for(int i =0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == 0)
		{
			printf("Empty!	Consumer1 is waiting.\n");
			pthread_cond_wait(&condConsumer, &the_mutex);
		}
		buffer--;
		printf("Consumer1 retrived a toy......%d\n", i);
		sleep(4);
		pthread_cond_broadcast(&condConsumer);
		pthread_cond_broadcast(&condProducer);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}
void *consumer2(void *ptr)
{
	printf("con2\n");
	for(int i =0; i < Max; i++)
	{
		pthread_mutex_lock(&the_mutex);
		while(buffer == 0)
		{
			printf("Empty!	Consumer2 is waiting.\n");
			pthread_cond_wait(&condConsumer, &the_mutex);
		}
		buffer--;
		printf("Consumer2 retrived a toy......%d\n", i);
		sleep(4);
		pthread_cond_broadcast(&condConsumer);
		pthread_cond_broadcast(&condProducer);
		pthread_mutex_unlock(&the_mutex);
	}
	pthread_exit(0);
}

int main(int argc, char **argv)
{
	pthread_t pro1, con1, pro2, con2, pro3;
	pthread_mutex_init(&the_mutex, 0);
	pthread_cond_init(&condConsumer, 0);
	pthread_cond_init(&condProducer, 0);
	pthread_create(&pro3, 0, producer3, 0);
	printf("Have created pro3\n");

	pthread_create(&pro2, 0, producer2, 0);
	printf("Have created pro2\n");

	pthread_create(&pro1, 0, producer1, 0);
	printf("Have created pro1\n");

	pthread_create(&con2, 0, consumer2, 0);
	printf("Have created con2\n");

	pthread_create(&con1, 0, consumer1, 0);
	printf("Have created con1\n");
	pthread_join(pro1, 0);
	pthread_join(pro2, 0);
	pthread_join(con2, 0);
	pthread_join(con1, 0);

	pthread_join(pro3, 0);
	pthread_cond_destroy(&condConsumer);
	pthread_cond_destroy(&condProducer);
}
