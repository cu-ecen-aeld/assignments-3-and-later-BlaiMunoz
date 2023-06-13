#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

typedef struct {
    pthread_mutex_t* mutex;
    int wait_to_obtain_ms;
    int wait_to_release_ms;
} thread_data_t;

void* threadfunc(void* thread_param) {
    thread_data_t* thread_data = (thread_data_t*)thread_param;

    // Wait for wait_to_obtain_ms milliseconds
    usleep(thread_data->wait_to_obtain_ms * 1000);

    // Obtain the mutex
    pthread_mutex_lock(thread_data->mutex);
    printf("Thread obtained mutex\n");

    // Wait for wait_to_release_ms milliseconds
    usleep(thread_data->wait_to_release_ms * 1000);

    // Release the mutex
    pthread_mutex_unlock(thread_data->mutex);
    printf("Thread released mutex\n");

    return thread_param;
}

bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex, int wait_to_obtain_ms, int wait_to_release_ms)
{
    // Allocate memory for thread_data
    thread_data_t* thread_data = (thread_data_t*)malloc(sizeof(thread_data_t));
    if (thread_data == NULL) {
        return false; // Memory allocation failed
    }

    // Set up mutex and wait arguments
    thread_data->mutex = mutex;
    thread_data->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_data->wait_to_release_ms = wait_to_release_ms;

    // Create the thread
    if (pthread_create(thread, NULL, threadfunc, thread_data) != 0) {
        free(thread_data);
        return false; // Thread creation failed
    }

    return true;
}
