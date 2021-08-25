#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fuel = 0;
pthread_mutex_t  mutexFuel;

void *filling_fuel(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 15;
		printf("Filled fuel...%d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
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
		sleep(1);
	}
	fuel -= 40;
	printf("Got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t th[2];
	int i;

	for (i = 0; i < 2; i++)
	{
		if (i == 1)
			pthread_create(&th[i], NULL, &filling_fuel, NULL);
		else
			pthread_create(&th[i], NULL, &car, NULL);
	}
	for (i = 0; i < 2; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	pthread_mutex_destroy(&mutexFuel);
}