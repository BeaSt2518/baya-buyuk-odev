#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;

typedef struct LINKED_LIST_NODE_s{

	LINKED_LIST_NODE next; /* Do not change order */

	int data;

} LINKED_LIST_NODE_t[1];

typedef struct LINKED_LIST_s *LINKED_LIST;

typedef struct LINKED_LIST_s{

  	LINKED_LIST_NODE head; /* May overlap with next. */

} LINKED_LIST_t[1], *LINKED_LIST;


//function to append a node to the end of the list
void append(LINKED_LIST list, int data)
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

//funciton to print the list
void printlist(LINKED_LIST list)
{
    LINKED_LIST_NODE current = list->head;
    while(current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
}

//topological sort function
void topologicalsort(LINKED_LIST list, int matrix[8][8], int size)
{

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
            append(list, i);
            //printlist(list);
        }
    }
    while(list->head != NULL)
    {
        int current = list->head->data;
        printf("%d ", current);
        list->head = list->head->next;
        for(i = 0; i < size; i++)
        {
            if(matrix[current][i] == 1)
            {
                indegree[i]--;
                if(indegree[i] == 0)
                {
                    append(list, i);
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

void main(){

    //The thing is that vertex 1 is actually vertex zero and I coded that way. So the list is actually 0 1 2 3 4


    LINKED_LIST list = malloc(sizeof(LINKED_LIST_t));
    LINKED_LIST list2 = malloc(sizeof(LINKED_LIST_t));
    list = initlist();
                                //   1 2 3 4 5
    int matrix[SIZE][SIZE] = {      {0,1,1,0,0}, //1
                                    {0,0,0,1,1}, //2
                                    {0,0,0,0,0}, //3
                                    {0,0,0,0,0}, //4
                                    {0,0,0,0,0}};//5

                           //1 2 3 4 5 6 7 8
    int matrix2[8][8] = {   {0,0,0,1,0,0,0,0}, //1
                            {0,0,0,1,1,0,0,0}, //2
                            {0,0,0,0,1,0,0,1}, //3
                            {0,0,0,0,0,1,1,1}, //4
                            {0,0,0,0,0,0,1,0}, //5
                            {0,0,0,0,0,0,0,0}, //6
                            {0,0,0,0,0,0,0,0}, //7
                            {0,0,0,0,0,0,0,0}};//8
    
    

    //topologicalsort(list, matrix, SIZE);
    topologicalsort(list2, matrix2, 8);
    //printlist(list);
    printlist(list2);

}