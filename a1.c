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

//I think this will be unused edit: it is used
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
		//printf("They are equal\n");
	}	
}

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

int balance(NODE root)
{
	if(root == NULL)
	{
		return 0;
	}
	else
	{
		int rightheight = BTHeight(root->right);
		int leftheight = BTHeight(root->left);
		//positive means left heavy and negative means right heavy
		return leftheight - rightheight;
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

NODE leftRotation(NODE gp, NODE p , NODE c)
{
	p->right = c->left;
	c->left = p;
	gp->left = c;
	//update height
	p->height = comparesize(BTHeight(p->left), BTHeight(p->right)) +1;
	c->height = comparesize(BTHeight(c->left), BTHeight(c->right)) +1;

	//return new root
	return c;
}

NODE rightRotation(NODE gp, NODE p , NODE c)
{
	p->left = c->right;
	c->right = p;
	gp->right = c;
	//update height
	p->height = comparesize(BTHeight(p->left), BTHeight(p->right)) +1;
	c->height = comparesize(BTHeight(c->left), BTHeight(c->right)) +1;

	//return new root
	return c;
}


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
	//update height of the current node
	curr->height = comparesize(BTHeight(curr->left), BTHeight(curr->right)) + 1;

	//get the balance factor of the current node 
	int bf = balance(curr);

	//If the tree becomes unbalanced, there are 4 cases
	//left left case
	if(bf > 1 && key < curr->left->key)
	{
		return rightRotation(curr, curr->left, curr->left->left);
	}
	//right right case	
	if(bf < -1 && key > curr->right->key)
	{
		return leftRotation(curr, curr->right, curr->right->right);
	}
	//left right case
	if(bf > 1 && key > curr->left->key)
	{
		curr->left = leftRotation(curr, curr->left, curr->left->right);
		return rightRotation(curr, curr->left, curr->left->left);
	}
	//right left case
	if(bf < -1 && key < curr->right->key)
	{
		curr->right = rightRotation(curr, curr->right, curr->right->left);
		return leftRotation(curr, curr->right, curr->right->right);
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

	insert(t1, 1, NULL);
	insert(t1, 2, NULL);
	insert(t1, 3, NULL);
	insert(t1, 4, NULL);
	insert(t1, 5, NULL);
	insert(t1, 6, NULL);
	insert(t1, 7, NULL);
	insert(t1, 8, NULL);
	insert(t1, 9, NULL);
	insert(t1, 10, NULL);
	insert(t1, 11, NULL);
	insert(t1, 12, NULL);

	print(t1->root,0);

	free(t1);


	return 0;
}

