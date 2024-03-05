#include "ccvector.h"
#include "common.h"
#include "string.h"

#define INITIAL_SIZE    100

int VecCreate(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = NULL;

    CC_UNREFERENCED_PARAMETER(Vector);

    if (NULL == Vector)
    {
        return -1;
    }

    vec = (CC_VECTOR*)malloc(sizeof(CC_VECTOR));
    if (NULL == vec)
    {
        return -1;
    }

    memset(vec, 0, sizeof(*vec));

    vec->Count = 0;
    vec->Size = INITIAL_SIZE;
    vec->Array = (int*)malloc( sizeof(int) * INITIAL_SIZE );
    if (NULL == vec->Array) 
    {
        free(vec);
        return -1;
    }

    *Vector = vec;

    return 0;
}

int VecDestroy(CC_VECTOR **Vector)
{
    CC_VECTOR *vec = *Vector;

    if (NULL == Vector)
    {
        return -1;
    }

    free(vec->Array);
    free(vec);

    *Vector = NULL;

    return 0;
}

int Realloc(int** v, int size)
{
    /// REALLOC
    int* tmp = (int*)realloc(*v, ((size + INITIAL_SIZE) * sizeof(int)));
    if (tmp == NULL)
    {
        return -1;
    }
    *v = tmp;
    return 0;
}

int VecInsertTail(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if ((Vector->Count + 1) >= Vector->Size)
    {
        if (Realloc(&Vector->Array, Vector->Size) == 0)
        {
            Vector->Size += INITIAL_SIZE;
        }
        else
        {
            return -1;
        }
    }

    Vector->Array[Vector->Count] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertHead(CC_VECTOR *Vector, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if (Realloc(&Vector->Array, Vector->Size) == 0)
        {
            Vector->Size += INITIAL_SIZE;
        }
        else
        {
            return -1;
        }
    }

    for (int i = Vector->Count-1; i >= 0; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[0] = Value;
    Vector->Count++;

    return 0;
}

int VecInsertAfterIndex(CC_VECTOR *Vector, int Index, int Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (NULL == Vector)
    {
        return -1;
    }

    if (Vector->Count >= Vector->Size)
    {
        if (Realloc(&Vector->Array, Vector->Size) == 0)
        {
            Vector->Size += INITIAL_SIZE;
        }
        else
        {
            return -1;
        }
    }

    if (Index >= Vector->Count || Index < 0)
    {
        return -1;
    }

    Index++;

    for (int i = Vector->Count - 1; i >= Index; i--)
    {
        Vector->Array[i + 1] = Vector->Array[i];
    }
    Vector->Array[Index] = Value;
    Vector->Count++;

    return 0;
}

int VecRemoveByIndex(CC_VECTOR *Vector, int Index)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);

    if (Vector == NULL)
    {
        return -1;
    }
        if (Vector->Count >= Vector->Size)
    {
        /// REALLOC
        return -1;
    }
    if (Index >= Vector->Count || Index < 0)
    {
        return -1;
    }

    CC_VECTOR *vec = Vector;
    int n = vec->Count;

    for (int i = Index; i < n; i++)
    {
        vec->Array[i] = vec->Array[i + 1];
    }
    vec->Count--;
    
    return 0;
}

int VecGetValueByIndex(CC_VECTOR* Vector, int Index, int* Value)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Vector == NULL)
    {
        return -1;
    }
    if (Index >= Vector->Count || Index < 0)
    {
        return -1;
    }

    if (Value == NULL)
    {
            return -1;
    }

    *Value = Vector->Array[Index];
    return 0;
}

int VecGetCount(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);

    if (Vector == NULL)
    {
        return -1;
    }
    if (Vector->Count < 0 || Vector->Count >= INITIAL_SIZE)
    {
        return -1;
    }
    return Vector->Count;
}

int VecClear(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (Vector == NULL)
    {
        return -1;
    }

    CC_VECTOR* vec = Vector;
    vec->Size = INITIAL_SIZE;
    vec->Count = 0;

    return vec->Count;
}

int VecSort(CC_VECTOR *Vector)
{
    CC_UNREFERENCED_PARAMETER(Vector);
    if (Vector == NULL)
    {
        return -1;
    }
    CC_VECTOR* vec = Vector;
    int ok = 0;
    int n = vec->Size;

    while (ok == 0)
    {
        ok = 1;
        for (int i = 0; i < n - 1; i++)
        {
            if (vec->Array[i] < vec->Array[i + 1])
            {
                int aux;
                aux = vec->Array[i];
                vec->Array[i] = vec->Array[i + 1];
                vec->Array[i + 1] = aux;
                ok = 0;
            }
        }
    }
    Vector = vec;
    return n;
}

int VecAppend(CC_VECTOR *DestVector, CC_VECTOR *SrcVector)
{
    CC_UNREFERENCED_PARAMETER(DestVector);
    CC_UNREFERENCED_PARAMETER(SrcVector);

    if (DestVector == NULL || SrcVector == NULL)
    {
        return -1;
    }
    if (DestVector->Count >= DestVector->Size)
    {
        return -1;
    }
    if (SrcVector->Count >= SrcVector->Size)
    {
        return -1;
    }
    if (SrcVector->Count + DestVector->Count >= INITIAL_SIZE)
    {
        return -1;
    }

    CC_VECTOR* dest, * src;
    dest = DestVector;
    src = SrcVector;

    for (int i = dest->Count; i <= (dest->Count + src->Count); i++)
    {
        dest->Array[i] = src->Array[(i - dest->Count)];
    }

    return (dest->Count + src->Count);
}