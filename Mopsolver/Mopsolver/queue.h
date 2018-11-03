//
//  queue.h
//  Mopsolver
//
//  Created by Giovana Puccini on 10/29/18.
//  Copyright © 2018 Giovana Puccini. All rights reserved.
//

#ifndef queue_h
#define queue_h

typedef struct Tuple_S * Tuple;

typedef struct Node_S * Node;

typedef struct Queue_S * Queue;

Tuple createTuple(int val1, int val2);

int getVal1(Tuple t);

int getVal2(Tuple t);

Tuple getParent(Tuple t);

void addParent(Tuple t, Tuple parent);

Queue createQueue();

size_t sizeQueue(Queue queue);

Tuple dequeue(Queue queue);

void enqueue(Queue queue, Tuple item);

void destroyQueue(Queue q);

#endif /* queue_h */
