#include <iostream>

using namespace std;

typedef char ElementType;
typedef struct tagSBTNode
{
    struct tagSBTNode *left;
    struct tagSBTNode *right;
    ElementType data;
} SBTNode;

SBTNode *SBT_CreateNode(ElementType newData);
void SBT_DestroyNode(SBTNode *node);
void SBT_DestroyTree(SBTNode *root);

void SBT_PreorderPrintTree(SBTNode *node);
void SBT_InorderPrintTree(SBTNode *node);
void SBT_PostorderPrintTree(SBTNode *node);

SBTNode *SBT_CreateNode(ElementType newData)
{
    SBTNode *node = (SBTNode *)malloc(sizeof(SBTNode));
    node->left = NULL;
    node->right = NULL;
    node->data = newData;

    return node;
}

void SBT_DestroyNode(SBTNode *node)
{
    free(node);
}
void SBT_DestroyTree(SBTNode *root)
{
    if (root == NULL)
    {
        return;
    }

    SBT_DestroyTree(root->left);
    SBT_DestroyTree(root->right);
    SBT_DestroyNode(root);
}

void SBT_PreorderPrintTree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << endl;
    SBT_PreorderPrintTree(node->left);
    SBT_PreorderPrintTree(node->right);
}

void SBT_InorderPrintTree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }
    SBT_PreorderPrintTree(node->left);
    cout << node->data << endl;
    SBT_PreorderPrintTree(node->right);
}

void SBT_PostorderPrintTree(SBTNode *node)
{
    if (node == NULL)
    {
        return;
    }
    SBT_PreorderPrintTree(node->left);
    SBT_PreorderPrintTree(node->right);
    cout << node->data << endl;
}