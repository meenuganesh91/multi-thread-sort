/*
 program to do multithreaded sorting
 */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int unsorted_array[10] = {100,350, 10, 3, 150,1000, 4 , 0, 96, 28};
int sorted_array[10] = {0};

/*
 structure to know the positons of the array that we need to access.
 */
struct array_pos{
    int start_pos;
    int end_pos;
}positions_first, positions_second;

void *selection_sort(void* positions);
//void *merge_sort(void* );

int main(){
    
    pthread_t p_thread[3];
    int thr_id;
    int status;
    positions_first.start_pos = 0;
    positions_first.end_pos = 5;
    thr_id = pthread_create(&p_thread[0], NULL, selection_sort, (void*) &positions_first);
    if(thr_id < 0)
    {
        perror("Thread create error.");
        exit(0);
    }
    positions_second.start_pos = 5;
    positions_second.end_pos = 10;
    thr_id = pthread_create(&p_thread[1], NULL, selection_sort, (void*) &positions_second);
    if(thr_id < 0)
    {
        perror("Thread create error.");
        exit(0);
    }
    pthread_join(p_thread[0], NULL);
    printf("return thread 0 %d\n", status);
    pthread_join(p_thread[1], NULL);
    printf("return thread 1 %d\n", status);
    for(int i = 0; i<10; i++){
        printf("%d \n", unsorted_array[i]);
    }
    //thr_id = pthread_create(&p_thread[2], NULL, merge_sort, (void *) );
    if(thr_id < 0)
    {
        perror("Thread create error.");
        exit(0);
    }
    return 0;
    
}
void *selection_sort(void *positions){
    long tid;
    tid = (long)pthread_self;
    printf("Thread ID : (%lu) \n", tid);
    int temp = 0;
    struct array_pos* pos;
    pos = (struct array_pos*) positions;
    for(int i = pos->start_pos; i < pos->end_pos; i++){
        for(int j= i+1; j< pos->end_pos; j++){
            if(unsorted_array[i]> unsorted_array[j]){
                temp = unsorted_array[i];
                unsorted_array[i] = unsorted_array[j];
                unsorted_array[j] = temp;
            }
        }
    }
    pthread_exit(0);
    
}

