#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct info
{
    char name[20];
    int age;
    int isMarried;
}info;

typedef struct node
{
    info *aPerson;
    struct node *left;
    struct node *right;
}peopleTree;

peopleTree* isPresent(peopleTree *root, info *aPerson);
void insert(peopleTree **root, info *aPerson);
void read_Insert(peopleTree **root, char *file);
peopleTree* maximum(peopleTree *root);
peopleTree* minimum(peopleTree *root);
void freeTree(peopleTree **root);

void insert(peopleTree **root, info *aPerson)
{
    if (*root == NULL)
    {
        *root = (peopleTree *)malloc(sizeof(peopleTree));
        if (*root == NULL)
        {
            printf("Memory allocation failure.\n");
            return;
        }
        (*root)->aPerson = aPerson;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    else if ( strcmp((*root)->aPerson->name, aPerson->name) < 0 )
    {
        return insert(&((*root)->right), aPerson);
    }
    else
    {
        return insert(&((*root)->left), aPerson);
    }
}

void read_Insert(peopleTree **root, char *file)
{
    FILE *ptr = fopen(file, "r");

    if (ptr == NULL)
    {
        printf("File could not open.\n");
        return;
    }
    char person[20];

    while (fgets(person, sizeof(person), ptr))
    {
        info *aPerson = (info *)malloc(sizeof(info));

        if (aPerson == NULL)
        {
            printf("Memory allocation failure.\n");
            return;
        }
        person[strchr(person, '\n') - person] = '\0';
        
        char name[20];
        int age, isMarry;

        sscanf(person, "%s %i %i", name, &age, &isMarry);

        strcpy(aPerson->name, name);
        aPerson->age = age;
        aPerson->isMarried = isMarry;

        insert(root, aPerson);
    }
    fclose(ptr);
}

peopleTree* isPresent(peopleTree *root, info *aPerson)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->aPerson->age == aPerson->age &&
        root->aPerson->isMarried == aPerson->isMarried &&
        strcmp(root->aPerson->name, aPerson->name) == 0  )
    {
        return root;
    }
    else if ( strcmp((root)->aPerson->name, aPerson->name) < 0 )
    {
        return isPresent((root->right), aPerson);
    }
    else
    {
        return isPresent((root->left), aPerson);
    }
}

peopleTree* minimum(peopleTree *root)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return NULL;
    }
    else if (root->left == NULL)   { return root; }
    else                           { return minimum(root->left); }
}

peopleTree* maximum(peopleTree *root)
{
    if (root == NULL)
    {
        printf("Tree is empty.\n");
        return NULL;
    }
    else if (root->right == NULL)  { return root; }
    else                           { return maximum(root->right); }
}

void freeTree(peopleTree **root)
{
    if ((*root) == NULL) return;

    freeTree(&((*root)->left));
    freeTree(&((*root)->right));

    free((*root));
}

peopleTree* delete(peopleTree *sinker, info *aPerson)
{
    
}

int main()
{
    peopleTree *root = NULL;
    read_Insert(&root, "personInfo.txt");

    info aP;
    aP.age = 37;
    aP.isMarried = 0;
    strcpy(aP.name, "Sophia");

    peopleTree *isP = isPresent(root, &aP);

    if (isP != NULL)
    {
        printf("Yes there is \"%s\" whos age is %i, and marry situation: %i.\n", aP.name, aP.age, aP.isMarried);
    }
    else
    {
        printf("There is not.\n");
    }
    peopleTree *min = maximum(root);
    printf("%s %i %i\n",min->aPerson->name, min->aPerson->age, min->aPerson->isMarried);
}