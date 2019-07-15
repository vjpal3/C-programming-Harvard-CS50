#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
    int value;
    struct Node *low;
    struct Node *high;
}Node;

Node *rootNode;

void addNode(int value)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->low = NULL;
    newNode->high = NULL;

    if (rootNode == NULL) {
        rootNode = newNode;
        return;
    }

    Node *trav = rootNode;
    while(1)
    {
        if(newNode->value < trav->value)
        {
           if(trav->low == NULL)
           {
               trav->low = newNode;
               return;
           }
           trav = trav->low;
        }
        else
        {
            if(trav->high == NULL)
            {
                trav->high = newNode;
                return;
            }
            trav = trav->high;
        }
     }
}

void displayTreeOnEnter(Node *curNode)
{
    // Preorder traversal
    //  10 8 5 4 6 7 9 15 13 17 20 18

    printf("%i ", curNode->value);

    if (curNode->low != NULL)
    {
        displayTreeOnEnter(curNode->low);
    }
    if (curNode->high)
    {
       displayTreeOnEnter(curNode->high);
    }
}

void displayTreeOnDeparture(Node *curNode)
{
    // Postorder traversal
    //4 7 6 5 9 8 13 18 20 17 15 10

    if (curNode->low)
    {
        displayTreeOnDeparture(curNode->low);
    }

    if (curNode->high)
    {
        displayTreeOnDeparture(curNode->high);
    }

    printf("%i ", curNode->value);
}

int doesContain(int value)
{
    // search the tree
    // return 0 if value is not in the tree
    // return 1 if value does exist in the tree

    Node *trav = rootNode;
    while(1)
    {
        if(trav->value == value)
        {
            return 1;
        }

        if(value < trav->value)
        {
            if(!trav->low)
            {
                return 0;
            }
            trav = trav->low;
            continue;
        }
        if(!trav->high)
        {
            return 0;
        }
        trav = trav->high;
    }
}

void freeBinaryTreeRecursive(Node *trav)
{
    if(trav->low)
    {
        freeBinaryTreeRecursive(trav->low);
    }

     if(trav->high)
    {
        freeBinaryTreeRecursive(trav->high);
    }

    free(trav);
}

void tests()
{
    assert(doesContain(10) && "tree does contain 10");
    assert(!doesContain(2) && "tree does not contain 2");
    assert(doesContain(8) && "tree does contain 8");
    assert(doesContain(4) && "tree does contain 4");
    assert(!doesContain(1) && "tree does not contain 1");
    assert(doesContain(15) && "tree does contain 15");
    assert(!doesContain(100) && "Tree does not contain 100");
    assert(doesContain(13) && "tree does contain 13");
    assert(doesContain(7) && "tree does contain 7");
    assert(!doesContain(16) && "tree does not contain 16");
    assert(doesContain(17) && "tree does not contain 17");
    assert(doesContain(20) && "tree does contain 20");
}

int main(void)
{
    printf("Binary Search Tree:\n");
    rootNode = NULL;
    addNode(10);
    addNode(8);
    addNode(15);
    addNode(17);
    addNode(20);
    addNode(18);
    addNode(5);
    addNode(6);
    addNode(9);
    addNode(4);
    addNode(13);
    addNode(7);

    printf("Display Tree on Enter: ");
    displayTreeOnEnter(rootNode);
    printf("\n");

    printf("Display Tree on Departure: ");
    displayTreeOnDeparture(rootNode);
    printf("\n");

    tests();

    freeBinaryTreeRecursive(rootNode);
}
