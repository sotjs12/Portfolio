#include <iostream>

using namespace std;

typedef struct tagNode
{
    char *data;
    struct tagNode *nextNode;
} Node;

typedef struct tagLinkedQueue
{
    Node *front;
    Node *rear;
    int count;
} LinkedQueue;

void LQ_CreateQueue(LinkedQueue **queue);
void LQ_DestroyQueue(LinkedQueue *queue);

Node *LQ_CreateNode(char *newData);
void LQ_DestroyNode(Node *node);

void LQ_EnQueue(LinkedQueue *queue, Node *node);
Node *LQ_DeQueue(LinkedQueue *queue);

int LQ_IsEmpty(LinkedQueue *queue);

void LQ_CreateQueue(LinkedQueue **queue)
{
    (*queue) = (LinkedQueue *)malloc(sizeof(LinkedQueue));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->count = 0;
}

void LQ_DestroyQueue(LinkedQueue *queue)
{
    Node *poped;
    while (!LQ_IsEmpty(queue))
    {
        poped = LQ_DeQueue(queue);
        LQ_DestroyNode(poped);
    }
    free(queue);
}

Node *LQ_CreateNode(char *newData)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = (char *)malloc(strlen(newData) + 1);

    strcpy(node->data, newData);
    node->nextNode = NULL;
    return node;
}
void LQ_DestroyNode(Node *node)
{
    free(node->data);
    free(node);
}

void LQ_EnQueue(LinkedQueue *queue, Node *node)
{
    if (queue->front == NULL)
    {
        queue->front = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->nextNode = node;
        queue->rear = node;
    }
    queue->count++;
}
Node *LQ_DeQueue(LinkedQueue *queue)
{
    Node *poped = queue->front;
    queue->front = poped->nextNode;
    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    queue->count--;
    return poped;
}

int LQ_IsEmpty(LinkedQueue *queue)
{
    return queue->front == NULL;
}

void Test()
{
    Node *poped;
    LinkedQueue *queue;

    LQ_CreateQueue(&queue);

    LQ_EnQueue(queue, LQ_CreateNode("abc"));
    LQ_EnQueue(queue, LQ_CreateNode("def"));
    LQ_EnQueue(queue, LQ_CreateNode("efg"));
    LQ_EnQueue(queue, LQ_CreateNode("hij"));

    cout << queue->count << endl;

    while (LQ_IsEmpty(queue) == 0)
    {
        poped = LQ_DeQueue(queue);
        cout << poped->data << endl;
        LQ_DestroyNode(poped);
    }
    LQ_DestroyQueue(queue);
}