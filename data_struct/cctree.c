#include "cctree.h"
#include "common.h"

#define INITIAL_SIZE 100

int TreeCreate(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }

    CC_TREE* temp = (CC_TREE*) malloc(1 * sizeof(CC_TREE));
    if (temp == NULL)
    {
        return -1;
    }
    temp->Left = NULL;
    temp->Right = NULL;
    temp->Count = 0;
    temp->Root = 1;

    *Tree = temp;

    return 0;
}

int TreeDestroy(CC_TREE **Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }

    if (*Tree == NULL)
    {
        return -1;
    }
    TreeDestroy(&((*Tree)->Left));
    TreeDestroy(&((*Tree)->Right));

    free(*Tree);
    return 0;
}

CC_TREE* newNode(int data)
{
    CC_TREE* node = (CC_TREE*)malloc(1 * sizeof(CC_TREE));
    if (node == NULL)
    {
        return NULL;
    }
    node->Data = data;
    node->Left = NULL;
    node->Right = NULL;

    return node;
}

CC_TREE* insert(CC_TREE* node, int data)
{
    //daca nu exista returneaza un nou nod
    if (node == NULL)
    {
        return(newNode(data));
    }
    else
    {
        if (data <= node->Data)
        {
            node->Left = insert(node->Left, data);
        }
        else
        {
            node->Right = insert(node->Right, data);
        }
        return (node);
    }
}

int TreeInsert(CC_TREE* Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);

   if (Tree == NULL)
    {
        return -1;
    }
   if (Tree->Count == 0)
   {
       Tree->Count++;
       Tree->Data = Value;
       Tree->Root = 1;
       Tree->Left = NULL;
       Tree->Right = NULL;
       return 0;
   }
   if (insert(Tree, Value) == Tree) //Am folosit algoritmul prezent in curs
   {
       Tree->Count++;
       return 0;
   }
   return -1;
}

CC_TREE* findMin(CC_TREE *node)
{
    if (node == NULL)
    {
        return NULL;
    }
    else
    {
        if (node->Left == NULL)
        {
            return node;
        }
        return findMin(node->Left);
    }
}

CC_TREE* findMax(CC_TREE* node)
{
    if (node == NULL)
    {
        return NULL;
    }
    else
    {
        if (node->Right == NULL)
        {
            return node;
        }
        return findMin(node->Right);
    }
}

CC_TREE* delete(CC_TREE* node, int data)
{
    CC_TREE* temp;

        if (data < node->Data)
        {
            node->Left = delete(node->Left, data);
        }
        else
        {
            if (data > node->Data)
            {
                node->Right = delete(node->Right, data);
            }
            else
            {
                /*Acum putem sa stergem acest nod si sa-l inlocuim fie cu cel mai mic
                element din sub-arborele din dreapta, fie cu cel mai mare element din sub-arborele din stanga*/
                if (node->Right && node->Left)
                {
                    temp = findMin(node->Right);
                    node->Data = temp->Data;
                    node->Right = delete(node->Right, temp->Data);
                }
                else
                {
                    /*In cazul in care nu exista niciun fiu sau exista doar unul
                    singur atunci putem sa stergem nodul si sa-i conectam parintele cu fiul acestuia*/
                    temp = node;
                    if (node->Left == NULL)
                    {
                        node = node->Right;
                    }
                    else
                    {
                        if (node->Right == NULL)
                        {
                            node = node->Left;
                        }
                    }
                    if (temp->Count != 0)
                    {
                        free(temp);//temp nu mai este necesar
                    }
                }
            }
        }
        return node;
}   

int TreeRemove(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Tree == NULL)
    {
        return -1;
    }

    Tree->Count--;
    delete(Tree, Value); //Am folosit algoritmul prezent in curs
    return 0;
}

CC_TREE* search(CC_TREE* t, int key)
{
    //empty tree -> valoarea nu este gasita
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        if (key == t->Data)
        {
            return t;
        }
        else
        {
            if (key < t->Data)
            {
                return(search(t->Left, key));
            }
            else
            {
                return(search(t->Right, key));
            }
        }
    }
}

int TreeContains(CC_TREE *Tree, int Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Value);
    if (Tree == NULL)
    {
        return -1;
    }
    if (Tree->Count == 0)
    {
        return 0;
    }

    CC_TREE* temp;
    temp = search(Tree, Value);
    if (temp == NULL)
    {
        return 0;
    }

    return 1;
}

int TreeGetCount(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }
    return Tree->Count;
}

int TreeGetHeight(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }

    int leftHeight = TreeGetHeight(Tree->Left);
    int rightHeight = TreeGetHeight(Tree->Right);
    int max;

    if (leftHeight > rightHeight)
    {
        max = leftHeight + 1;
    }
    else
    {
        max = rightHeight + 1;
    }
    return max;
}

int TreeClear(CC_TREE *Tree)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Tree);
    if (Tree == NULL)
    {
        return -1;
    }

    TreeClear(Tree->Left);
    TreeClear(Tree->Right);
    if (Tree->Root == 1)
    {
        Tree->Count = 0;
        Tree->Right = NULL;
        Tree->Left = NULL;
        return 0;
    }
    free(Tree);
    return 0;
}

int TreeGetNthPreorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (Value == NULL)
    {
        Value = (int*)malloc(sizeof(int));
        if (Value == NULL)
        {
            exit(-1);
        }
    }
    if (Tree == NULL)
    {
        return -1;
    }
    static int i;
    if (Tree->Root == 1)
    {
        i = 0;
    }
    if (i == Index)
    {
        Value = &Tree->Data;
    }
    i++;
    TreeGetNthPreorder(Tree->Left, Index, Value);
    TreeGetNthPreorder(Tree->Right, Index, Value);
    return 0;
}

int TreeGetNthInorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (Value == NULL)
    {
        Value = (int*)malloc(sizeof(int));
        if (Value == NULL)
        {
            exit(-1);
        }
    }
    if (Tree == NULL)
    {
        return -1;
    }
    static int i;
    TreeGetNthInorder(Tree->Left, Index, Value);
    if (Tree->Root == 1)
    {
        i = 0;
    }
    if (i == Index)
    {
        Value = &Tree->Data;
    }
    i++;
    TreeGetNthInorder(Tree->Right, Index, Value);
    return 0;
}

int TreeGetNthPostorder(CC_TREE *Tree, int Index, int *Value)
{
    CC_UNREFERENCED_PARAMETER(Tree);
    CC_UNREFERENCED_PARAMETER(Index);
    CC_UNREFERENCED_PARAMETER(Value);

    if (Value == NULL)
    {
        Value = (int*)malloc(sizeof(int));
        if (Value == NULL)
        {
            exit(-1);
        }
    }
    if (Tree == NULL)
    {
        return -1;
    }
    static int i;
    TreeGetNthPostorder(Tree->Left, Index, Value);
    TreeGetNthPostorder(Tree->Right, Index, Value);
    if (Tree->Root == 1)
    {
        i = 0;
    }
    if (i == Index)
    {
        Value = &Tree->Data;
    }
    i++;
    return 0;
}

