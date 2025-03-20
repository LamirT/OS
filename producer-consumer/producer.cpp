#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstring>

const char* SHM_NAME = "/prod_cons_shm";
const char* SEM_FULL_NAME = "/full";
const char* SEM_EMPTY_NAME = "/empty";
const char* SEM_MUTEX_NAME = "/mutex";

struct Table {
    int items[2];
    int count;
};

void* producer(void* arg) {
    Table* table = static_cast<Table*>(arg);

    sem_t* full = sem_open(SEM_FULL_NAME, 0);
    sem_t* empty = sem_open(SEM_EMPTY_NAME, 0);
    sem_t* mutex = sem_open(SEM_MUTEX_NAME, 0);

    if (full == SEM_FAILED || empty == SEM_FAILED || mutex == SEM_FAILED) {
        std::cerr << "Failed to open semaphore" << std::endl;
        return nullptr;
    }

    for (int i = 0; i < 10; ++i) {
        sem_wait(empty);
        sem_wait(mutex);

        // Produce item
        table->items[table->count] = i;
        table->count++;
        std::cout << "Produced: " << i << std::endl;

        sem_post(mutex);
        sem_post(full);

        sleep(1); // Simulate time taken to produce an item
    }

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    return nullptr;
}

int main() {
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(Table));
    Table* table = static_cast<Table*>(mmap(nullptr, sizeof(Table), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
    table->count = 0;

    sem_t* full = sem_open(SEM_FULL_NAME, O_CREAT, 0666, 0);
    sem_t* empty = sem_open(SEM_EMPTY_NAME, O_CREAT, 0666, 2);
    sem_t* mutex = sem_open(SEM_MUTEX_NAME, O_CREAT, 0666, 1);

    if (full == SEM_FAILED || empty == SEM_FAILED || mutex == SEM_FAILED) {
        std::cerr << "Failed to create semaphore" << std::endl;
        return 1;
    }

    pthread_t prod_thread;
    pthread_create(&prod_thread, nullptr, producer, table);

    pthread_join(prod_thread, nullptr);

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);
    sem_unlink(SEM_FULL_NAME);
    sem_unlink(SEM_EMPTY_NAME);
    sem_unlink(SEM_MUTEX_NAME);

    munmap(table, sizeof(Table));
    shm_unlink(SHM_NAME);

    return 0;
}