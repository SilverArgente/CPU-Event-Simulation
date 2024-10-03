/*
 * 7/10/24
*/

#include <stdlib.h>

struct Task {
    int id;
    int priority;
    int arrivalTime;
    int processingTime;
};

struct Node {
    struct Task task;
    int priority;
};

struct PQ {
    struct Node *heap;
    int size;
    int max_size;
};

struct PQ PQ_new(void) {
    /* Construct an empty heap */
    
    struct PQ pq;

    pq.heap = malloc(sizeof(struct Node) * 32);
    pq.size = 0;
    pq.max_size = 32;

    return pq;

}

void PQ_clear(struct PQ* pq) {
    /* Remove all elements from the heap, effectively clearing it */
    
    free(pq->heap);
    pq->max_size = 32;
    pq->size = 0;
    
}

int PQ_empty(struct PQ* pq) {
    /* Return 1 if the heap is empty; otherwise, return 0 */
    
    return pq->size == 0;

}

void PQ_enqueue(struct PQ* pq, struct Task element, int priority) {
    /* Insert the specified element into the heap with the given priority */
    
    struct Node node;
    int i;

    node.task = element;
    node.priority = priority;

    pq->size += 1;
    i = pq->size;

    /* If heap memory is full, reallocate more memory */
    if (i == pq->max_size)
    {
	pq->max_size += 32;
        pq->heap = realloc(pq->heap, sizeof(struct Node) * pq->max_size);
    }
    
    pq->heap[i] = node;
    
    /* Heapify new element up */
    while (i > 1 && pq->heap[i/2].priority > pq->heap[i].priority)
    {
	struct Node temp = pq->heap[i/2];
	pq->heap[i/2] = pq->heap[i];
	pq->heap[i] = temp;
	i = i/2;
    } 

}

void PQ_min_heapify(struct PQ *pq, int i)
{
    
    int mindex;

    /* Compare parent with left child to find minimum */ 
    if (2*i <= pq->size && pq->heap[2*i].priority < pq->heap[i].priority)
    {
	mindex = 2 * i;
    }
    else
    {
        mindex = i;
    }

    /* Compare newly found minimum with right child */
    if (2*i + 1 <= pq->size && pq->heap[2*i+1].priority < pq->heap[mindex].priority)
    {
        mindex = 2 * i + 1;
    }
    
    /* Recursively percolate down */ 
    if (mindex != i)
    {
        struct Node temp = pq->heap[i];
        pq->heap[i] = pq->heap[mindex];
	pq->heap[mindex] = temp;
        PQ_min_heapify(pq, mindex);
    }

}

struct Task PQ_dequeue(struct PQ* pq) {
    /* Retrieve and remove the highest-priority element from the heap */
    
    struct Node node;
    struct Task task;
    int size;

    node = pq->heap[1];
    task = node.task;
    size = pq->size;

    pq->heap[1] = pq->heap[size];
    pq->size -= 1;

    PQ_min_heapify(pq, 1);

    return task;

}

struct Task PQ_front(struct PQ* pq) {
    /* Retrieve the highest-priority element without removing it */
    
    return pq->heap[1].task;

}

int PQ_priority(struct PQ* pq) {
    /* Retrieve the priority of the highest-priority element on the heap */
    
    return pq->heap[1].priority;

}
