#include "ccstack.h"
#include "common.h"
#include <string.h>

#define INITIAL_SIZE 100

int StCreate(CC_STACK **Stack)
{
    CC_STACK* stc = (CC_STACK*)malloc(sizeof(CC_STACK));
    if (stc == NULL)
    {
        return -1;
    }
    if (Stack == NULL)
    {
        return -1;
    }
    memset(stc, 0, sizeof(*stc));

    stc->Size = INITIAL_SIZE;
    stc->Count = 0;
    stc->Array = (int*)malloc(INITIAL_SIZE * sizeof(int));
    if (stc->Array == NULL)
    {
        free(stc);
        return -1;
    }

    *Stack = stc;
    return 0;
}

int StDestroy(CC_STACK **Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    if (Stack == NULL)
    {
        return -1;
    }
    free((*Stack)->Array);
    free(*Stack);
    return 0;
}


int StPush(CC_STACK *Stack, int Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);

    if (Stack == NULL)
    {
        return -1;
    }
    if ((Stack->Count + 1) >= Stack->Size)
    {
        //REALLOC
        int* tmp = (int*)realloc(Stack->Array, ((Stack->Size + INITIAL_SIZE) * sizeof(int)));
        if (tmp == NULL)
        {
            return -1;
        }
        Stack->Array = tmp;
        Stack->Size += INITIAL_SIZE;
    }
    int n = Stack->Count;
    Stack->Array[n] = Value;
    Stack->Count++;

    return 0;
}

int StPop(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Value == NULL)
    {
        return -1;
    }
    if (Stack == NULL)
    {
        return -1;
    }

    int* res = (int*)malloc(sizeof(int));
    if (res == NULL)
    {
        return -1;
    }
    int n = Stack->Count;
    *res = Stack->Array[n - 1];
    (Stack->Count)--;
    *Value = *res;
    return 0;
}

int StPeek(CC_STACK *Stack, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Stack == NULL)
    {
        return -1;
    }
    if (Stack->Count < 0)
    {
        return -1;
    }
    if (Value == NULL)
    {
        return -1;
    }
    int* res = (int*)malloc(sizeof(int));
    if (res == NULL)
    {
        return -1;
    }
    int n = Stack->Count;
    *res = Stack->Array[n - 1];
    *Value = *res;
    return 0;
}

int StIsEmpty(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    if (Stack == NULL)
    {
        return -1;
    }
    if (Stack->Count < 0)
    {
        return -1;
    }
    if (Stack->Count == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int StGetCount(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    if (Stack == NULL)
    {
        return -1;
    }
    if (Stack->Count < 0)
    {
        return -1;
    }
    return Stack->Count;
}

int StClear(CC_STACK *Stack)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    if (Stack == NULL)
    {
        return -1;
    }
    if (Stack->Count < 0)
    {
        return -1;
    }
    Stack->Count = 0;
    return 0;
}

int StPushStack(CC_STACK *Stack, CC_STACK *StackToPush)
{
    CC_UNREFERENCED_PARAMETER(Stack);
    CC_UNREFERENCED_PARAMETER(StackToPush);
    

    if (Stack == NULL)
    {
        return -1;
    }
    if (StackToPush == NULL)
    {
        return -1;
    }

    CC_STACK* tmp;
    StCreate(&tmp);
    if (tmp == NULL)
    {
        return -1;
    }
    int n;
    n = StackToPush->Count;
    for (int i = 0; i < n; i++)
    {
        int m;
        StPop(StackToPush, &m);
        StPush(tmp, m);
    }
    for (int i = 0; i < n; i++)
    {
        int m;
        StPop(tmp, &m);
        StPush(Stack, m);
    }
    StDestroy(&tmp);
    return 0;
}