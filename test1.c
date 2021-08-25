#include <pthread.h>
#include <stdio.h>

void *routine(void)
{
	printf("This is a test\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, NULL, routine(), NULL);
	pthread_create(&t2, NULL, routine(), NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
