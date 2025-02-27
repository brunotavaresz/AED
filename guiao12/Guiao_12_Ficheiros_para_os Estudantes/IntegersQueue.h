// IntegersQueue.h

#ifndef _INTEGERS_QUEUE_
#define _INTEGERS_QUEUE_

typedef struct _IntegersQueue Queue;

Queue* QueueCreate(int size);

void QueueDestroy(Queue** p);

void QueueClear(Queue* q);

int QueueSize(const Queue* q);

int QueueIsFull(const Queue* q);

int QueueIsEmpty(const Queue* q);

int QueuePeek(const Queue* q);

void QueueEnqueue(Queue* q, int i);

int QueueDequeue(Queue* q);

#endif  // _INTEGERS_QUEUE_
