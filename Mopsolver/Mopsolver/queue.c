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

struct Tuple_S{
    int val1;
    int val2;
    Tuple parent;
};

struct Node_S{
    Tuple value;
    Node next;
};

struct Queue_S{
    size_t size;
    Node init_Node;
};

Tuple createTuple(int val1, int val2){
    Tuple t = (Tuple) malloc(sizeof(Tuple));
    t->val1 = val1;
    t->val2 = val2;
    t->parent = NULL;
    return t;
}

int getVal1(Tuple t){
    return t->val1;
}

int getVal2(Tuple t){
    return t->val2;
}

Tuple getParent(Tuple t){
    return t->parent;
}

void addParent(Tuple t, Tuple parent){
    t->parent = parent;
}

void enqueue(Queue queue, Tuple item){
    Node current;
    current = queue->init_Node;
    Node newNode;
    newNode = (Node) malloc(sizeof(struct Node_S));
    newNode->value = item;
    newNode->next = NULL;
    if(current != NULL){
        while(current->next != NULL){
            current = current->next;
        }
        current->next = newNode;
    }
    else{
        queue->init_Node = newNode;
    }
    queue->size++;
}

size_t sizeQueue(Queue queue){
    return queue->size;
}

Tuple dequeue(Queue queue){
    Tuple value = NULL;
    if(queue->init_Node != NULL){
        value = queue->init_Node->value;
        free(queue->init_Node);
        queue->init_Node = queue->init_Node->next;
    }
    return value;
}

Queue createQueue(){
    Queue queue = (Queue) malloc(sizeof(Queue));
    queue->size = 0;
    queue->init_Node = NULL;
    return queue;
}

void destroyQueue(Queue q){
    while(q->init_Node != NULL){
        Node temp = q->init_Node->next;
        free(q->init_Node->value);
        free(q->init_Node);
        q->init_Node = temp;
    }
    free(q);
}
