#include <iostream>

using namespace std;

typedef int ElementType;

typedef struct tagNode
{
    ElementType data;
} Node;

typedef struct tagCircularQueue
{
    int capacity;
    int front;
    int rear;
    Node *nodes;
} CircularQueue;

void CQ_CreateQueue(CircularQueue **queue, int capacity);
void CQ_DestroyQueue(CircularQueue *queue);
void CQ_EnQueue(CircularQueue *queue, ElementType data);
ElementType CQ_DeQueue(CircularQueue *queue);
int CQ_GetSize(CircularQueue *queue);
int CQ_IsEmpty(CircularQueue *queue);
int CQ_IsFull(CircularQueue *queue);

void CQ_CreateQueue(CircularQueue **queue, int capacity)
{
    *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    (*queue)->nodes = (Node *)malloc(sizeof(Node) * (capacity + 1));
    (*queue)->capacity = capacity;
    (*queue)->front = 0;
    (*queue)->rear = 0;
}

void CQ_DestroyQueue(CircularQueue *queue)
{
    free(queue->nodes);
    free(queue);
}

void CQ_EnQueue(CircularQueue *queue, ElementType data)
{
    int position = 0;
    if (queue->rear == queue->capacity)
    {
        position = queue->rear;
        queue->rear = 0;
    }
    else
    {
        position = queue->rear++;
    }
    queue->nodes[position].data = data;
}

ElementType CQ_DeQueue(CircularQueue *queue)
{
    int position = queue->front;
    if (queue->front == queue->capacity)
    {
        queue->front = 0;
    }
    else
    {
        queue->front++;
    }
    return queue->nodes[position].data;
}

int CQ_GetSize(CircularQueue *queue)
{
    if (queue->front < queue->rear)
    {
        return queue->rear - queue->front;
    }
    else
    {
        return queue->capacity - (queue->front - queue->rear) + 1;
    }
}

int CQ_IsEmpty(CircularQueue *queue)
{
    return queue->rear == queue->front;
}

int CQ_IsFull(CircularQueue *queue)
{
    if (queue->front < queue->rear)
    {
        return (queue->rear - queue->front) == queue->capacity;
    }
    else
    {
        return (queue->rear + 1) == queue->front;
    }
}

void CQ_Test()
{
    int i;
    CircularQueue *queue;
    CQ_CreateQueue(&queue, 10);

    CQ_EnQueue(queue, 1);
    CQ_EnQueue(queue, 2);
    CQ_EnQueue(queue, 3);
    CQ_EnQueue(queue, 4);

    for (i = 0; i < 3; ++i)
    {
        cout << "dequeue : " << CQ_DeQueue(queue) << endl;
    }

    i = 100;
    while (CQ_IsFull(queue) == 0)
    {
        CQ_EnQueue(queue, i++);
    }
    cout << "size : " << CQ_GetSize(queue) << endl;

    while (CQ_IsEmpty(queue) == 0)
    {
        cout << CQ_DeQueue(queue) << endl;
    }

    CQ_DestroyQueue(queue);
}
