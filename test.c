#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t lock;
void	*routine(void *arg)
{
	int *t = (int *)arg; // here we have the value
	for (int i = 0; i < 1000000; i++)
	{
        pthread_mutex_lock(&lock);
        *t = *t +1;
        pthread_mutex_unlock(&lock);
	}
    int* a = malloc(sizeof(int*));
            pthread_mutex_lock(&lock);

    *a = *t;
            pthread_mutex_unlock(&lock);

    return (void *) a;
}

int	main(void)
{
	pthread_t t[8];
    pthread_mutex_init(&lock , NULL);
	int i = 0;
	int result = 0;
    int* res2;
	while (i < 8)
	{
		pthread_create(t + i, NULL, routine, &result);
		i++;
	}
	i = 0;
	while (i < 7)
	{
        free(res2);
		pthread_join(t[i],(void **) &res2);
		i++;
	}
    pthread_join(t[7] , (void**)&res2);
    printf("the result is : %d \nand the return value is: %d\n " ,result , *res2) ;
    free(res2);
    pthread_mutex_destroy(&lock);
	return (0);
}