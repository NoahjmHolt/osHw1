#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024
#define NUM_THREADS 4 // Number of threads to use

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int readf(FILE *fp) {
    if ((fp = fopen("strings.txt", "r")) == NULL) {
        printf("ERROR: can't open string.txt!\n");
        return 0;
    }
    s1 = (char *)malloc(sizeof(char) * MAX);
    if (s1 == NULL) {
        printf("ERROR: Out of memory!\n");
        return -1;
    }
    s2 = (char *)malloc(sizeof(char) * MAX);
    if (s2 == NULL) {
        printf("ERROR: Out of memory\n");
        return -1;
    }
    /* Read s1 s2 from the file */
    s1 = fgets(s1, MAX, fp);
    s2 = fgets(s2, MAX, fp);
    n1 = strlen(s1) - 1;  /* Length of s1 */
    n2 = strlen(s2) - 1;  /* Length of s2 */

    if (s1 == NULL || s2 == NULL || n1 < n2) {  /* Error condition */
        return -1;
    }
    return 0;
}

void *search_substring(void *arg) {
    int start = *(int *)arg;
    int end = start + n1 / NUM_THREADS;

    int count;
    for (int i = start; i < end; i++) {
        count = 0;
        for (int j = 0, k = i; j < n2; j++, k++) {
            if (s1[k] != s2[j]) {
                break;
            }
            count++;
            if (count == n2) {
                pthread_mutex_lock(&mutex);
                total++;
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int count;
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    readf(fp);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i * (n1 / NUM_THREADS);
        pthread_create(&threads[i], NULL, search_substring, (void *)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The number of substrings is: %d\n", total);

    return 0;
}
