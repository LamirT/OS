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

void* consumer(void* arg) {
    Table* table = static_cast<Table*>(arg);

    sem_t* full = sem_open(SEM_FULL_NAME, 0);
    sem_t* empty = sem_open(SEM_EMPTY_NAME, 0);
    sem_t* mutex = sem_open(SEM_MUTEX_NAME, 0);

    if (full == SEM_FAILED || empty == SEM_FAILED || mutex == SEM_FAILED) {
        std::cerr << "Failed to open semaphore" << std::endl;
        return nullptr;
    }

    for (int i = 0; i < 10; ++i) {
        sem_wait(full);
        sem_wait(mutex);

        // Consume item
        int item = table->items[--table->count];
        std::cout << "Consumed: " << item << std::endl;

        sem_post(mutex);
        sem_post(empty);

        sleep(1); // Simulate time taken to consume an item
    }

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    return nullptr;
}

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    Table* table = static_cast<Table*>(mmap(nullptr, sizeof(Table), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    sem_t* full = sem_open(SEM_FULL_NAME, 0);
    sem_t* empty = sem_open(SEM_EMPTY_NAME, 0);
    sem_t* mutex = sem_open(SEM_MUTEX_NAME, 0);

    if (full == SEM_FAILED || empty == SEM_FAILED || mutex == SEM_FAILED) {
        std::cerr << "Failed to open semaphore" << std::endl;
        return 1;
    }

    pthread_t cons_thread;
    pthread_create(&cons_thread, nullptr, consumer, table);

    pthread_join(cons_thread, nullptr);

    sem_close(full);
    sem_close(empty);
    sem_close(mutex);

    munmap(table, sizeof(Table));
    close(shm_fd);

    return 0;
}