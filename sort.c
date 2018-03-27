#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StackQueue.h"
void PrintArr(int arr[],int size);

int cmp(int a,int b)
{
    return a > b ? 1 : 0;
}

void Swap(int* a,int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//把最大的往最后放 其实是沉底排序
//void BubbleSort(int arr[],int size)
//{
//    if(arr == NULL || size <= 1)
//    {
//        return;
//    }
//    int i = 0;
//    for(; i < size; ++i)
//    {
//        int j = 0;
//        for(; j < size - i - 1; ++j)
//        {
//            if(cmp(arr[j],arr[j+1]))
//            {
//                Swap(&arr[j],&arr[j+1]);
//            }
//        }
//    }
//}

//从后往前，把最小的往最前面放 -> 冒泡
void BubbleSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int i = size - 1;
    for(; i > 0; --i)
    {
        int j = size - 1;
        for(; j > size - i - 1;--j)
        {
            if(!cmp(arr[j],arr[j-1]))
            {
                Swap(&arr[j],&arr[j-1]);
            }
        }
    }
}

void SelectSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int i = 0;
    for(; i < size; ++i)
    {
        int j = i + 1;
        for(; j < size; ++j)
        {
            if(cmp(arr[i],arr[j]))
            {
                Swap(&arr[i],&arr[j]);
            }
        }
    }
}

void InsertSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int i = 1;
    for(; i < size; ++i)
    {
        int tmp = arr[i];
        int j = i;
        for(;j > 0; --j)
        {
            if(cmp(arr[j - 1],tmp))
            {
                arr[j] = arr[j - 1];
            }
            else
            {
                break;
            }
        }
        arr[j] = tmp;
    }
}

void AdjustDown(int arr[],int size,int index)
{
    if(arr == NULL)
    {
        return;
    }
    if(index >= size || index < 0)
    {
        return;
    }
    int parent = index;
    while(parent < size)
    {
        int child = parent * 2 + 1;
        if(child < size)
        {
            if(child + 1 < size && arr[child + 1] > arr[child])
            {
                child += 1;
            }
            if(cmp(arr[child],arr[parent]))
            {
                Swap(&arr[child],&arr[parent]);
            }
        }
        parent = child;
    }
}

void HeapSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int i = (size - 1 - 1) /2;
    for(; i >= 0; --i)
    {
        AdjustDown(arr,size,i);
    }
    for(i = size - 1;i > 0; --i)
    {
        Swap(&arr[0],&arr[i]);
        AdjustDown(arr,i,0);
    }
}

void ShellSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    //希尔序列 2 4 8 ...
    int gap = 1;
    for(; gap < size; gap *= 2)
    {
        int i = gap;
        for(; i < size; ++i)
        {
            int tmp = arr[i];
            int j = i;
            for(; j >= gap; j -= gap)
            {
                if(cmp(arr[j-gap],tmp))
                {
                    arr[j] = arr[j - gap];
                }
                else 
                {
                    break;
                }
            }
            arr[j] = tmp;
        }
    }
}

void MergeArr(int arr[],int beg,int mid,int end,int* buf)
{
    if(arr == NULL || buf == NULL)
    {
        return;
    }
    if(end - beg < 1)
    {
        return;
    }
    int beg_pos = beg;
    int mid_pos = mid;
    int index = beg;
    while(mid - beg_pos > 0 && end - mid_pos > 0)
    {
        if(arr[beg_pos] < arr[mid_pos])
        {
            buf[index++] = arr[beg_pos++];
        }
        else
        {
            buf[index++] = arr[mid_pos++];
        }
    }
    while(mid - beg_pos > 0)
    {
        buf[index++] = arr[beg_pos++];
    }
    while(end - mid_pos > 0)
    {
        buf[index++] = arr[mid_pos++];
    }
    memcpy(arr+beg,buf+beg,sizeof(arr[0])*(end - beg));
}

void _MergeSort(int arr[],int beg,int end,int* buf)
{
    if(arr == NULL)
    {
        return;
    }
    if(end - beg <= 1)
    {
        return;
    }
    int mid = beg + (end - beg)/2;
    _MergeSort(arr,beg,mid,buf);
    _MergeSort(arr,mid,end,buf);
    MergeArr(arr,beg,mid,end,buf);
}

void MergeSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    //每次排序的空间是一个 [beg,end) 的前闭后开区间
    int* buf = (int*)malloc(sizeof(arr[0])*size);
    memcpy(buf,arr,sizeof(arr[0])*size);
    _MergeSort(arr,0,size,buf);
}

void MergeSortByLoop(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    int* buf = (int*)malloc(sizeof(arr[0])*size);
    memcpy(buf,arr,sizeof(arr[0])*size);
    int gap = 1;
    for(; gap < size; gap *= 2)
    {
        int bound = 0;
        for(; bound < size; bound += gap * 2)
        {
            int beg = bound;
            int end = bound + gap * 2;
            int mid = beg + (end - beg)/2;
            if(end > size)
            {
                end = size;
            }
            if(mid > size)
            {
                mid = size;
            }
            MergeArr(arr,beg,mid,end,buf);
        }
    }
}

int Partion(int arr[],int left,int right)
{
    if(arr == NULL)
    {
        return -1;
    }
    if(right - left <= 1)
    {
        return -1;
    }
    int beg = left;
    int end = right - 1;
    int key = arr[end];
    while(end > beg)
    {
        //注意 ： 必须从左向右开始找
        while(end > beg && arr[beg] <= key)
        {
            ++beg;
        }
        while(end > beg && arr[end] >= key)
        {
            --end;
        }
        if(end > beg)
        {
            Swap(&arr[beg],&arr[end]);
        }
    }
    Swap(&arr[beg],&arr[right - 1]);
    return beg;
}

int Partion2(int arr[],int left,int right)
{
    if(arr == NULL)
    {
        return -1;
    }
    if(right - left <= 1)
    {
        return -1;
    }
    int beg = left;
    int end = right - 1;
    int key = arr[end];
    while(end > beg)
    {
        while(end > beg && arr[beg] <= key)
        {
            ++beg;
        }
        if(end > beg)
        {
            arr[end] = arr[beg];
        }
        while(end > beg && arr[end] >= key)
        {
            --end;
        }
        if(end > beg)
        {
            arr[beg] = arr[end];
        }
    }
    arr[beg] = key;
    return beg;
}

void _QuickSort(int arr[],int left,int right)
{
    if(arr == NULL)
    {
        return;
    }
    if(right - left <= 1)
    {
        return;
    }
    int mid = Partion2(arr,left,right);
    _QuickSort(arr,left,mid);
    _QuickSort(arr,mid+1,right);
}

void QuickSort(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    //这里每次排序的数组都是一个前闭后开的区间
    _QuickSort(arr,0,size);
}

void QuickSortByLoop(int arr[],int size)
{
    if(arr == NULL || size <= 1)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,0);
    SeqStackPush(&stack,size);
    while(stack.size != 0)
    {
        int beg = 0;
        int end = 0;
        SeqStackTop(&stack,&end);
        SeqStackPop(&stack);
        SeqStackTop(&stack,&beg);
        SeqStackPop(&stack);
        if(end - beg <= 1)
        {
            continue;
        }
        int mid = Partion(arr,beg,end);
        SeqStackPush(&stack,beg);
        SeqStackPush(&stack,mid);
        SeqStackPush(&stack,mid + 1);
        SeqStackPush(&stack,end);
    }
}

///////////////////////////////////////////////////////
//测试代码
///////////////////////////////////////////////////////

#if 1

#define TEST_HEADER printf("\n~~~~~~~~~~%s~~~~~~~~~~\n",__FUNCTION__)

void PrintArr(int arr[],int size)
{
    int i = 0;
    for(; i < size; ++i)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void TestBubbleSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    BubbleSort(arr,size);
    PrintArr(arr,size);
}

void TestSelectSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    SelectSort(arr,size);
    PrintArr(arr,size);
}

void TestInsertSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    InsertSort(arr,size);
    PrintArr(arr,size);
}

void TestHeapSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    HeapSort(arr,size);
    PrintArr(arr,size);
}

void TestShellSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    ShellSort(arr,size);
    PrintArr(arr,size);
}

void TestMergeSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    MergeSort(arr,size);
    PrintArr(arr,size);
}

void TestMergeSortByLoop()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    MergeSortByLoop(arr,size);
    PrintArr(arr,size);
}

void TestQuickSort()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    QuickSort(arr,size);
    PrintArr(arr,size);
}

void TestQuickSortByLoop()
{
    TEST_HEADER;
    int arr[] = {5,4,6,3,9,1,2,7,0,8};
    int size = sizeof(arr)/sizeof(arr[0]);
    QuickSortByLoop(arr,size);
    PrintArr(arr,size);
}

int main()
{
    TestBubbleSort();
    TestSelectSort();
    TestInsertSort();
    TestHeapSort();
    TestShellSort();
    TestMergeSort();
    TestMergeSortByLoop();
    TestQuickSort();
    TestQuickSortByLoop();
    return 0;
}

#endif
