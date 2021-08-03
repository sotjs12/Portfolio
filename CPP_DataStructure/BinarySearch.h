#include <iostream>

using namespace std;

typedef struct
{
    int number;
    double score;
} Score;

Score *BinarySearch(Score scoreList[], int size, double target)
{
    int left = 0;
    int right = size - 1;
    int pivot = 0;
    while (left < right)
    {
        pivot = (left + right) / 2;
        if (scoreList[pivot].score == target)
        {
            return &(scoreList[pivot]);
        }
        else if (scoreList[pivot].score < target)
        {
            right = pivot - 1;
        }
        else
        {
            left = pivot + 1;
        }
    }
    return NULL;
}

typedef int ElementType;

typedef struct tagBSTNode
{
    struct tagBSTNode *left;
    struct tagBSTNode *right;
    ElementType data;
} BSTNode;

BSTNode *BST_CreateNode(ElementType data);
void BST_DestroyNode(BSTNode *node);
void BST_DestroyTree(BSTNode *tree);

BSTNode *BST_SearchNode(BSTNode *tree, ElementType target);
BSTNode *BST_SearchMinNode(BSTNode *tree);
void BST_InsertNode(BSTNode *tree, BSTNode *node);
BSTNode *BST_RemoveNode(BSTNode *tree, BSTNode *parent, ElementType target);
void BST_InorderPrintTree(BSTNode *node);

BSTNode *BST_CreateNode(ElementType data)
{
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = data;

    return newNode;
}
void BST_DestroyNode(BSTNode *node)
{
    free(node);
}
void BST_DestroyTree(BSTNode *tree)
{
    if (tree == NULL)
    {
        return;
    }
    BST_DestroyTree(tree->left);
    BST_DestroyTree(tree->right);
    BST_DestroyNode(tree);
}

BSTNode *BST_SearchNode(BSTNode *tree, ElementType target)
{
    if (target == tree->data)
    {
        return tree;
    }
    else if (tree->data < target)
    {
        return BST_SearchNode(tree->right, target);
    }
    else
    {
        return BST_SearchNode(tree->left, target);
    }
}

BSTNode *BST_SearchMinNode(BSTNode *tree)
{
    if (tree->left == NULL)
    {
        return tree;
    }
    else
    {
        return BST_SearchMinNode(tree->left);
    }
}

void BST_InsertNode(BSTNode *tree, BSTNode *node)
{
    if (tree->data < node->data)
    {
        if (tree->right == NULL)
        {
            tree->right = node;
        }
        else
        {
            BST_InsertNode(tree->right, node);
        }
    }
    else
    {
        if (tree->left == NULL)
        {
            tree->left = node;
        }
        else
        {
            BST_InsertNode(tree->left, node);
        }
    }
}
BSTNode *BST_RemoveNode(BSTNode *tree, BSTNode *parent, ElementType target)
{
    BSTNode *removed;
    if (tree == NULL)
    {
        return removed;
    }

    if (tree->data == target)
    {
        removed = tree;
        if (tree->left == NULL && tree->right == NULL)
        {
            if (parent->left == tree)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        else
        {
            if (tree->left != NULL && tree->right != NULL)
            {
                BSTNode *minNode = BST_SearchMinNode(tree);
                removed = BST_RemoveNode(tree, NULL, minNode->data);
                tree->data = minNode->data;
            }
            else
            {
                BSTNode *temp;
                if (tree->left != NULL)
                {
                    temp = tree->left;
                }
                else
                {
                    temp = tree->right;
                }
                if (parent->left == tree)
                {
                    parent->left = temp;
                }
                else
                {
                    parent->right = temp;
                }
            }
        }
    }
    else if (tree->data < target)
    {
        removed = BST_RemoveNode(tree->right, tree, target);
    }
    else
    {
        removed = BST_RemoveNode(tree->left, tree, target);
    }
    return removed;
}
void BST_InorderPrintTree(BSTNode *node)
{
    if (node != NULL)
    {
        BST_InorderPrintTree(node->left);
        cout << node->data << " ";
        BST_InorderPrintTree(node->right);
    }
}
void TestBST()
{
    BSTNode *tree = BST_CreateNode(123);
    BSTNode *node = NULL;

    BST_InsertNode(tree, BST_CreateNode(22));
    BST_InsertNode(tree, BST_CreateNode(9918));
    BST_InsertNode(tree, BST_CreateNode(424));
    BST_InsertNode(tree, BST_CreateNode(17));
    BST_InsertNode(tree, BST_CreateNode(3));
    BST_InsertNode(tree, BST_CreateNode(98));
    BST_InsertNode(tree, BST_CreateNode(34));
    BST_InsertNode(tree, BST_CreateNode(760));
    BST_InsertNode(tree, BST_CreateNode(317));
    BST_InsertNode(tree, BST_CreateNode(1));

    BST_InorderPrintTree(tree);
    cout << endl;

    node = BST_RemoveNode(tree, NULL, 98);
    BST_DestroyNode(node);

    BST_InorderPrintTree(tree);
    cout << endl;

    BST_InsertNode(tree, BST_CreateNode(111));
    BST_InorderPrintTree(tree);

    BST_DestroyTree(tree);
}


void Test()
{
    TestBST();
}