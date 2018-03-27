#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define QueueMaxSize 100

typedef int QueueType;

typedef struct SeqQueue
{
        QueueType data[QueueMaxSize];
        size_t tail;
        size_t head;
        size_t size;
}SeqQueue;

void SeqQueueInit(SeqQueue* q);

void SeqQueueDestory(SeqQueue* q);

void SeqQueuePush(SeqQueue* q, QueueType value);

void SeqQueuePop(SeqQueue* q);

int SeqQueueFront(SeqQueue* q, QueueType* value);

size_t SeqQueueSize(SeqQueue* q);


typedef int SeqStackType;

#define SeqStackMaxSize 1000

typedef struct SeqStack
{
        SeqStackType data[SeqStackMaxSize];
        size_t size;
}SeqStack;

void SeqStackInit(SeqStack* stack);

void SeqSatckDestory(SeqStack* stack);

void SeqStackPush(SeqStack* stack, SeqStackType value);

void SeqStackPop(SeqStack* stack);

int SeqStackTop(SeqStack* stack, SeqStackType* value);


