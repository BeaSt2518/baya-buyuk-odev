#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;

typedef struct LINKED_LIST_NODE_s{

	LINKED_LIST_NODE next; /* Do not change order */

	void *data;

} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;

typedef struct LINKED_LIST_s{

  	LINKED_LIST_NODE head; /* May overlap with next. */

} LINKED_LIST_t[1], *LINKED_LIST;


//function to append a node to the end of the list
void append(LINKED_LIST list, void *data)
{
    LINKED_LIST_NODE newnode = malloc(sizeof(LINKED_LIST_NODE_t));
    newnode->data = data;
    newnode->next = NULL;
    LINKED_LIST_NODE current = list->head;
    if(current == NULL)
    {
        list->head = newnode;
    }
    else
    {
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = newnode;
    }
}

//funciton ot print the list
void printlist(LINKED_LIST list)
{
    LINKED_LIST_NODE current = list->head;
    while(current != NULL)
    {
        printf("%d ", *(int*)current->data);
        current = current->next;
    }
}

//topological sort function
void topologicalsort(LINKED_LIST list, int **matrix, int size)
{
    
    //why are we taking the matrix as a pointer to a pointer?
    //
    int i;
    int j;
    int *indegree = malloc(sizeof(int)*size);
    for(i = 0; i < size; i++)
    {
        indegree[i] = 0;
    }
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            if(matrix[i][j] == 1)
            {
                indegree[j]++;
            }
        }
    }
    for(i = 0; i < size; i++)
    {
        if(indegree[i] == 0)
        {
            append(list, &i);
        }
    }
    while(list->head != NULL)
    {
        int *current = list->head->data;
        printf("%d ", *current);
        list->head = list->head->next;
        for(i = 0; i < size; i++)
        {
            if(matrix[*current][i] == 1)
            {
                indegree[i]--;
                if(indegree[i] == 0)
                {
                    append(list, &i);
                }
            }
        }
    }
}

//linked list init function
LINKED_LIST initlist()
{
    LINKED_LIST list = malloc(sizeof(LINKED_LIST_t));
    list->head = NULL;
    return list;
}

int main(){


    LINKED_LIST list = malloc(sizeof(LINKED_LIST_t));
    list = initlist();

    int matrix[5][5] = {{0,1,0,0,1},
                        {0,0,1,0,0},
                        {0,0,0,0,0},
                        {0,0,0,1,0},
                        {0,1,0,0,0}};

    topologicalsort(list, matrix, 5);
    printlist(list);



    return 0;
}