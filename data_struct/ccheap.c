#include "ccheap.h"
#include "common.h"
#include "ccvector.h"

#define INITIAL_SIZE 100

int HpInsert();

int HpCreateMaxHeap(CC_HEAP **MaxHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MaxHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);
    CC_HEAP* temp;

    temp = (CC_HEAP*)malloc(1 * sizeof(CC_HEAP));
    if (temp == NULL)
    {
        return -1;
    }
    temp->Max = 1;

    if (InitialElements != NULL)
    {
        temp->Array = (int*)malloc((InitialElements->Count + 1) * sizeof(int));
        if (temp->Array == NULL)
        {
            return -1;
        }

        temp->Count = InitialElements->Count;
        temp->Size = InitialElements->Size;

        CC_VECTOR* p = InitialElements;
        for (int i = 0; i < p->Count - 2; i++)
        {
            HpInsert(temp, p->Array[i]);
        }

        return 0;
    }

    temp->Array = (int*)malloc(INITIAL_SIZE * sizeof(int));
    if (temp->Array == NULL)
    {
        return -1;
    }
    temp->Count = 0;
    temp->Size = INITIAL_SIZE;

    *MaxHeap = temp;
    return 0;
}

int HpCreateMinHeap(CC_HEAP** MinHeap, CC_VECTOR* InitialElements)
{
    CC_UNREFERENCED_PARAMETER(MinHeap);
    CC_UNREFERENCED_PARAMETER(InitialElements);

    CC_HEAP* temp;

    temp = (CC_HEAP*)malloc(1 * sizeof(CC_HEAP));
    if (temp == NULL)
    {
        return -1;
    }
    temp->Max = -1;

    if (InitialElements != NULL)
    {
        temp->Array = (int*)malloc((InitialElements->Count + 1) * sizeof(int));
        if (temp->Array == NULL)
        {
            return -1;
        }

        temp->Count = InitialElements->Count;
        temp->Size = InitialElements->Size;

        CC_VECTOR* p = InitialElements;
        for (int i = 0; i < p->Count - 2; i++)
        {
            HpInsert(temp, p->Array[i]);
        }

        return 0;
    }

    temp->Array = (int*)malloc(INITIAL_SIZE * sizeof(int));
    if (temp->Array == NULL)
    {
        return -1;
    }
    temp->Count = 0;
    temp->Size = INITIAL_SIZE;

    *MinHeap = temp;
    return 0;
}

int HpDestroy(CC_HEAP **Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    if (Heap == NULL)
    {
        return -1;
    }
    if (*Heap == NULL)
    {
        return 0;
    }
    free((*Heap)->Array);
    free(*Heap);
    return 0;
}

int HpInsert(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Heap == NULL)
    {
        return -1;
    }
    if (Heap->Count >= Heap->Size)
    {
        //REALLOC
        int* tmp = (int*)realloc(Heap->Array, ((Heap->Size + INITIAL_SIZE) * sizeof(int)));
        if (tmp == NULL)
        {
            return -1;
        }
        Heap->Array = tmp;
        Heap->Size += INITIAL_SIZE;
    }
    
    int i = Heap->Count;
    CC_HEAP* temp = Heap;
    temp->Array[temp->Count] = Value;
    do
    {
        if (Heap->Max > 0)
        {
            if (temp->Array[((i - 1) / 2)] < temp->Array[i])
            {
                int aux;
                aux = temp->Array[((i - 1) / 2)];
                temp->Array[((i - 1) / 2)] = temp->Array[i];
                temp->Array[i] = aux;
            }
            i = ((i - 1) / 2);
        }
        else
        {
            if (temp->Array[((i - 1) / 2)] > temp->Array[i])
            {
                int aux;
                aux = temp->Array[((i - 1) / 2)];
                temp->Array[((i - 1) / 2)] = temp->Array[i];
                temp->Array[i] = aux;
            }
            i = ((i - 1) / 2);
        }
    } while (i != 0);

    Heap->Count++;
    return 0;
}

int HpRemove(CC_HEAP *Heap, int Value)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(Value);
    int aux;
    int i = 0;
    for (i = 0; i < Heap->Count; i++)
    {
        if (Heap->Array[i] == Value)
        {
            aux = Heap->Array[i];
            Heap->Array[i] = Heap->Array[Heap->Count];
            Heap->Array[Heap->Count] = aux;
            Heap->Count--;
            while (i < Heap->Count)

            {
                if (Heap->Max < 0)
                {
                    if (Heap->Array[2 * i + 1] > Heap->Array[2 * i + 2])
                    {
                        aux = Heap->Array[i];
                        Heap->Array[i] = Heap->Array[2 * i + 1];
                        Heap->Array[2 * i + 1] = aux;
                        i = 2 * i + 1;
                    }
                    else
                    {
                        aux = Heap->Array[i];
                        Heap->Array[i] = Heap->Array[2 * i + 2];
                        Heap->Array[2 * i + 2] = aux;
                        i = 2 * i + 2;
                    }
                }
                else
                {
                    if (Heap->Array[2 * i + 1] < Heap->Array[2 * i + 2])
                    {
                        aux = Heap->Array[i];
                        Heap->Array[i] = Heap->Array[2 * i + 1];
                        Heap->Array[2 * i + 1] = aux;
                        i = 2 * i + 1;
                    }
                    else
                    {
                        aux = Heap->Array[i];
                        Heap->Array[i] = Heap->Array[2 * i + 2];
                        Heap->Array[2 * i + 2] = aux;
                        i = 2 * i + 2;
                    }
                }
            }
        }
    }
    return 0;
}

int HpGetExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    if (Heap == NULL)
    {
        return -1;
    }
    if (ExtremeValue == NULL)
    {
        int* p = (int*)malloc(sizeof(int));
        if (p == NULL)
        {
            return -1;
        }
        ExtremeValue = p;
    }
    *ExtremeValue = Heap->Array[0];
    return 0;
}

int HpPopExtreme(CC_HEAP *Heap, int* ExtremeValue)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(ExtremeValue);
    if (Heap == NULL)
    {
        return -1;
    }

    if (HpGetExtreme(Heap, ExtremeValue) != 0)
    {
        return -1;
    }

    HpRemove(Heap, *ExtremeValue);
    return 0;
}

int HpGetElementCount(CC_HEAP *Heap)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    if (Heap == NULL)
    {
        return -1;
    }

    return Heap->Count;
}

void sortVec(CC_VECTOR* vec)
{
    int ok = 0;
    while (ok == 0)
    {
        ok = 1;
            for (int i = 0; i < vec->Count; i++)
            {
                if (vec->Array[i] > vec->Array[i + 1])
                {
                    int aux;
                    aux = vec->Array[i];
                    vec->Array[i] = vec->Array[i + 1];
                    vec->Array[i + 1] = aux;
                    ok = 0;
                }
            }
    }
}



int HpSortToVector(CC_HEAP *Heap, CC_VECTOR* SortedVector)
{
    CC_UNREFERENCED_PARAMETER(Heap);
    CC_UNREFERENCED_PARAMETER(SortedVector);
    if (Heap == NULL)
    {
        return -1;
    }
    if (SortedVector == NULL)
    {
        CC_VECTOR* temp = (CC_VECTOR*)malloc(sizeof(int));
        if (temp == NULL)
        {
            return -1;
        }
        temp->Array = (int*)malloc((Heap->Count + 1) * sizeof(int));
        if (temp->Array == NULL)
        {
            return -1;
        }

        temp->Count = Heap->Count;
        temp->Size = Heap->Count + 1;
        SortedVector = temp;
    }
    if (Heap->Count >= SortedVector->Size)
    {
        free(SortedVector->Array);
        free(SortedVector);
        CC_VECTOR* temp = (CC_VECTOR*)malloc(sizeof(int));
        if (temp == NULL)
        {
            return -1;
        }
        temp->Array = (int*)malloc((Heap->Count + 1) * sizeof(int));
        if (temp->Array == NULL)
        {
            return -1;
        }

        temp->Count = Heap->Count;
        temp->Size = Heap->Count + 1;
        SortedVector = temp;
    }
    SortedVector->Count = Heap->Count;

    for (int i = 0; i < Heap->Count; i++)
    {
        if (i < SortedVector->Size && i > 0)
        {
            SortedVector->Array[i] = Heap->Array[i];
        }
    }

    sortVec(SortedVector);

    return 0;
}
