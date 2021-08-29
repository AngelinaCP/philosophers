#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

void *roll_dice()
{
	int *value = malloc(sizeof(int));
	int res;
	res = (rand() % 6) + 1;
	*value = res;
	return ((void *)value);
}
int main(int argc, char **argv)
{
	int *res;

	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(th, (void**)&res) != 0)
		return (2);
	printf("Result: %d", *res);
	free(res);
	return (0);
}