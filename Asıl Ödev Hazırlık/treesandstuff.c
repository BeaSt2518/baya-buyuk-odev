#include <stdio.h>
#include <stdlib.h>

//https://www.youtube.com/watch?v=vRwi_UcZGjU this is the video I used to learn about AVL trees
//https://www.javatpoint.com/insertion-in-avl-tree this was another document
//I looked at the geeks for geeks one and didn't understand it (kind of copied it)

typedef struct NODE_s *NODE;
struct NODE_s {
    NODE left;
    NODE right;
    int key;
    int height;
}NODE_t[1];

typedef struct TREE_s *TREE;
struct TREE_s {
    NODE root;
}TREE_t[1];

NODE node_init(int key) {
    NODE node = (NODE)malloc(sizeof(NODE_t));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->height = 1;
    return node;
}

//somewhat didn't work but I am trying to work it out
int BTHeight(NODE root)
{
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		int rightheight = BTHeight(root->right);
		int leftheight = BTHeight(root->left);
		if (leftheight > rightheight)
		{
			return leftheight +1 ;
		}
		else
		{
			return rightheight +1;
		}
	}
}

void print(NODE n, int h){
	int i;
	if(n != NULL){
		print(n->right,h+1);
		for(i = 0; i < h; i++) {
			printf("     ");
		}
		printf("%d\n", n->key);
        //printf("%d\n", n->height);
		print(n->left, h+1);
	}
}

NODE left_rotation(NODE node) {
   
   //basically just swapping nodes with greater efficiency
   //my other method to swap the keys with gp p and c was not working
    NODE temp = node->right;
    NODE temp2 = temp->left;
    temp->left = node;
    node->right = temp2;
    
    //update heihgts
    node->height = 1 + max(checkheihgt(node->left), checkheihgt(node->right));
    temp->height = 1 + max(checkheihgt(temp->left), checkheihgt(temp->right));
    
    return temp;
}

NODE right_rotation(NODE node) {
    
    //Same as left rotation
    NODE temp = node->left;
    NODE temp2 = temp->right;
    temp->right = node;
    node->left = temp2;
    
    //update heihgts
    node->height = 1 + max(checkheihgt(node->left), checkheihgt(node->right));
    temp->height = 1 + max(checkheihgt(temp->left), checkheihgt(temp->right));

    return temp;
}

int max(int a, int b) {
    if (a >= b) {
        return a;
    }
    else
    {
        return b;
    }
    
}

int checkheihgt(NODE node) {
    if (node == NULL) {
        return 0;
    }
    else
    {
        return node->height;
    }
    
}

int balance_checker(NODE node) {
    if (node == NULL) {
        return 0;
    }
    else
    {
        return checkheihgt(node->left) - checkheihgt(node->right);
    }
    
}

NODE insert(NODE node, int key) {
    int balance;
    
    if (node == NULL) {
        return node_init(key);
    }
    else if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else
    {
        return node;
    }
    node->height = 1 + max(checkheihgt(node->left), checkheihgt(node->right));
    
    balance = balance_checker(node);
    //printf("balance: %d\n" , balance);

    //left left case
    if (balance > 1 && key < node->left->key) {
        return right_rotation(node);
    }
    //right right case
    if (balance < -1 && key > node->right->key) {
        return left_rotation(node);
    }
    //left right case
    if (balance > 1 && key > node->left->key) {
        node->left = left_rotation(node->left);
        return right_rotation(node);
    }
    //right left case
    if (balance < -1 && key < node->right->key) {
        node->right = right_rotation(node->right);
        return left_rotation(node);
    }
    
    return node;
}

void delete(TREE tree, int key){
	if(tree != NULL){
		NODE parent, node;

		parent = (NODE)tree;
		node = tree->root;
		while((node != NULL) && (key != node->key)){
			if(key < node->key){
				parent = node;
				node = node->left;
			}
			else if(key > node->key){
				parent = node;
				node = node->right;
			}
		}

        

		if(node == NULL){
			printf("Node not found.\n");
		}
		else{

			if((node->left == NULL) && (node->right == NULL)){ /* No child */
				if(node == parent->left){
					parent->left = NULL;
				}
				else{
					parent->right = NULL;
				}
			}
			else if((node->left == NULL) && (node->right != NULL)){ /* A single right child. */
				if(node == parent->left){
					parent->left = node->right;
				}
				else{
					parent->right = node->right;
				}
			}
			else if((node->left != NULL) && (node->right == NULL)){ /* A single left child. */
				if(node == parent->left){
					parent->left = node->left;
				}
				else{
					parent->right = node->left;
				}
			}
			else{ /* Two children. */
				NODE max = node->left;
				while(max->right != NULL){
					max = max->right;
				}
				max->right = node->right;
				if(node == parent->left){
					parent->left = node->left;
				}
				else{
					parent->right = node->left;
				}
			}
			free(node);
		}

	}
	else{
		printf("Invalid tree.\n");
	}
}





int main() {
    TREE tree = (TREE)malloc(sizeof(TREE_t));
    tree->root = NULL;
    tree->root = insert(tree->root, 42);
    tree->root = insert(tree->root, 19);
    tree->root = insert(tree->root, 33);
    tree->root = insert(tree->root, 28);
    tree->root = insert(tree->root, 6);
    tree->root = insert(tree->root, 5);
    tree->root = insert(tree->root, 11);
    tree->root = insert(tree->root, 9);
    tree->root = insert(tree->root, 8);
    tree->root = insert(tree->root, 10);
    delete(tree, 9);
    print(tree->root, 0);
    return 0;
}