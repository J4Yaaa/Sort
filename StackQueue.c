#include "StackQueue.h"

/////////////栈操作

void SeqStackInit(SeqStack* stack)
{
    if(stack == NULL)
    {
        return;
    }
    stack->size = 0;
}

void SeqSatckDestory(SeqStack* stack)
{
    if(stack == NULL)
    {
        return;
    }
    stack->size = 0;
}

void SeqStackPush(SeqStack* stack, SeqStackType value)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size >= SeqStackMaxSize)
    {
        return;
    }
    stack->data[stack->size++] = value;
}

void SeqStackPop(SeqStack* stack)
{
    if(stack == NULL)
    {
        return;
    }
    if(stack->size <= 0)
    {
        return;
    }
    --stack->size;
}

int SeqStackTop(SeqStack* stack, SeqStackType* value)
{
    if(stack == NULL || value == NULL)
    {
        return 0;
    }
    if(stack->size <= 0)
    {
        return 0;
    }
    *value = stack->data[stack->size - 1];
    return 1;
}

//////////////队列操作
void SeqQueueInit(SeqQueue* q)
{
    if(q == NULL)
    {
        return;
    }
    q->head = 0;
    q->tail = 0;
    q->size = 0;
}

void SeqQueueDestory(SeqQueue* q)
{
    if(q == NULL)
    {
        return;
    }
    q->head = 0;
    q->tail = 0;
    q->size = 0;

}

void SeqQueuePush(SeqQueue* q, QueueType value)
{
    if(q == NULL)
    {
        return;
    }
    if(q->size >= QueueMaxSize)
    {
        return;
    }
    q->data[q->tail++] = value;
    if(q->tail >= QueueMaxSize)
    {
        q->tail %= QueueMaxSize;
    }
    ++q->size;
}

void SeqQueuePop(SeqQueue* q)
{
    if(q == NULL)
    {
        return;
    }
    if(q->size <= 0)
    {
        return;
    }
    ++q->head;
    if(q->head >= QueueMaxSize)
    {
        q->head %= QueueMaxSize;
    }
    --q->size;
}

int SeqQueueFront(SeqQueue* q, QueueType* value)
{
    if(q == NULL || value == NULL)
    {
        return 0;
    }
    if(q->size <= 0)
    {
        return 0;
    }
    *value = q->data[q->head];
    return 1;
}

size_t SeqQueueSize(SeqQueue* q)
{
    if(q == NULL)
    {
        return 0;
    }
    return q->size;
}

////////////////////////////////////////////////////////////////
//测试代码
////////////////////////////////////////////////////////////////

#if 0

#define TEST_HEADER printf("\n----------------%s--------------\n",__FUNCTION__)

void TestStack()
{
    TEST_HEADER;
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,'a');
    SeqStackPush(&stack,'b');
    SeqStackPush(&stack,'c');
    SeqStackPush(&stack,'d');
    SeqStackType value;
    int ret = 0;

    ret = SeqStackTop(&stack,&value);
    printf("ret except 1,actual %d; value except d,actual %c\n",ret,value);
    SeqStackPop(&stack);

    ret = SeqStackTop(&stack,&value);
    printf("ret except 1,actual %d; value except c,actual %c\n",ret,value);
    SeqStackPop(&stack);

    ret = SeqStackTop(&stack,&value);
    printf("ret except 1,actual %d; value except b,actual %c\n",ret,value);
    SeqStackPop(&stack);

    ret = SeqStackTop(&stack,&value);
    printf("ret except 1,actual %d; value except a,actual %c\n",ret,value);
    SeqStackPop(&stack);

    ret = SeqStackTop(&stack,&value);
    printf("ret except 0,actual %d;\n",ret);
    SeqStackPop(&stack);
}

void TestQueue()
{
    TEST_HEADER;
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,'a');
    SeqQueuePush(&q,'b');
    SeqQueuePush(&q,'c');
    SeqQueuePush(&q,'d');

    QueueType value;
    int ret = 0;

    ret = SeqQueueFront(&q,&value);
    printf("ret = %d,value = %c,size = %lu\n",ret,value,SeqQueueSize(&q));
    SeqQueuePop(&q);

    ret = SeqQueueFront(&q,&value);
    printf("ret = %d,value = %c,size = %lu\n",ret,value,SeqQueueSize(&q));
    SeqQueuePop(&q);

    ret = SeqQueueFront(&q,&value);
    printf("ret = %d,value = %c,size = %lu\n",ret,value,SeqQueueSize(&q));
    SeqQueuePop(&q);

    ret = SeqQueueFront(&q,&value);
    printf("ret = %d,value = %c,size = %lu\n",ret,value,SeqQueueSize(&q));
    SeqQueuePop(&q);

    ret = SeqQueueFront(&q,&value);
    printf("ret = %d,size = %lu\n",ret,SeqQueueSize(&q));
    SeqQueuePop(&q);
}

int main()
{
    TestStack();
    TestQueue();
    return 0;
}

#endif
