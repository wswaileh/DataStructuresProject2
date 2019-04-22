/**
 *
 * NUMBERS STACK FUNCTIONS
 *
 */

typedef struct Node* pointer;
typedef pointer numStack;
typedef pointer Position;

typedef struct Node
{
    float number;
    Position next;
};

numStack createNumStack()
{
    numStack s = (numStack) malloc(sizeof(struct Node));
    if (s!=NULL)
        s->next = NULL;
    else
        printf("Out Of Memory!\n");
    return s;
}

void pushNumber(numStack s,float x)
{
    Position p = (Position) malloc(sizeof(struct Node));
    p->number = x;
    p->next = s-> next;
    s->next = p;
}

float popNumber(numStack s)
{
    Position nodeToPop = s->next;
    s-> next = nodeToPop->next;
    float number = nodeToPop->number;
    free(nodeToPop);
    return number;
}

float getTopNumber(numStack s)
{
    return s->next->number;
}

int isNumStackEmpty(numStack s)
{
    return (s->next == NULL);
}

void deleteNumStack(numStack s)
{
    while (!isNumStackEmpty(s))
        popNumber(s);
    free(s);
}
/**
 *
 * FUNCTIONS FOR CHAR STACKS
 *
 */

typedef struct node* ptr;
typedef ptr stack ;
typedef ptr position;
typedef struct node
{
    char element ;
    position next;
};

stack createStack()
{
    stack s = (stack) malloc(sizeof(struct node));
    if (s!=NULL)
        s->next= NULL;
    else
        printf("out of memory\n");
    return s;
}

void push(stack s,char x)
{
    position p = (position) malloc(sizeof(struct node));
    p->element = x;
    p->next = s->next;
    s->next = p;
}

float pop(stack s)
{
    position nodeToPop = s->next;
    s-> next = nodeToPop->next;
    char x = nodeToPop->element;
    free(nodeToPop);
    return x;
}

char getTop(stack s)
{
    return s->next->element;
}

int isEmpty(stack s)
{
    return (s->next == NULL);
}

void deleteStack(stack s)
{
    while (!isEmpty(s))
        pop(s);
    free(s);
}
