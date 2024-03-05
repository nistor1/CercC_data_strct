#include <string.h>
#include "cchashtable.h"
#include "common.h"

#define INITIAL_SIZE 100

int HtCreate(CC_HASH_TABLE **HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);

    if (HashTable == NULL)
    {
        return -1;
    }

    CC_HASH_TABLE* tmp;
    tmp = (CC_HASH_TABLE*)malloc(INITIAL_SIZE * sizeof(CC_HASH_TABLE));
    if (tmp == NULL)
    {
        return -1;
    }

    memset(tmp, 0, sizeof(*tmp));

    for (int i = 0; i < INITIAL_SIZE; i++)
    {
        tmp[i].Count = 0;
        tmp[i].Size = INITIAL_SIZE;
        tmp[i].Key = -1;
        tmp[i].Next = NULL;
        tmp[i].Data = (char*)malloc(30 * sizeof(char));
    }

    *HashTable = tmp;

    return 0;
}

int htDelete(CC_HASH_TABLE* temp)
{
    if (temp == NULL)
    {
        return 0;
    }
    htDelete(temp->Next);
    free(temp);
    return 0;
}

int HtDestroy(CC_HASH_TABLE** HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    if (HashTable == NULL)
    {
        return -1;
    }
    for (int i = 0; i < (*HashTable)->Count; i++)
    {
        htDelete(( * HashTable) +  i);
    }
    free(*HashTable);
    return 0;
}

int HtSetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int Value)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);

    if (HashTable == NULL)
    {
        return -1;
    }

    if (Key == NULL)
    {
        return -1;
    }

    if (Value < 0)
    {
        return -1;
    }

    CC_HASH_TABLE_ITERATOR tmp;
    tmp.HashTable = HashTable;

    if (tmp.HashTable[Value].Next == NULL && tmp.HashTable[Value].Key == -1)
    {
        //string_copy(tmp.HashTable[Value].Data, Key);
        tmp.HashTable[Value].Key = Value;
        return 0;
    }
    if (tmp.HashTable[Value].Key != -1)
    {
        CC_HASH_TABLE prev;
        while (tmp.HashTable[Value].Next != NULL)
        {
            prev = tmp.HashTable[Value];
            CC_HASH_TABLE *aux;
            aux = tmp.HashTable[Value].Next;
            tmp.HashTable[Value] = *aux;
        }
        prev = tmp.HashTable[Value];
        if (tmp.HashTable[Value].Next != NULL)
        {
            CC_HASH_TABLE* aux;
            aux = tmp.HashTable[Value].Next;
            tmp.HashTable[Value] = *aux;
        }
        CC_HASH_TABLE* node = (CC_HASH_TABLE*)malloc(1 * sizeof(CC_HASH_TABLE));
        if (node == NULL)
        {
            return -1;
        }
        node->Count = tmp.HashTable[Value].Count + 1;
        node->Size = INITIAL_SIZE;
        node->Key = Value;
        node->Next = NULL;
        node->Data = (char*)malloc(30 * sizeof(char));

    }
    tmp.HashTable[Value].Count++;

    return 0;
}

int HtGetKeyValue(CC_HASH_TABLE *HashTable, char *Key, int *Value)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Value);

    if (HashTable == NULL)
    {
        return -1;
    }
    if (Key == NULL)
    {
        return -1;
    }
    if (Value == NULL)
    {
            return -1;
    }
    


    return 0;
}

int HtRemoveKey(CC_HASH_TABLE *HashTable, char *Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    return -1;
}

int HtHasKey(CC_HASH_TABLE *HashTable, char *Key)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    CC_UNREFERENCED_PARAMETER(Key);
    return -1;
}

int HtGetFirstKey(CC_HASH_TABLE* HashTable, CC_HASH_TABLE_ITERATOR **Iterator, char **Key)
{
    CC_HASH_TABLE_ITERATOR *iterator = NULL;

    CC_UNREFERENCED_PARAMETER(Key);

    if (NULL == HashTable)
    {
        return -1;
    }
    if (NULL == Iterator)
    {
        return -1;
    }
    if (NULL == Key)
    {
        return -1;
    }

    iterator = (CC_HASH_TABLE_ITERATOR*)malloc(sizeof(CC_HASH_TABLE_ITERATOR));
    if (NULL == iterator)
    {
        return -1;
    }

    memset(iterator, 0, sizeof(*iterator));

    iterator->HashTable = HashTable;
    // INITIALIZE THE REST OF THE FIELDS OF iterator

    *Iterator = iterator;

    // FIND THE FIRST KEY AND SET Key

    return 0;
}

int HtGetNextKey(CC_HASH_TABLE_ITERATOR *Iterator, char **Key)
{
    CC_UNREFERENCED_PARAMETER(Key);
    CC_UNREFERENCED_PARAMETER(Iterator);
    return -1;
}

int HtReleaseIterator(CC_HASH_TABLE_ITERATOR **Iterator)
{
    CC_UNREFERENCED_PARAMETER(Iterator);
    if (Iterator == NULL)
    {
        return -1;
    }
    (*Iterator)->HashTable = NULL;
    return 0;
}

int HtClear(CC_HASH_TABLE *HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    htDelete(HashTable);
    for (int i = 0; i < INITIAL_SIZE; i++)
    {
        HashTable[i].Count = 0;
        HashTable[i].Size = INITIAL_SIZE;
        HashTable[i].Key = -1;
        HashTable[i].Next = NULL;
        HashTable[i].Data = (char*)malloc(30 * sizeof(char));
    }
    return 0;
}

int HtGetKeyCount(CC_HASH_TABLE *HashTable)
{
    CC_UNREFERENCED_PARAMETER(HashTable);
    if (HashTable == NULL)
    {
        return -1;
    }
    return HashTable->Count;
}
