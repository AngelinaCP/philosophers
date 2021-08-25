#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int primes[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 6};

void *routine(void *arg)
{
	int	index = *(int *)arg;
	int	sum = 0;
	for (int j = 0; j < 5; j++)
	{
		sum += primes[index + j];
	}
	printf("%d\n", sum);
	*(int *)arg = sum;
	return (arg);
}

int main(int argc, char **argv)
{
	int globalSum;

	globalSum = 0;
	pthread_t th[2];
	int i;
	for (i = 0; i < 2; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
		}
	}
	for (i = 0; i < 2; i++)
	{
		void	*r;
		if (pthread_join(th[i], &r) != 0)
		{
			perror("Failed to join thread\n");
		}
		globalSum += *(int *)r;
	}
	printf("%d\n", globalSum);
}