#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024
#define NUM_THREADS 4 // You can adjust the number of threads as needed

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;
pthread_mutex_t lock;

void* search_substrings(void* arg) {
    long id = (long)arg;
    int start = (n1 / NUM_THREADS) * id;
    int end = (id == NUM_THREADS - 1) ? n1 - n2 + 1 : (n1 / NUM_THREADS) * (id + 1);

    int local_count = 0;
    int i,j,k;
    for (i = start; i < end; i++) {
        int count = 0;
        for (j = i, k = 0; k < n2; j++, k++) {
            if (*(s1 + j) != *(s2 + k)) {
                break;
            } else {
                count++;
            }
            if (count == n2) {
                local_count++;
            }
        }
    }

    pthread_mutex_lock(&lock);
    total += local_count;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

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
    /*read s1 s2 from the file*/
    s1 = fgets(s1, MAX, fp);
    s2 = fgets(s2, MAX, fp);
    n1 = strlen(s1) - 1; /*length of s1*/
    n2 = strlen(s2) - 1; /*length of s2*/

    if (s1 == NULL || s2 == NULL || n1 < n2) /*when error exit*/
        return -1;

    return 1;
}

int main(int argc, char *argv[]) {
    int count;
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&lock, NULL);

    readf(fp);

    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, search_substrings, (void*)i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("The number of substrings is: %d\n", total);
    return 1;
}
