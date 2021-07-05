#include <iostream>

using namespace std;

typedef int ElementType;

typedef struct TagNode
{
	ElementType data;
	struct TagNode *nextNode;
	struct TagNode *prevNode;
} Node;

Node *SLL_CreateNode(ElementType newData)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = newData;
	newNode->nextNode = NULL;

	return newNode;
}

void SLL_DestroyNode(Node *node)
{
	free(node);
}

void SLL_AppendNode(Node **head, Node *newNode)
{
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		Node *tail = *head;
		while (tail->nextNode != NULL)
		{
			tail = tail->nextNode;
		}
		tail->nextNode = newNode;
	}
}

void SLL_InsertAfter(Node *current, Node *newNode)
{
	newNode->nextNode = current->nextNode;
	current->nextNode = newNode;
}

void SLL_InsertNewHead(Node **head, Node *newNode)
{
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		newNode->nextNode = *head;
		*head = newNode;
	}
}

void SLL_RemoveNode(Node **head, Node *remove)
{
	if (*head == remove)
	{
		*head = remove->nextNode;
	}
	else
	{
		Node *current = *head;
		while (current != NULL && current->nextNode != remove)
		{
			current = current->nextNode;
		}
		if (current != NULL)
		{
			current->nextNode = remove->nextNode;
		}
	}
}

Node *SLL_GetNodeAt(Node *head, int location)
{
	Node *tail = head;

	while (tail != NULL && location-- > 0)
	{
		tail = tail->nextNode;
	}

	return tail;
}

int SLL_GetNodeCount(Node *head)
{
	int count = 0;
	Node *current = head;

	while (current != NULL)
	{
		current = current->nextNode;
		count++;
	}

	return count;
}

void SLL_Test()
{
	int i = 0;
	int count = 0;
	Node *list = NULL;
	Node *current = NULL;
	Node *newNode = NULL;

	for (i = 0; i < 5; ++i)
	{
		newNode = SLL_CreateNode(i);
		SLL_AppendNode(&list, newNode);
	}

	newNode = SLL_CreateNode(-1);
	SLL_InsertNewHead(&list, newNode);

	newNode = SLL_CreateNode(-2);
	SLL_InsertNewHead(&list, newNode);

	count = SLL_GetNodeCount(list);

	for (i = 0; i < count; ++i)
	{
		current = SLL_GetNodeAt(list, i);
		cout << current->data << endl;
	}

	for (i = 0; i < count; ++i)
	{
		current = SLL_GetNodeAt(list, i);
		if (current != NULL)
		{
			SLL_RemoveNode(&list, current);
			SLL_DestroyNode(current);
		}
	}
}
// DLL

Node *DLL_CreateNode(ElementType newData)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = newData;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;

	return newNode;
}

void DLL_DestroyNode(Node *node)
{
	free(node);
}

void DLL_AppendNode(Node **head, Node *newNode)
{
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		Node *tail = *head;
		while (tail->nextNode != NULL)
		{
			tail = tail->nextNode;
		}
		tail->nextNode = newNode;
		newNode->prevNode = tail;
	}
}

Node *DLL_GetNodeAt(Node *head, int location)
{
	Node *tail = head;

	while (tail != NULL && location-- > 0)
	{
		tail = tail->nextNode;
	}

	return tail;
}

void DLL_RemoveNode(Node **head, Node *remove)
{
	if (*head == remove)
	{
		*head = remove->nextNode;
		if (*head != NULL)
		{
			(*head)->prevNode = NULL;
		}
		remove->nextNode = NULL;
		remove->prevNode = NULL;
	}
	else
	{
		remove->prevNode->nextNode = remove->nextNode;
		if (remove->nextNode != NULL)
		{
			remove->nextNode->prevNode = remove->prevNode;
		}
		remove->prevNode = NULL;
		remove->nextNode = NULL;
	}
}

void DLL_InsertAfter(Node *current, Node *newNode)
{
	newNode->nextNode = current->nextNode;
	newNode->prevNode = current;
	if (current->nextNode != NULL)
	{
		current->nextNode->prevNode = newNode;
	}
	current->nextNode = newNode;
}

int DLL_GetNodeCount(Node *head)
{
	int count = 0;
	Node *current = head;

	while (current != NULL)
	{
		current = current->nextNode;
		count++;
	}

	return count;
}

// CLL


int main(void)
{
	return 0;
}