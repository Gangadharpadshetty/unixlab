a.
#include <iostream>
#include <pthread.h>
// Function that will be executed by each thread
void* countTo100(void* arg) {
int item = *((int*)arg);
for (int i = 1; i <= 100; ++i) {
std::cout << "Thread " << item << ": Count " << i << std::endl;
}
pthread_exit(NULL);
}
int main() {
const int numThreads = 2;
pthread_t threads[numThreads];
// Loop to create threads
for (int i = 0; i < numThreads; ++i) {
int* item = new int(i);
int threadCreateStatus = pthread_create(&threads[i], NULL, countTo100, (void*)item);
if (threadCreateStatus) {
std::cerr << "Error creating thread: " << threadCreateStatus << std::endl;
return -1;
}
}
// Wait for both threads to finish
for (int i = 0; i < numThreads; ++i) {
pthread_join(threads[i], NULL);
}
return 0;
}
