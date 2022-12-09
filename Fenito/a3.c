#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 31
#define NULLVALUE 0



void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void leftRotate(int btree[], int index){
    int temp = btree[index];
    btree[index] = btree[2*index + 2];
    btree[2*index + 2] = btree[2*index + 1];
    btree[2*index + 1] = temp;
}


void rightRotate(int btree[], int index){
    int temp = btree[index];
    btree[index] = btree[2*index + 1];
    btree[2*index + 1] = btree[2*index + 2];
    btree[2*index + 2] = temp;
}


int max(int a, int b){
    if(a >= b){
        return a;
    }
    else{
        return b;
    }
}


int btheight(int index)
{
    int i = 0;
    int count = 0;

    if(index == 1)
    {
        return 1;
    }

    while(i < index)
    {
        count++;
        i = pow(2,count)-1;
    }
    return count;
}



int checkBalanceIterative(int btree[], int index){
    int left = 0;
    int right = 0;
    int i = 0;
    while(btree[2*index + 1] != NULLVALUE){
        left++;
        i = 2*i + 1;
    }
    i = 0;
    while(btree[2*index + 2] != NULLVALUE){
        right++;
        i = 2*i + 2;
    }
    return left - right;
}


void insert(int btree[], int key){
    int i = 0;
    while(btree[i] != NULLVALUE){
        if(key < btree[i]){
            i = 2*i + 1;
        }
        else{
            i = 2*i + 2;
        }
    }
    btree[i] = key;
}


void insertBalancedIterative(int btree[], int key){
    if (btree[0] == 0)
    {
        btree[0] = key;
    }
    else{
        int i = 0;
    while(btree[i] != NULLVALUE){
        if(key < btree[i]){
            i = 2*i + 1;
        }
        else{
            i = 2*i + 2;
        }
    }
    btree[i] = key;
    while(i != 0){
        if(checkBalanceIterative(btree, i) > 1){
            if(key < btree[2*i + 1]){
                rightRotate(btree, i);
            }
            else{
                leftRotate(btree, 2*i + 1);
                rightRotate(btree, i);
            }
        }
        else if(checkBalanceIterative(btree, i) < -1){
            if(key > btree[2*i + 2]){
                leftRotate(btree, i);
            }
            else{
                rightRotate(btree, 2*i + 2);
                leftRotate(btree, i);
            }
        }
        i = (i-1)/2;
    }

    }
    

}



 


int search(int btree[], int key){
    int i = 0;
    while(btree[i] != 0){
        if(key == btree[i]){
            printf("Found %d at index %d \n", key, i);
            return i;
        }
        else if(key < btree[i]){
            i = 2*i + 1;
        }
        else{
            i = 2*i + 2;
        }
    }
    return -1;
}





void delete(int btree[], int key){
    int i = 0;
    while(btree[i] != 0){
        if(key == btree[i]){
            btree[i] = 0;
            return;
        }
        else if(key < btree[i]){
            i = 2*i + 1;
        }
        else{
            i = 2*i + 2;
        }
    }
}

void tree_print(int btree[], int i, int h){
    if(i < MAX){
        tree_print(btree, 2*i + 2, h+1);
        for(int j = 0; j < h; j++){
            printf("     ");
        }
        printf("%d\n", btree[i]);
        tree_print(btree, 2*i + 1, h+1);
    }
}
//i is the index of the array
//h is the height of the tree

void print(int *btree, int i, int h){
    if(i < MAX){
        print(btree, 2*i + 2, h+1);
        for(int j = 0; j < h; j++){
            printf("     ");
        }
        printf("%d\n", btree[i]);
        print(btree, 2*i + 1, h+1);
    }
}


void printArray(int *btree){
    for(int i = 0; i < MAX; i++){
        printf("[%d] ", btree[i]);
    }
    printf("\n");
}

//-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
void main(){
    int btree[MAX] = {NULLVALUE};

    insertBalanced(btree, 10);
    insertBalanced(btree, 6);
    insertBalanced(btree, 2);
    insertBalanced(btree, 1);
    insertBalanced(btree, 4);
    insertBalanced(btree, 3);
    int height = btheight(0);
    printf("Height of the tree is %d \n", height);

    

    //delete(btree, 5);

    //search(btree, 5);
   printArray(btree);
   tree_print(btree, 0, 0);

 }