//
//  queue.h
//  Mopsolver
//
//  Created by Giovana Puccini on 10/29/18.
//  Copyright © 2018 Giovana Puccini. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>

typedef struct Node_S * Node;

typedef struct Queue_S * Queue;

Queue createQueue();

size_t sizeQueue(Queue queue);

const int topQueue(Queue queue);

const int removeTopQueue(Queue queue);

void addItem(Queue queue, int item);

#endif /* queue_h */
