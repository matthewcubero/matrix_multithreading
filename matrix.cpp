#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#define NUM_THREADS 10

using namespace std;
clock_t start = clock();
int fd0[2], fd1[2], fd2[2], fd3[2], fd4[2];
int A[5] = {5,5,5,5,5};
int B[5] = {5,5,5,5,5};
int sum = 0;

// A threads, sends their current value to B
void *multA0(void *arg) {
    int element = (long)arg;
    cout << "Thread A0 made" << endl;
    // lets forward these to B threads
    write(fd0[1],&element,4);
    pthread_exit(NULL);
}
void *multA1(void *arg) {
    cout << "Thread A1 made" << endl;    
    int element = (long)arg;
    // lets forward these to B threads
    write(fd1[1],&element,4);
    pthread_exit(NULL);
}
void *multA2(void *arg) {
    cout << "Thread A2 made" << endl;
    int element = (long)arg;
    // lets forward these to B threads
    write(fd2[1],&element,4);
    pthread_exit(NULL);
}
void *multA3(void *arg) {
    cout << "Thread A3 made" << endl;
    int element = (long)arg;
    // lets forward these to B threads
    write(fd3[1],&element,4);
    pthread_exit(NULL);
}
void *multA4(void *arg) {
    cout << "Thread A4 made" << endl;
    int element = (long)arg;
    // lets forward these to B threads
    write(fd4[1],&element,4);
    pthread_exit(NULL);
}
// B threads
void *multB0(void *arg) {
    cout << "Thread B0 made" << endl;
    // B threads will receive val from A and multiply them
    // together and add to total sum
    int elementB, elementA;
    read(fd0[0],&elementA,4);
    elementB = (long)arg;
    int result = elementA*elementB;
    sum+=result;
    pthread_exit(NULL);
}
void *multB1(void *arg) {
    cout << "Thread B1 made" << endl;
    // B threads will receive val from A and multiply them
    // together and add to total sum    
    int elementB, elementA;
    read(fd1[0],&elementA,4);
    elementB = (long)arg;
    int result = elementA*elementB;
    sum+=result;
    close(fd1[0]);
    pthread_exit(NULL);
}
void *multB2(void *arg) {
    cout << "Thread B2 made" << endl;
    // B threads will receive val from A and multiply them
    // together and add to total sum
    int elementB, elementA;
    read(fd2[0],&elementA,4);
    elementB = (long)arg;
    int result = elementA*elementB;
    sum+=result;
    pthread_exit(NULL);
}
void *multB3(void *arg) {
    cout << "Thread B3 made" << endl;    
    // B threads will receive val from A and multiply them
    // together and add to total sum
    int elementB, elementA;
    read(fd3[0],&elementA,4);
    elementB = (long)arg;
    int result = elementA*elementB;
    sum+=result;
    close(fd3[0]);
    pthread_exit(NULL);
}
void *multB4(void *arg) {
    cout << "Thread B4 made" << endl;    
    // B threads will receive val from A and multiply them
    // together and add to total sum
    int elementB, elementA;
    read(fd4[0],&elementA,4);
    elementB = (long)arg;
    int result = elementA*elementB;
    sum+=result;
    pthread_exit(NULL);
}
int main(int argc, char *argv[]) {
    // array of threads
    pthread_t threads[NUM_THREADS];
    int rc;
   
    // open all the pipes for the file descriptors
    if(pipe(fd0) < 0) {
        cout << "Pipe 0 ERROR" << endl;
        exit(1);
    }
    if(pipe(fd1) < 0) {
        cout << "Pipe 1 ERROR" << endl;
        exit(1);
    }
    if(pipe(fd2) < 0) {
        cout << "Pipe 2 ERROR" << endl;
        exit(1);
    }
    if(pipe(fd3) < 0) {
        cout << "Pipe 3 ERROR" << endl;
        exit(1);
    }
    if(pipe(fd4) < 0) {
        cout << "Pipe 4 ERROR" << endl;
        exit(1);
    }

    rc = pthread_create(&threads[0], NULL, multA0, (void *)A[0]);
    if(rc) { 
        cout << "Error with A0" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[1], NULL, multA1, (void *)A[1]);
    if(rc) { 
        cout << "Error with A1" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[2], NULL, multA2, (void *)A[2]);
    if(rc) { 
        cout << "Error with A2" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[3], NULL, multA3, (void *)A[3]);
    if(rc) { 
        cout << "Error with A3" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[4], NULL, multA4, (void *)A[4]);
    if(rc) { 
        cout << "Error with A4" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[5], NULL, multB0, (void *)B[0]);
    if(rc) { 
        cout << "Error with B0" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[6], NULL, multB1, (void *)B[1]);
    if(rc) { 
        cout << "Error with B1" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[7], NULL, multB2, (void *)B[2]);
    if(rc) { 
        cout << "Error with B2" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[8], NULL, multB3, (void *)B[3]);
    if(rc) { 
        cout << "Error with B3" << endl;
        exit(1);
    }
    rc = pthread_create(&threads[9], NULL, multB4, (void *)B[4]);
    if(rc) { 
        cout << "Error with B4" << endl;
        exit(1);
    }
    // join all threads to ensure correct answer
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);
    pthread_join(threads[5], NULL);
    pthread_join(threads[6], NULL);
    pthread_join(threads[7], NULL);
    pthread_join(threads[8], NULL);
    pthread_join(threads[9], NULL);
    cout << "The matrix mult is = " << sum << endl;
    clock_t end = clock();
    double cput_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    cout << "Program took " << cput_time_used << " seconds to execute" << endl;
    return 0;
}

// Compile with:
//  g++ -g -o matrix matrix.cpp -lpthread