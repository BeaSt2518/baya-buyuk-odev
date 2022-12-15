#include <stdio.h>
#include <stdlib.h>

#define N 15

typedef struct hash_table_s *Hash;
typedef struct hash_table_s{
    int key;
    Hash next;
} hash_table_t[1];

int hash_function(int key)
{ 
    return key % 10;
}

void insert(Hash hash_table[], int key)
{
    int index = hash_function(key);
    Hash temp = (Hash)malloc(sizeof(hash_table_t));
    temp->key = key;
    temp->next = NULL;
    if(hash_table[index] == NULL)
    {
        hash_table[index] = temp;
    }
    else
    {
        Hash temp1 = hash_table[index];
        while(temp1->next != NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}

//insert key into hash table
/*void insert(Hash hash_table[], int key)
{
    int index = hash_function(key);
    Hash temp = (Hash)malloc(sizeof(hash_table_t));
    temp->key = key;
    temp->next = NULL;
    if(hash_table[index] == NULL)
    {
        hash_table[index] = temp;
    }
    else
    {
        Hash temp1 = hash_table[index];
        while(temp1->next != NULL)
        {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
}*/

void print_hash_table(Hash hash_table[])
{
    for(int i = 0; i < 10; i++)
    {
        Hash temp = hash_table[i];
        //printf("%d: ", i);
        while(temp != NULL)
        {
            printf("%d", temp->key);
            temp = temp->next;
        }
    }
    printf("\n");
}

void print_hash_table_char(Hash hash_table[])
{
    for(int i = 0; i < 10; i++)
    {
        Hash temp = hash_table[i];
        //printf("%d: ", i);
        while(temp != NULL)
        {
            printf("%c",temp->key);
            temp = temp->next;
        }
    }
    printf("\n");
}

int main()
{
    Hash hash_table[10];
    for(int i = 0; i < 10; i++)
    {
        hash_table[i] = NULL;
    }

    printf("Our pasword is: 12345678911\n");

    insert(hash_table, 1);
    insert(hash_table, 2);
    insert(hash_table, 3);
    insert(hash_table, 4);
    insert(hash_table, 5);
    insert(hash_table, 6);
    insert(hash_table, 7);
    insert(hash_table, 8);
    insert(hash_table, 9);
    insert(hash_table, 1);

    printf("After hashing with ints: ");
    print_hash_table(hash_table);

    printf("After hashing with chars: ");
    print_hash_table_char(hash_table);
}


