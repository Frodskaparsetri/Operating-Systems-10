#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int unsortedList[] = {7, 12, 19, 3, 18, 4, 2, 6, 15, 8};
int *mergeList;

typedef struct
{
    int start;
    int width;
} sortParams;

void bubbleSort(int list[], int offset, int n);
void *sortThread(void *params);
void *mergeThread(void *params);

int main(int argc, char *argv[])
{
    // Define list size and list split
    int listSize = sizeof(unsortedList) / sizeof(int);
    int halfSize = (int)ceilf((float)(listSize) / 2.0f);

    // Define sort params
    sortParams left, right;
    left.start = 0;
    left.width = halfSize;

    right.start = halfSize;
    right.width = listSize;

    printf("Original: ");
    for (int i = 0; i < listSize; i++)
    {
        printf("%d ", unsortedList[i]);
    }
    printf("\n");

    // Start Sort Threads...
    pthread_t leftTid, rightTid, mergeTid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    // execute left and right sorting
    pthread_create(&leftTid, &attr, sortThread, &left);
    pthread_create(&rightTid, &attr, sortThread, &right);

    pthread_join(leftTid, NULL);
    pthread_join(rightTid, NULL);

    // execute merge
    pthread_create(&mergeTid, &attr, mergeThread, NULL);
    pthread_join(mergeTid, NULL);

    printf("After Sort Thread: ");
    for (int i = 0; i < listSize; i++)
    {
        printf("%d ", unsortedList[i]);
    }
    printf("\n");

    printf("After Merged Thread: ");
    for (int i = 0; i < listSize; i++)
    {
        printf("%d ", mergeList[i]);
    }
    printf("\n");

    free(mergeList);

    return 0;
}

void *sortThread(void *params)
{
    sortParams *sort = params;
    bubbleSort(unsortedList, sort->start, sort->width);

    pthread_exit(0);
}

void *mergeThread(void *params)
{
    int size = sizeof(unsortedList);
    mergeList = (int *)malloc(size);
    memcpy(mergeList, unsortedList, size);

    int width = size / sizeof(unsortedList[0]);
    bubbleSort(mergeList, 0, width);

    pthread_exit(0);
}

// https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(int list[], int offset, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = offset; j < n - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                int temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}