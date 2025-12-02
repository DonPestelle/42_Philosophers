# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

int counter = 0;

void *thread_function(void *arg) {
    counter++;
    return NULL;
}

int main(void) {
    pthread_t thread[100000];
    for (int i = 0; i < 100000; i++) {
        pthread_create(&thread[i], NULL, thread_function, NULL);
    }
    sleep(10);/*
    for (int i = 0; i < 100000; i++) {
        pthread_join(thread[i], NULL);
    }*/
    printf("Final counter value: %d\n", counter);
    return 0;
}