#include <iostream>

using namespace std;

typedef int ElementType;
typedef struct tagHeapNode
{
    ElementType data;
} HeapNode;
typedef struct tagHeap
{
    HeapNode *nodes;
    int capacity;
    int usedSize;
} Heap;

Heap *Heap_Create(int initialsize);
void Heap_Destroy(Heap *heap);
void Heap_Insert(Heap *heap, ElementType newData);
void Heap_DeleteMin(Heap *heap, HeapNode *root);
int Heap_GetParent(int index);
int Heap_GetLeftChild(int index);
void Heap_SwapNodes(Heap *heap, int index1, int index2);
void Heap_PrintNodes(Heap *heap);

Heap *Heap_Create(int initialsize)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->capacity = initialsize;
    heap->usedSize = 0;
    heap->nodes = (HeapNode *)malloc(sizeof(HeapNode) * initialsize);

    return heap;
}
void Heap_Destroy(Heap *heap)
{
    free(heap->nodes);
    free(heap);
}
int Heap_GetParent(int index)
{
    return (index - 1) / 2;
}
int Heap_GetLeftChild(int index)
{
    return (index * 2) + 1;
}
void Heap_SwapNodes(Heap *heap, int index1, int index2)
{
    int temp = heap->nodes[index1].data;
    heap->nodes[index1].data = heap->nodes[index2].data;
    heap->nodes[index2].data = temp;
}
void Heap_Insert(Heap *heap, ElementType newData)
{
    HeapNode newNode;
    newNode.data = newData;

    int position = heap->usedSize++;
    int parentPosition = Heap_GetParent(position);

    heap->nodes[position] = newNode;

    if (heap->usedSize == heap->capacity)
    {
        heap->capacity *= 2;
        heap->nodes = (HeapNode *)realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    while (position > 0 && heap->nodes[parentPosition].data > heap->nodes[position].data)
    {
        Heap_SwapNodes(heap, position, parentPosition);
        position = parentPosition;
        parentPosition = Heap_GetParent(parentPosition);
    }
}
void Heap_DeleteMin(Heap *heap, HeapNode *root)
{
    int parent = 0;
    int left = 0;
    int right = 0;
    memcpy(root, &heap->nodes[0], sizeof(HeapNode));
    memset(&heap->nodes[0], 0, sizeof(HeapNode));
    heap->usedSize--;
    Heap_SwapNodes(heap, 0, heap->usedSize);

    while (true)
    {
        left = Heap_GetLeftChild(parent);
        right = left + 1;
        if (left >= heap->usedSize)
            break;

        if (right >= heap->usedSize)
        {
            if (heap->nodes[left].data < heap->nodes[parent].data)
            {
                Heap_SwapNodes(heap, parent, left);
            }
            break;
        }

        if (heap->nodes[left].data > heap->nodes[right].data)
        {
            Heap_SwapNodes(heap, parent, right);
            parent = right;
        }
        else
        {
            Heap_SwapNodes(heap, parent, left);
            parent = left;
        }
    }
}

void Heap_PrintNodes(Heap *heap)
{
    for (int i = 0; i < heap->usedSize; ++i)
    {
        cout << heap->nodes[i].data << ",";
    }
    cout << endl;
}

void HeapTest()
{
    Heap *h = Heap_Create(3);
    HeapNode minNode;

    Heap_Insert(h, 12);
    Heap_Insert(h, 87);
    Heap_Insert(h, 111);
    Heap_Insert(h, 34);
    Heap_Insert(h, 16);
    Heap_Insert(h, 75);
    Heap_PrintNodes(h);

    Heap_DeleteMin(h, &minNode);
    Heap_PrintNodes(h);

    Heap_DeleteMin(h, &minNode);
    Heap_PrintNodes(h);

    Heap_DeleteMin(h, &minNode);
    Heap_PrintNodes(h);

    Heap_DeleteMin(h, &minNode);
    Heap_PrintNodes(h);

    Heap_DeleteMin(h, &minNode);
    Heap_PrintNodes(h);

    Heap_DeleteMin(h, &minNode);
    Heap_PrintNodes(h);
}

typedef int PriorityType;
typedef struct
{
    PriorityType priority;
    void *data;
} PQNode;
typedef struct
{
    PQNode *nodes;
    int capacity;
    int usedSize;
} PriorityQueue;

PriorityQueue *PQ_Create(int initialsize);
void PQ_Destroy(PriorityQueue *pq);
void PQ_Enqueue(PriorityQueue *pq, PQNode newData);
void PQ_Dequeue(PriorityQueue *pq, PQNode *root);
int PQ_GetParent(int index);
int PQ_GetLeftChild(int index);
void PQ_SwapNodes(PriorityQueue *pq, int index1, int index2);
int PQ_IsEmpty(PriorityQueue *pq);

PriorityQueue *PQ_Create(int initialsize)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->capacity = initialsize;
    pq->usedSize = 0;
    pq->nodes = (PQNode *)malloc(sizeof(PQNode) * initialsize);

    return pq;
}
void PQ_Destroy(PriorityQueue *pq)
{
    free(pq->nodes);
    free(pq);
}
int PQ_GetParent(int index)
{
    return (index - 1) / 2;
}
int PQ_GetLeftChild(int index)
{
    return (index * 2) + 1;
}
void PQ_Enqueue(PriorityQueue *pq, PQNode newNode)
{
    int position = pq->usedSize++;
    int parentPosition = PQ_GetParent(position);

    pq->nodes[position] = newNode;

    if (pq->usedSize == pq->capacity)
    {
        pq->capacity *= 2;
        pq->nodes = (PQNode *)realloc(pq->nodes, sizeof(PQNode) * pq->capacity);
    }

    while (position > 0 && pq->nodes[parentPosition].priority > pq->nodes[position].priority)
    {
        PQ_SwapNodes(pq, position, parentPosition);
        position = parentPosition;
        parentPosition = PQ_GetParent(parentPosition);
    }
}
void PQ_Dequeue(PriorityQueue *pq, PQNode *root)
{
    int parent = 0;
    int left = 0;
    int right = 0;
    memcpy(root, &pq->nodes[0], sizeof(PQNode));
    memset(&pq->nodes[0], 0, sizeof(PQNode));
    pq->usedSize--;
    PQ_SwapNodes(pq, 0, pq->usedSize);

    while (true)
    {
        left = PQ_GetLeftChild(parent);
        right = left + 1;
        if (left >= pq->usedSize)
            break;

        if (right >= pq->usedSize)
        {
            if (pq->nodes[left].priority < pq->nodes[parent].priority)
            {
                PQ_SwapNodes(pq, parent, left);
            }
            break;
        }

        if (pq->nodes[left].priority > pq->nodes[right].priority)
        {
            PQ_SwapNodes(pq, parent, right);
            parent = right;
        }
        else
        {
            PQ_SwapNodes(pq, parent, left);
            parent = left;
        }
    }
}
void PQ_SwapNodes(PriorityQueue *pq, int index1, int index2)
{
    PQNode *temp = (PQNode *)malloc(sizeof(PQNode));
    memcpy(temp, &(pq->nodes[index1]), sizeof(PQNode));
    memcpy(&(pq->nodes[index1]), &(pq->nodes[index2]), sizeof(PQNode));
    memcpy(&(pq->nodes[index2]), temp, sizeof(PQNode));
    free(temp);
}
int PQ_IsEmpty(PriorityQueue *pq)
{
    return pq->usedSize == 0;
}
void PrintNode(PQNode *node)
{
    cout << node->priority << " : " << (char *)node->data << endl;
}
void PQ_Test()
{
    PriorityQueue *pq = PQ_Create(3);
    PQNode poped;
    PQNode nodes[7] = {
        {34, (void *)"코딩"},
        {12, (void *)"고객미팅"},
        {87, (void *)"커피타기"},
        {45, (void *)"문서작성"},
        {35, (void *)"디버깅"},
        {66, (void *)"이닦기"}};

    PQ_Enqueue(pq, nodes[0]);
    PQ_Enqueue(pq, nodes[1]);
    PQ_Enqueue(pq, nodes[2]);
    PQ_Enqueue(pq, nodes[3]);
    PQ_Enqueue(pq, nodes[4]);
    PQ_Enqueue(pq, nodes[5]);

    while (!PQ_IsEmpty(pq))
    {
        PQ_Dequeue(pq, &poped);
        PrintNode(&poped);
    }
    PQ_Destroy(pq);
}

void Test()
{
    PQ_Test();
}