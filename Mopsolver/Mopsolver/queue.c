//
//  queue.c
//  Mopsolver
//
//  Created by Giovana Puccini on 10/29/18.
//  Copyright © 2018 Giovana Puccini. All rights reserved.
//

#include <memory.h>
#include <stdlib.h>
#include "queue.h"


struct Node_S{
    int value;
    Node next;
};

struct Queue_S{
    size_t size;
    Node init_Node;
};

void addItem(Queue queue, int item){
    Node current;
    current = queue->init_Node;
    while(current->next != NULL){
        current = current->next;
    }
    Node newNode;
    newNode = (Node) malloc(sizeof(struct Node_S));
    newNode->value = item;
    current->next = newNode;
    queue->size++;
}

const int removeTopQueue(Queue queue){
    int value = queue->init_Node->value;
    queue->init_Node = queue->init_Node->next;
    return value;
}

const int topQueue(Queue queue){
    return queue->init_Node->value;
}

Queue createQueue(){
    Queue queue;
    queue = (Queue) malloc(sizeof(struct Queue_S));
    queue->init_Node = NULL;
    queue->size = 0;
    return queue;
}
