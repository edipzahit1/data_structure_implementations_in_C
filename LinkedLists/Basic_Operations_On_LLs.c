#include <stdio.h>
#include <stdlib.h>

typedef struct linkedList
{
    int v;
    struct linkedList *next;
    int sign;
}linkedList;

typedef struct doublyLL
{
    int v;
    struct doublyLL *next;
    struct doublyLL *prev;
}doublyLL;

linkedList* intersectionHashing(linkedList *firstList, linkedList *secondList);
linkedList* intersection(linkedList *firstHead, linkedList *secondHead);
int removeDublicates(linkedList *head);
int isCycle_1(linkedList *head);
int isCycle(linkedList *head);
void splitCLL(linkedList *head, linkedList **firstHalf, linkedList **secondHalf);
int countNodesCLL(linkedList *head);
void quicksort(linkedList *head);

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

linkedList* push(linkedList **head, int value)
{
    linkedList *new_node = (linkedList *)malloc(sizeof(linkedList)); //create node

    if (new_node == NULL)   
    {
        printf("Memory allocation failure.\n");
        return 0;
    } 
    new_node->v = value;    //put the value in new node
    new_node->sign = 0;
    new_node->next = *head;     //link new node to head
    *head = new_node;   //update head as it points the new node
    return *head;
}

int isCycle(linkedList *head) //using a sign in every node to indicate visited node
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return 0;
    }
    do
    {
        if (head->sign == 1)
            return 1;
        else    
            head->sign = 1;

        head = head->next;
    } while (head != NULL);
    return 0;
}

int isCycle_1(linkedList *head) //tortoise and hare algorithm
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return 0;
    }
    linkedList *fast = head;
    linkedList *slow = head;

    while (fast != NULL)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast == NULL) return 0;
        fast = fast->next;
        if (fast == slow) return 1;
    }
    return 0;
}

int listlen(linkedList *head)   //could not do it...
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return 0;
    }
    else if (isCycle_1(head))
    {
        
    }
    else
    {
        int count = 0;
        while (head != NULL)
        {
            count++;
            head = head->next;
        }
        return count;
    }
}

int countNodes(linkedList *head)
{
    if (head == NULL)
        return 0;
    else    
        return 1 + countNodes(head->next);
}

int removeDublicates(linkedList *head)  //function to delete duplicates of a sorted list
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return 0;
    }

    linkedList *temp = head;
    linkedList *next = NULL;

    while (temp->next != NULL)
    {
        if (temp->v == temp->next->v)
        {
            next = temp->next->next;
            free(temp->next);
            temp->next = next;
        }
        else
        {
            temp = temp->next;
        }
    }
}

linkedList* intersection(linkedList *firstHead, linkedList *secondHead) //my approach
{
    if (firstHead == NULL || secondHead == NULL)
    {
        printf("At least one list is empty.");
        return NULL;
    }

    linkedList *curr_1 = firstHead;
    linkedList *curr_2 = secondHead;
    linkedList *newList = NULL;

    while (curr_1 != NULL)
    {
        while (curr_2 != NULL)
        {
            if (curr_1->v == curr_2->v)
            {
                push(&newList, curr_1->v);
                break;
            }
            curr_2 = curr_2->next;
        }
        curr_2 = secondHead;
        curr_1 = curr_1->next;
    }
    
    return newList;
}

linkedList* reverseList(linkedList **head)
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
    return (*head);
}

int isPresent(int key, int set[])   { return set[key]; }
int insert(int key, int set[])      { set[key] = 1; }

linkedList* intersectionHashing(linkedList *firstList, linkedList *secondList) //implemented using hashing
{
    if (firstList == NULL || secondList == NULL)
    {
        printf("At least one list is empty.");
        return NULL;
    }
    linkedList *current = firstList;
    linkedList *newList = NULL;
    int set[100] = {0};

    while (current != NULL) //create the hash table
    {
        insert(current->v, set);
        current = current->next;
    }
    current = secondList;
    while (current != NULL) //scan the table to find matching values
    {
        if(isPresent(current->v, set))
            push(&newList, current->v);
        current = current->next;
    }
    reverseList(&newList);
    return newList;
}

void printList(doublyLL *head)
{
    if (head == NULL)
    {
        printf("the list is empty.\n");
    }
    else
    {
        while (head != NULL)
        {
            printf("%i --> ",head->v);
            head = head->next;
        }
        printf("NULL");
    }
    printf("\n");
}

void swap(int *x, int *y)                                                                                                   
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

//quicksort on SSL start---------------------------------------------------
linkedList* partitionSSL(linkedList *low, linkedList *high)
{
    int pivot_value = high->v;
    linkedList *i = low;

    for (linkedList *j = low; j != high; j = j->next)
    {
        if (j->v <= pivot_value)
        {
            swap(&(j->v), &(i->v));
            i = i->next;
        }
    }
    swap(&(i->v), &(high->v));
    return i;
}

void quicksort_recursionSLL(linkedList *low, linkedList *high) 
{
    if (low != NULL && high != NULL && low != high && low != high->next)
    {
        linkedList *pivot = partitionSSL(low, high);
        if (pivot != NULL && pivot != low) 
        {
            linkedList *temp = low;
            while (temp->next != pivot) temp = temp->next; //temp holds the node before pivot

            quicksort_recursionSLL(low, temp); // Sort elements before pivot
            quicksort_recursionSLL(pivot->next, high); // Sort elements after pivot
        }
    }
}

void quicksort(linkedList *head)
{
    if (head == NULL) 
    {
        printf("The list is empty.");
        return; 
    }
    if (head->next == NULL)
    {
        return;
    }
    linkedList *low = head;
    while (head->next != NULL)  head = head->next;
    linkedList *high = head;
    quicksort_recursionSLL(low, high);  
}
//quicksort on SSL end----------------------------------------------------------

int countNodesCLL(linkedList *head)
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return 0;
    }

    linkedList *slow = head;
    linkedList *fast = head;
    linkedList *temp = head;
    int count = 1;
    do
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == temp && fast == temp) break;
        count++;
    }while (1);
    return count;
}

void splitCLL(linkedList *head, linkedList **firstHalf, linkedList **secondHalf)
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return;
    }

    linkedList *current = head;

    for (int i = 0; i < countNodesCLL(head) / 2; ++i)
    {
        push(firstHalf, current->v);
        current = current->next;
    }
    while (current != head)
    {
        push(secondHalf, current->v);
        current = current->next;
    }
    reverseList(firstHalf);
    reverseList(secondHalf);
}

int pushDLL(doublyLL **head, int val)
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

//mergesort for DLL start-----------------------------------------------------------------
void mergeDLLs(doublyLL *head, doublyLL *low, doublyLL *high)
{
    
}

void mergeSortDLL(doublyLL *head, doublyLL *low, doublyLL *high)
{
    
}
//to be contuniued.

int insert_(int key, int set[])
{
    if (set[key] != 0)  set[key]++;
    else                set[key] = 1;
}

doublyLL* removeDublicatesDLL(doublyLL *head)
{
    if (head == NULL)
    {
        printf("The list is empty.");
        return NULL;
    }
    doublyLL *walker = head;
    int set[100] = {0};
    while (walker != NULL)
    {
        insert_(walker->v, set);
        walker = walker->next;
    }
    doublyLL *result = NULL;
    walker = head;
    while (walker != NULL)
    {
        if (set[walker->v] >= 1)
        {
            pushDLL(&result, walker->v);
            set[walker->v] = 0;
        }
        walker = walker->next;
    }
    return result;
}

int main()
{
    doublyLL *head = NULL;

    pushDLL(&head, 40);
    pushDLL(&head, 10);
    pushDLL(&head, 20);
    pushDLL(&head, 10);
    pushDLL(&head, 50);
    pushDLL(&head, 10);
    pushDLL(&head, 40);
    pushDLL(&head, 10);
    pushDLL(&head, 30);
    pushDLL(&head, 40);
    pushDLL(&head, 40);
    pushDLL(&head, 40);

    head = removeDublicatesDLL(head);
    printList(head);
}
