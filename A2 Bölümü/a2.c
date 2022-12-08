#include <stdio.h>
#include <stdlib.h>

void set_root(int *tree, int root){
    tree[0] = root;
}

void set_left(int *tree, int root, int left){
    tree[root*2+1] = left;
}

void set_right(int *tree, int root, int right){
    tree[root*2+2] = right;
}

void print_tree(int *tree, int root){
    printf("%d ", tree[root]);
    if(tree[root*2+1] != 0)
        print_tree(tree, root*2+1);
    if(tree[root*2+2] != 0)
        print_tree(tree, root*2+2);
}


void main(){
    int tree[10];
    set_left(tree, 0, 1);
    set_right(tree, 0, 2);
    set_left(tree, 1, 3);
    set_right(tree, 1, 4);
    set_left(tree, 2, 5);
    print_tree(tree, 0);
 }