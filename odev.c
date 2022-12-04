#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s{
	NODE left;
	NODE right;
	int key;
	void *data;
	int height;
} NODE_t[1];

typedef struct{
	NODE root;
} BST_t[1], *BST;

void print(NODE n, int h){
	int i;
	if(n != NULL){
		print(n->right,h+1);
		for(i = 0; i < h; i++) {
			printf("     ");
		}
		printf("%d\n", n->key);
		print(n->left, h+1);
	}
}

int comparesize(int a, int b)
{
	if(a > b)
	{
		return a;
	}
	else if (b>a)
	{
		return b;
	}
	else
	{
		printf("They are equal\n");
	}
	
}

NODE bst_init_node(int key, void *data){
	NODE n = (NODE)malloc(sizeof(NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	n->height = 1;
	return n;
}

//void insert_rec(NODE, int, void *);

/*
void insert_rec(NODE curr, int key, void *data){
	if(key < curr->key){
		if(curr->left != NULL){
			insert_rec(curr->left, key, data);
		}
		else{
			curr->left = bst_init_node(key, data);
		}
	}
	else if(key > curr->key){
		if(curr->right != NULL){
			insert_rec(curr->right, key, data);
		}
		else{
			curr->right = bst_init_node(key, data);
		}
	}
	else {
		printf("ERROR: Duplicate key: %d. Ignoring...\n\n", key);
		curr = NULL;
	}
}

void insert(BST tree, int key, void *data){
	if(tree != NULL){
		if(tree->root != NULL){
			insert_rec(tree->root, key, data);
		}
		else{
			tree->root = bst_init_node(key, data);
		}
	}
	else{
		printf("Invalid tree.\n");
	}
}
*/

NODE insert_rec(NODE curr, int key, void *data){
	if(curr == NULL){
		curr = bst_init_node(key, data);
	}
	else{
		if(key < curr->key){
			curr->left = insert_rec(curr->left, key, data);
		}
		else if(key > curr->key){
			curr->right = insert_rec(curr->right, key, data);
		}
		else {
			printf("ERROR: Duplicate key: %d. Ignoring...\n\n", key);
		}
	}
	return curr;
}

void insert(BST tree, int key, void *data){
	if(tree != NULL){
		if(tree->root != NULL){
			tree->root = insert_rec(tree->root, key, data);
		}
		else{
			tree->root = bst_init_node(key, data);
		}
	}
	else{
		printf("Invalid tree.\n");
	}
}


void delete(BST tree, int key, void *data){
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
			free(node->data); /*!?*/
			free(node);
		}

	}
	else{
		printf("Invalid tree.\n");
	}
}


BST bst_init(){
	BST t1 = (BST)malloc(sizeof(BST_t));
	t1->root = NULL;
	return t1;
}

void bst_free(BST t){
	//Tentative
	free(t);
}


int main() {
	BST t1 = bst_init();

	insert(t1, 52, NULL);
	insert(t1, 13, NULL);
	insert(t1, 18, NULL);
	insert(t1, 32, NULL);
	insert(t1, 78, NULL);
	insert(t1, 45, NULL);
	insert(t1, 67, NULL);
	insert(t1, 28, NULL);
	insert(t1, 72, NULL);
	insert(t1, 32, NULL);
	insert(t1, 99, NULL);
	insert(t1, 3, NULL);

	print(t1->root,0);

	bst_free(t1);


	return 0;
}






