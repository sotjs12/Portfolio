#include <iostream>
#include "LinkedList.h"

using namespace std;

enum VisitMode
{
    Visited,
    NotVisited
};

typedef int ElementType;
typedef struct tagVertex
{
    ElementType data;
    int visited;
    int index;

    struct tagVertex *next;
    struct tagEdge *adjacencyList;
} Vertex;
typedef struct tagEdge
{
    int weight;
    struct tagEdge *next;
    Vertex *from;
    Vertex *target;
} Edge;

typedef struct
{
    Vertex *vertices;
    int vertexCount;
} Graph;

Graph *CreateGraph();
void DestroyGraph(Graph *g);

Vertex *CreateVertex(ElementType data);
void DestroyVertex(Vertex *v);

Edge *CreateEdge(Vertex *from, Vertex *target, int weight);
void DestroyEdge(Edge *e);

void AddVertex(Graph *g, Vertex *v);
void AddEdge(Vertex *v, Edge *e);
void PrintGraph(Graph *g);

Graph *CreateGraph()
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->vertexCount = 0;
    g->vertices = NULL;
    return g;
}
void DestroyGraph(Graph *g)
{
    Vertex *temp;
    while (g->vertices != NULL)
    {
        temp = g->vertices->next;
        DestroyVertex(g->vertices);
        g->vertices = temp;
    }

    free(g);
}

Vertex *CreateVertex(ElementType data)
{
    Vertex *v = (Vertex *)malloc(sizeof(Vertex));
    v->data = data;
    v->adjacencyList = NULL;
    v->index = -1;
    v->next = NULL;
    v->visited = NotVisited;

    return v;
}
void DestroyVertex(Vertex *v)
{
    Edge *temp;
    while (v->adjacencyList != NULL)
    {
        temp = v->adjacencyList->next;
        DestroyEdge(v->adjacencyList);
        v->adjacencyList = temp;
    }

    free(v);
}

Edge *CreateEdge(Vertex *from, Vertex *target, int weight)
{
    Edge *e = (Edge *)malloc(sizeof(Edge));
    e->from = from;
    e->target = target;
    e->weight = weight;
    e->next = NULL;

    return e;
}
void DestroyEdge(Edge *e)
{
    free(e);
}

void AddVertex(Graph *g, Vertex *v)
{
    if (g->vertices == NULL)
    {
        g->vertices = v;
    }
    else
    {
        Vertex *lastV = g->vertices;
        while (lastV->next != NULL)
            lastV = lastV->next;

        lastV->next = v;
    }
    v->index = g->vertexCount++;
}
void AddEdge(Vertex *v, Edge *e)
{
    if (v->adjacencyList == NULL)
    {
        v->adjacencyList = e;
    }
    else
    {
        Edge *lastE = v->adjacencyList;
        while (lastE->next != NULL)
            lastE = lastE->next;
        lastE->next = e;
    }
}
void PrintGraph(Graph *g)
{
    if (g->vertices == NULL)
        return;

    Vertex *v = g->vertices;
    Edge *e = NULL;
    while (v != NULL)
    {
        cout << (char)v->data << " : ";
        e = v->adjacencyList;
        while (e != NULL)
        {
            cout << (char)e->target->data << "[" << e->weight << "] ";
            e = e->next;
        }
        if (v->adjacencyList != NULL)
            cout << endl;
        v = v->next;
    }
    cout << endl;
}

void DFS(Vertex *v)
{
    Edge *e;
    cout << (char)v->data << " ";
    v->visited = Visited;
    e = v->adjacencyList;
    while (e != NULL)
    {
        if (e->target != NULL && e->target->visited == NotVisited)
            DFS(e->target);
        e = e->next;
    }
}

void Test_Graph_0()
{
    Graph *g = CreateGraph();

    Vertex *v1 = CreateVertex('1');
    Vertex *v2 = CreateVertex('2');
    Vertex *v3 = CreateVertex('3');
    Vertex *v4 = CreateVertex('4');
    Vertex *v5 = CreateVertex('5');

    AddVertex(g, v1);
    AddVertex(g, v2);
    AddVertex(g, v3);
    AddVertex(g, v4);
    AddVertex(g, v5);

    AddEdge(v1, CreateEdge(v1, v2, 0));
    AddEdge(v1, CreateEdge(v1, v3, 0));
    AddEdge(v1, CreateEdge(v1, v4, 0));
    AddEdge(v1, CreateEdge(v1, v5, 0));

    AddEdge(v2, CreateEdge(v2, v1, 0));
    AddEdge(v2, CreateEdge(v2, v3, 0));
    AddEdge(v2, CreateEdge(v2, v5, 0));

    AddEdge(v3, CreateEdge(v3, v1, 0));
    AddEdge(v3, CreateEdge(v3, v2, 0));

    AddEdge(v4, CreateEdge(v4, v1, 0));
    AddEdge(v4, CreateEdge(v4, v5, 0));

    AddEdge(v5, CreateEdge(v5, v1, 0));
    AddEdge(v5, CreateEdge(v5, v2, 0));
    AddEdge(v5, CreateEdge(v5, v4, 0));

    PrintGraph(g);

    DestroyGraph(g);
}

void Test()
{
    Test_Graph_0();
}

void TopologicalSort(Vertex *v, Node **list);
void TS_DFS(Vertex *v, Node **list);

void TopologicalSort(Vertex *v, Node **list)
{
    while (v != NULL && v->visited != NotVisited)
    {
        TS_DFS(v, list);
        v = v->next;
    }
}
void TS_DFS(Vertex *v, Node **list)
{
    v->visited = Visited;
    Edge *e = v->adjacencyList;
    while (e != NULL)
    {
        if (e->target != NULL && e->target->visited == NotVisited)
            TS_DFS(e->target, list);
        e = e->next;
    }
    Node *leaf = SLL_CreateNode(v->data);
    SLL_InsertNewHead(list, leaf);
}