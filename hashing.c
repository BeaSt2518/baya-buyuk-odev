#include <stdio.h>
#include <stdlib.h>

//linked list structure for chaining
typedef struct hashing_s *NODE;
struct hashing_s
{
    int key;
    NODE next;
} hashing_t[1];




//hash function
int hashFunction(int key)
{
    return key % 15;
}

//insert key into hash table
void insert(NODE hash_table[], int key)
{
    int index = hashFunction(key);
    NODE temp = (NODE)malloc(sizeof(hashing_t));
    temp->key = key;
    temp->next = NULL;
    if(hash_table[index] == NULL)
    {
        hash_table[index] = temp;
    }
    else
    {
        NODE temp1 = hash_table[index];
        while(temp1->next != NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}

//search key in hash table by looking at the array of linked lists
NODE search(NODE hash_table[], int key)
{
    int index = hashFunction(key);
    NODE temp = hash_table[index];
    while(temp != NULL)
    {
        if(temp->key == key)
        {
            printf("Key found in hash table");
            return temp;
        }
        printf("Key not found in hash table");
    }
}

//delete key from hash table
void delete(NODE hash_table[], int key)
{
    int index = hashFunction(key);
    NODE temp = hash_table[index];
    NODE prev = NULL;
    while(temp != NULL)
    {
        if(temp->key == key)
        {
            if(prev == NULL)
            {
                hash_table[index] = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

//print hash table
void print_hash_table(NODE hash_table[])
{
    int i;
    for(i = 0; i < 15; i++)
    {
        NODE temp = hash_table[i];
        printf("hash_table[%d]-->", i);
        while(temp != NULL)
        {
            printf("%d-->", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}    


void main()
{
    NODE hash_table[15] = {NULL};
    insert(hash_table, 1);
    insert(hash_table, 2);
    insert(hash_table, 3);
    insert(hash_table, 4);
    insert(hash_table, 5);
    insert(hash_table, 6);
    insert(hash_table, 7);
    insert(hash_table, 8);
    insert(hash_table, 9);
    insert(hash_table, 10);
    insert(hash_table, 11);
    insert(hash_table, 12);
    insert(hash_table, 21);
    print_hash_table(hash_table);
    delete(hash_table, 12);
    search(hash_table, 4);





}