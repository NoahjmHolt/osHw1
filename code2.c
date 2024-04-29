#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define BUFFER_SIZE 12

char buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int count = 0;
bool eof = false;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    FILE *file = fopen("message.txt", "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        pthread_mutex_lock(&mutex);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
}
	buffer[in] = ch;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    eof = true;
    fclose(file);
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while (1) {
pthread_mutex_lock(&mutex);
        while (count == 0 && !eof) {
            pthread_cond_wait(&full, &mutex);
        }

	if (count == 0 && eof) {
                break;
        }

	char ch = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("%c", ch);
fflush(stdout); // Flush stdout to ensure characters are printed immediately
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
  return 0;
}

