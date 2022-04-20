// We use a circular queue

#include <stdio.h>
#include <malloc.h>

typedef struct Queue {
    int head, tail, size, check;
    int* array;
};

// returns 1 if queue is full, else returns 0
int isQueueFull(struct Queue* q) {
    return (q->head == q->tail && q->check) ? 1 : 0;
}

// returns 1 if queue is empty, else returns 0
int isQueueEmpty(struct Queue* q) {
    return (q->head == q->tail && !q->check) ? 1 : 0;
}

// returns -1 if queue is already full, else returns 0
int enQueue(struct Queue* q, int val) {
    if(isQueueFull(q)) return -1;

    q->array[q->tail] = val;
    if((q->tail + 1) % q->size == 0) q->check = 1 - q->check;
    q->tail = (q->tail + 1) % q->size;
    return 0;
}

// returns -1 if queue is already empty, else returns the dequeued element
int deQueue(struct Queue* q) {
    if(isQueueEmpty(q)) return -1;

    if((q->head + 1) % q->size == 0) q->check = 1 - q->check;
    q->head = (q->head + 1) % q->size;
    return q->array[(q->head + q->size - 1) % q->size];
}

int search(int array[], int size, int value) {
    for(int i=0 ; i<size ; i++) {
        if(array[i] == value) return i;
    }
    return -1;
}


int main()
{
    // ----------------------------- input starts ------------------------------
    struct Queue q;
    int referenceCount, pageFrameCount;
    double hitCount = 0;
    int reference[1000];
    printf("Number of references: ");
    scanf("%d", &referenceCount);

    printf("Enter the page references\n");
    for(int i=0 ; i<referenceCount ; i++) scanf("%d", &reference[i]);

    printf("Number of page frames: ");
    scanf("%d", &pageFrameCount);

    // ------------- initialize the queue --------------------
    q.array = malloc(sizeof(int) * pageFrameCount);
    q.check = 0;
    q.size = pageFrameCount;
    q.head = q.tail = 0;

    for(int i=0 ; i<q.size ; i++) q.array[i] = -1;
    // -------------- queue initialized ---------------------

    // -------------------------------- input ends -------------------------------

    for(int i=0 ; i<referenceCount ; i++) {

        if(search(q.array, q.size, reference[i]) == -1) {   // the reference is not in the page frame array

            if(!isQueueFull(&q)) {      // if queue is not full
                enQueue(&q, reference[i]);
            }
            else {                      // queue is full

                // we are basically replacing a page here
                deQueue(&q);
                enQueue(&q, reference[i]);
            }
        }
        else {
            // it iz a hit
            hitCount++;
        }
    }

    // display the final page frame array
    printf("Final page frame array\n");
    for(int i=0 ; i<q.size ; i++) printf("%d ", q.array[i]);
    printf("\nHit Count = %.0f\t", hitCount);
    printf("Hit ratio: %f", hitCount / referenceCount);
    printf("\nNumber of page faults = %.0f\t", referenceCount - hitCount);
    printf("Page Fault Ratio: %f\n", 1 - (hitCount / referenceCount));

}