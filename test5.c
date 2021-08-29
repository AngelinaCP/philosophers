#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

int primes[5] = {1, 3, 4, 5, 6};

void *routine(void *arg)
{
	//sleep(1);
	int index = *(int *)arg;
	printf("%d ", primes[index]);
	free (arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t th[5];
	int	i;

	for (i = 0; i < 5; i++)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		pthread_create(&th[i], NULL, &routine, a);
	}
	for (i = 0; i < 5; i++)
	{
		pthread_join(th[i], NULL);
	}

}