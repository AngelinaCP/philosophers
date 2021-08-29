#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fuel = 0;
pthread_mutex_t  mutexFuel;
pthread_cond_t condFuel;

void *filling_fuel(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 60;
		printf("Filled fuel...%d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
//		pthread_cond_signal(&condFuel);
	// signal only to one thread
		pthread_cond_broadcast(&condFuel);
		sleep(1);
	}
	return (NULL);
}

void *car(void *arg)
{
	pthread_mutex_lock(&mutexFuel);
	while (fuel < 40)
	{
		printf("No fuel. Waiting...\n");
		pthread_cond_wait(&condFuel, &mutexFuel);
		sleep(1);
	}
	fuel -= 40;
	printf("Got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t th[5];
	int i;

	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	for (i = 0; i < 5; i++)
	{
		if (i == 1)
			pthread_create(&th[i], NULL, &filling_fuel, NULL);
		else
			pthread_create(&th[i], NULL, &car, NULL);
	}
	for (i = 0; i < 5; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
}