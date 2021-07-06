#include <iostream>

using namespace std;

typedef int ElementType;

typedef struct tagNode
{
    ElementType data;
} Node;

typedef struct tagArrayStack
{
    int capacity;
    int top;
    Node *nodes;
} ArrayStack;

void AS_CreateStack(ArrayStack **stack, int capacity)
{
    *stack = (ArrayStack *)malloc(sizeof(ArrayStack));
    (*stack)->nodes = (Node *)malloc(sizeof(Node));
    (*stack)->capacity = capacity;
    (*stack)->top = 0;
}

void AS_DestroyStack(ArrayStack *stack)
{
    free(stack->nodes);
    free(stack);
}

void AS_Push(ArrayStack *stack, ElementType data)
{
    int position = stack->top;
    stack->nodes[position].data = data;
    stack->top++;
}

ElementType AS_Pop(ArrayStack *stack)
{
    int position = --stack->top;
    return stack->nodes[position].data;
}

ElementType AS_Top(ArrayStack *stack)
{
    int position = stack->top - 1;
    return stack->nodes[position].data;
}

int AS_GetSize(ArrayStack *stack)
{
    return stack->top;
}

int AS_IsEmpty(ArrayStack *stack)
{
    return (stack->top == 0);
}

int AS_IsFull(ArrayStack *stack)
{
    return (stack->top == stack->capacity);
}

void AS_Test()
{
    int i = 0;
    ArrayStack *stack = NULL;
    AS_CreateStack(&stack, 10);

    AS_Push(stack, 3);
    AS_Push(stack, 37);
    AS_Push(stack, 11);
    AS_Push(stack, 12);

    cout
        << "capacity "
        << stack->capacity
        << " size : "
        << AS_GetSize(stack)
        << " top: "
        << AS_Top(stack)
        << endl;

    for (i = 0; i < 4; ++i)
    {
        if (AS_IsEmpty(stack))
        {
            break;
        }
        cout << AS_Pop(stack) << endl;
    }
    AS_DestroyStack(stack);
}

/// linked stack

typedef struct lsTagNode
{
    char *data;
    struct lsTagNode *nextNode;
    struct lsTagNode *prevNode;
} LSNode;

typedef struct tagLinkedListStack
{
    LSNode *top;
    int size;
} LinkedListStack;

LSNode *LLS_Top(LinkedListStack *stack)
{
    return stack->top;
}
int LLS_GetSize(LinkedListStack *stack)
{
    return stack->size;
}
int LLS_IsEmpty(LinkedListStack *stack)
{
    return (stack->size == 0);
}

void LLS_CreateStack(LinkedListStack **stack)
{
    *stack = (LinkedListStack *)malloc(sizeof(LinkedListStack));
    (*stack)->top = NULL;
    (*stack)->size = 0;
}

void LLS_Push(LinkedListStack *stack, LSNode *newNode)
{
    stack->size++;
    if (stack->top == NULL)
    {
        stack->top = newNode;
    }
    else
    {
        stack->top->nextNode = newNode;
        newNode->prevNode = stack->top;
        stack->top = newNode;
    }
}

LSNode *LLS_Pop(LinkedListStack *stack)
{
    stack->size--;
    if (stack->size < 0)
    {
        stack->size = 0;
    }

    LSNode *poped = stack->top;
    if (poped != NULL)
    {
        stack->top = poped->prevNode;
    }
    return poped;
}

void LLS_DestroyNode(LSNode *node)
{
    free(node->data);
    free(node);
}

void LLS_DestoryStack(LinkedListStack *stack)
{
    while (!LLS_IsEmpty(stack))
    {
        LSNode *poped = LLS_Pop(stack);
        LLS_DestroyNode(poped);
    }
    free(stack);
}

LSNode *LLS_CreateNode(char *data)
{
    LSNode *newNode = (LSNode *)malloc(sizeof(LSNode));
    newNode->nextNode = NULL;
    newNode->prevNode = NULL;
    newNode->data = (char *)malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(newNode->data, data);

    return newNode;
}

typedef enum
{
    LEFT_PARENTHESIS = '(',
    RIGHT_PARENTHESIS = ')',
    PLUS = '+',
    MULTIPLY = '*',
    MINUS = '-',
    DIVIDE = '/',
    SPACE = ' ',
    OPERAND
} SYMBOL;

char NUMBER[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};

int IsNumber(char cipher)
{
    int len = sizeof(NUMBER);
    for (int i = 0; i < len; ++i)
    {
        if (cipher == NUMBER[i])
        {
            return 1;
        }
    }
    return 0;
}

unsigned int GetNextToken(char *expression, char *token, int *type)
{
    unsigned int i = 0;
    for (i = 0; expression[i] != 0; i++)
    {
        token[i] = expression[i];
        if (IsNumber(expression[i]) == 1)
        {
            *type = OPERAND;
            if (IsNumber(expression[i + 1]) != 1)
            {
                break;
            }
        }
        else
        {
            *type = expression[i];
            break;
        }
    }
    token[++i] = '\0';
    return i;
}

int GetPriority(char op, int inStack)
{
    int priority = -1;

    switch (op)
    {
    case LEFT_PARENTHESIS:
        if (inStack)
        {
            priority = 3;
        }
        else
        {
            priority = 0;
        }
        break;
    case MULTIPLY:
    case DIVIDE:
        priority = 1;
        break;
    case PLUS:
    case MINUS:
        priority = 2;
        break;
    }
    return priority;
}

int IsPrior(char operator1, char operator2)
{
    return (GetPriority(operator1, 1) > GetPriority(operator2, 0));
}
void GetPosfix(char *infixExpression, char *postfixExpression)
{
    LinkedListStack *stack = NULL;
    LLS_CreateStack(&stack);

    unsigned int i = 0;
    unsigned int len = strlen(infixExpression);

    char token[32];
    LSNode *poped;
    int type = -1;

    while (i < len)
    {
        i += GetNextToken(&infixExpression[i], token, &type);
        if (type == OPERAND)
        {
            strcat(postfixExpression, token);
            strcat(postfixExpression, " ");
        }
        else if (type == RIGHT_PARENTHESIS)
        {
            while (!LLS_IsEmpty(stack))
            {
                poped = LLS_Pop(stack);
                if (poped->data[0] == LEFT_PARENTHESIS)
                {
                    LLS_DestroyNode(poped);
                    break;
                }
                else
                {
                    strcat(postfixExpression, poped->data);
                    LLS_DestroyNode(poped);
                }
            }
        }
        else
        {
            while (!LLS_IsEmpty(stack) && !IsPrior(stack->top->data[0], token[0]))
            {
                poped = LLS_Pop(stack);
                if (poped->data[0] != LEFT_PARENTHESIS)
                {
                    strcat(postfixExpression, poped->data);
                }
                LLS_DestroyNode(poped);
            }
            LLS_Push(stack, LLS_CreateNode(token));
        }
    }
    while (!LLS_IsEmpty(stack))
    {
        poped = LLS_Pop(stack);
        if (poped->data[0] != LEFT_PARENTHESIS)
        {
            strcat(postfixExpression, poped->data);
        }
        LLS_DestroyNode(poped);
    }
}

double GetOperaterResult(int type, double left, double right)
{
    double result = 0.0;

    switch (type)
    {
    case PLUS:
        result = left + right;
        break;
    case MINUS:
        result = left - right;
        break;
    case MULTIPLY:
        result = left * right;
        break;
    case DIVIDE:
        result = left / right;
        break;
    }
    return result;
}

double Calculate(char *postfixExpression)
{
    LinkedListStack *stack = NULL;
    LLS_CreateStack(&stack);
    LSNode *poped = NULL;
    char token[32];
    int type = -1;
    char resultStr[32];
    double result;

    unsigned int i = 0;
    unsigned int len = strlen(postfixExpression);
    while (i < len)
    {
        i += GetNextToken(&postfixExpression[i], token, &type);
        if (type == SPACE)
        {
            continue;
        }
        else if (type == OPERAND)
        {
            LLS_Push(stack, LLS_CreateNode(token));
        }
        else
        {
            poped = LLS_Pop(stack);
            double OP_right = atof(poped->data);
            LLS_DestroyNode(poped);

            poped = LLS_Pop(stack);
            double OP_left = atof(poped->data);
            LLS_DestroyNode(poped);

            result = GetOperaterResult(type, OP_left, OP_right);
            gcvt(result, 10, resultStr);
            LLS_Push(stack, LLS_CreateNode(resultStr));
        }
    }

    poped = LLS_Pop(stack);
    result = atof(poped->data);
    LLS_DestroyNode(poped);
    LLS_DestoryStack(stack);

    return result;
}

void CalculateTest(char *expression)
{
    char infixExpression[100];
    char postfixExpression[100];

    memset(infixExpression, 0, sizeof(infixExpression));
    memset(postfixExpression, 0, sizeof(postfixExpression));

    strcpy(infixExpression, expression);

    GetPosfix(infixExpression, postfixExpression);

    cout << "infixExpression : " << infixExpression << endl;
    cout << "PostfixExpression : " << postfixExpression << endl;
    cout << "Result : " << Calculate(postfixExpression) << endl;
}

void CalculateTestCase()
{
    char testStr[] = "1+3.334/(4.28*(110-7729))";
    CalculateTest(testStr);
}