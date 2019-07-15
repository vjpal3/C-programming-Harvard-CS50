#include <stdio.h>
#include<stdlib.h>

typedef struct Node
{
   int value;
   struct Node *next;
} Node;

Node *rootNode;

void addNodeAtEnd(int n)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = n;
    newNode->next = NULL;

    if(rootNode == NULL)
    {
        rootNode = newNode;
        return;
    }
    Node *trav = rootNode;
    while(trav->next != NULL)
    {
        trav = trav->next;
    }
    trav->next = newNode;
}

void addNodeAtStart(int n)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = n;
    if(rootNode == NULL)
    {
        rootNode = newNode;
        return;
    }
    newNode->next = rootNode;
    rootNode = newNode;
}

void addNodeAtPos(int value, int pos)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;

    if (pos == 1)
    {
        newNode->next = rootNode;
        rootNode = newNode;
        return;
    }

    Node *trav = rootNode;

    for (int i = 0; i < pos-2; i++)
    {
        trav = trav->next;
    }
    newNode->next = trav->next;
    trav->next = newNode;
}

void displayList()
{
    Node *trav = rootNode;
    printf("List: ");
    // while(trav->next != NULL) {
    while(trav != NULL)
    {
        printf("%i ", trav->value);
        trav = trav->next;
    }
     printf("\n");
}


void removeNode(int n)
{
    Node *trav = rootNode;
    if(rootNode->value == n)
    {
        rootNode = rootNode->next;
        free(trav);
        return;
    }
    while(trav->next->value != n)
    {
        trav = trav->next;
    }
    Node *temp = trav->next; //Store the address of the node to be removed.
    trav->next = temp->next; //Link the next node to the previous of the node to be removed.
    free(temp);
}

void freeList()
{
    while(rootNode != NULL)
    {
        //Assign trav to rootNode everytime in the loop, since we are assigning successive values to trav
        Node *trav = rootNode;

        while(trav->next != NULL)
        {
            trav = trav->next;
        }
        removeNode(trav->value);
    }

    free(rootNode);

}

void freeListRecursion(Node *curNode)
{
    if(curNode->next == NULL)
    {
        printf("CurNode about to be freed 1: %i\n", curNode->value);
        free(curNode); //Frees the last node
        return;
    }
    freeListRecursion(curNode->next);

    printf("CurNode about to be freed 2: %i\n", curNode->value);

    free(curNode); //Frees successive nodes, rootNode being the last
    return;

}

int main(void)
{
    rootNode = NULL;
    // addNodeAtEnd(5);
    // addNodeAtEnd(15);
    //  displayList();
    // printf("List: %i %i\n", rootNode->value, rootNode->next->value);

    // addNodeAtStart(2);
    // addNodeAtStart(12);
    // addNodeAtStart(6);
    // addNodeAtStart(18);
    // displayList();

    addNodeAtPos(2, 1); //2
    addNodeAtPos(3, 2); // 2 3
    addNodeAtPos(4, 1); // 4 2 3
    addNodeAtPos(5, 2); //4 5 2 3
    printf("List Formed: ");
    displayList();
    printf("\n");

    // removeNode(5);
    // printf("List after removal: ");
    // displayList(); // 4 2 3
    // printf("\n");

    //freeList();

    freeListRecursion(rootNode);
        // OUTPPUT
        // List Formed: List: 4 5 2 3
        // CurNode about to be freed 1: 3
        // CurNode about to be freed 2: 2
        // CurNode about to be freed 2: 5
        // CurNode about to be freed 2: 4
}
