#include <stdio.h>
#include <stdlib.h>

typedef struct linkedList
{
    int v;
    struct linkedList *next;
}linkedList;

linkedList* singleyToCircley(linkedList *head);
linkedList* push(linkedList **head, int value);
linkedList* pop(linkedList **head);
linkedList* getNth(linkedList *head, int N);
int countNodes_1(linkedList *head);
int countNodes_2(linkedList *head);
int reverseList(linkedList **head);
int deleteBeginning(linkedList **head);
int deleteEnd(linkedList *head);
int deleteNth(linkedList **head, int pos);
int deleteList(linkedList **head);
void printList(linkedList *head);

linkedList* push(linkedList **head, int value)
{
    linkedList *new_node = (linkedList *)malloc(sizeof(linkedList)); //create node

    if (new_node == NULL)   
    {
        printf("Memory allocation failure.\n");
        return 0;
    } 
    new_node->v = value;    //put the value in new node
    new_node->next = *head;     //link new node to head
    *head = new_node;   //update head as it points the new node
    return *head;
}

linkedList* pop(linkedList **head)
{
    if (*head == NULL)
    {
        printf("The list is empty. Cannot pop.\n");
        return NULL;
    }

    linkedList *popped = *head; //popped element points head
    *head = (*head)->next;  //update head
    popped->next = NULL;    

    return popped;
}

int countNodes_1(linkedList *head) //iteratively
{
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

int countNodes_2(linkedList *head) //recursively
{
    if (head == NULL)
        return 0;
    else
        return 1 + countNodes_2(head->next);
}

int reverseList(linkedList **head)
{
    linkedList *current, *previous, *nextNode;
    current = *head;
    previous = NULL;
    nextNode = NULL;

    while (current != NULL)
    {
        nextNode = current->next;   // store the next node
        current->next = previous;   // current node now point the previous one
        previous = current;     //update previous to current
        current = nextNode;     //update current to next
    }
    *head = previous; //head points to last element
}

int deleteBeginning(linkedList **head) //deletes the beginning
{
    linkedList *temp = *head;
    *head = (*head)->next;
    free(temp);
}

int deleteEnd(linkedList *head) //deletes from end
{
    if (head == NULL || head->next == NULL) //delete the head if it has only one element or none.
    {
        free(head);
        return 1;
    }
    linkedList *next;           //in this function, we are not creating a temporary head 
    next = head->next;          //pointer, because it will still point the start when returned. (local pointer)

    while(next->next != NULL)
    {
        head = head->next;
        next = head->next;
    }
    head->next = NULL;
    free(next);
    return 1;
}

int deleteNth(linkedList **head, int pos)
{
    if (*head == NULL)  //if list empty
    {
        printf("List is empty.");   
        return 0;
    }
    if (pos > countNodes_1(*head)) //if exceeds
    {
        printf("Position exceeds.");
        return 0;
    }
    if (pos == 1)   //if the head
    {
        deleteBeginning(head);
        return 1;
    }
    
    linkedList *current = *head;    //another position
    linkedList *previous = NULL;

    for (int i = 1; i < pos; ++i)
    {
        previous = current;
        current = current->next;
    }

    previous->next = current->next;
    free(current);
    return 1;
}

int deleteList(linkedList **head) //deletes the whole list
{
    if (*head == NULL)
    {
        printf("The list is already empty.");
        return 1;
    }

    linkedList *current = *head;
    linkedList *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
    return 1;
}

linkedList* getNth(linkedList *head, int N) //it returns the node
{
    if (head == NULL)   //if empty
    {
        printf("The list is empty.");
        return NULL;
    }
    if (N > countNodes_1(head)) //if exceeds.
    {
        printf("Out of list.");
        return NULL;
    }
    for (int i = 1; i < N; ++i)
    {
        head = head->next;
    }
    return head;
}

linkedList* singleyToCircley(linkedList *head) //convert singley linked list to circley and return the head
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return 0;
    }
    
    linkedList *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = head;
    return head;
}

void printList(linkedList *head)
{
    if (head == NULL)
    {
        printf("the list is empty.\n");
    }
    else
    {
        for (linkedList *current = head; current != NULL; current = current->next)
        {
            printf("%i --> ",current->v);
        }
        printf("NULL");
    }
    printf("\n");
}

int main()
{
    linkedList *head = NULL;
    
    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    push(&head, 50);
    pop(&head);
    
    printList(head);
}