#include <stdio.h>
#include <stdlib.h>

typedef struct doublyLL
{
    int v;
    struct doublyLL *next;
    struct doublyLL *prev;
}doublyLL;

int push(doublyLL **head, int val);
int countNodes(doublyLL *head);
int deleteBeginning(doublyLL **head);
int deleteNth(doublyLL **head, int pos);
void printList(doublyLL *head);
int reverseList(doublyLL **head);

int push(doublyLL **head, int val)
{
    doublyLL *new_node = (doublyLL *)malloc(sizeof(doublyLL));

    if (new_node == NULL)
    {
        printf("Memory allocation failure.\n");
        return 0;
    }
    new_node->v = val;
    new_node->prev = NULL;
    new_node->next = *head;
    if (*head != NULL) (*head)->prev = new_node;
    *head = new_node;

    return 1;  
}

int countNodes(doublyLL *head)
{
    if (head == NULL)
        return 0;
    else
        return 1 + countNodes(head->next);
}

int deleteBeginning(doublyLL **head)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return 0;
    }
    doublyLL *temp = *head;
    *head = (*head)->next;

    if (*head != NULL) 
        (*head)->prev = NULL;

    temp->next = NULL;
    free(temp);
}

int deleteNth(doublyLL **head, int pos)
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return 0;
    }
    if (pos > countNodes(*head))
    {
        printf("There is no element in index %i.\n", pos);
        return 0;
    }
    if (pos == 1)
    {
        deleteBeginning(head);
        return 1;
    }
    
    doublyLL *current = *head;

    for (int i = 1; i < pos; ++i)
    {
        current = current->next;
    }
    current->prev->next = current->next;
    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    else
    {
        current->prev = NULL;
    }
    free(current);
    return 1;
}

void printList(doublyLL *head)
{
    if (head == NULL)
    {
        printf("the list is empty.\n");
    }
    else
    {
        for (doublyLL *current = head; current != NULL; current = current->next)
        {
            printf("%i --> ",current->v);
        }
        printf("NULL");
    }
    printf("\n");
}

int reverseList(doublyLL **head) //you might want to draw and think about it 
{
    if (*head == NULL)
    {
        printf("List is empty.\n");
        return 0;
    }
    doublyLL *current = *head;
    doublyLL *previous = NULL;

    while (current != NULL)
    {
        previous = current->prev;
        current->prev = current->next;
        current->next = previous;
        current = current->prev;
    }
    
    (*head) = previous->prev; //because prev now points the next node :))
    return 1;
}

int main()
{
    doublyLL *head = NULL;

    push(&head, 10);
    push(&head, 20);
    push(&head, 30);
    push(&head, 40);
    reverseList(&head);
    printList(head);
}