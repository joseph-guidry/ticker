#include "avlTicker.h"


void destroy_tree(Node * t)
{
	if (t != NULL)
	{
		destroy_tree(t->child[0]);
		destroy_tree(t->child[1]);
		free(t->key);
		free(t);
	}
}

int get_height(Node * t)
{
	if (t != NULL)
	{
		return t->height;
	}
	else
	{
		return 0;
	}
}

void adjust_height(Node * t)
{
	//Double check and adjust
	if(t != NULL)
		t->height = 1 + Max(get_height(t->child[0]), get_height(t->child[1]));
}

void rotate(Node ** root, int d)
{
	//Implemenation of AVL tree rotation 
	Node * oldRoot;
	Node * newRoot;
	Node * oldMiddle;
	
	oldRoot = *root;
	newRoot = oldRoot->child[d];
	oldMiddle = newRoot->child[!d];
	
	oldRoot ->child[d] = oldMiddle;
	newRoot->child[!d] = oldRoot; 
	*root = newRoot;
	
	//Adjust heights after rotation
	adjust_height((*root)->child[!d]); 	//old
	adjust_height(*root);				//new
}

void rebalance(Node **t)
{
	//Checks the height of the nodes in the tree, will rotate if required in the appropriate direction.
	int d;
	
	if (*t != NULL)
	{
		for (d = 0; d < 2; d++)
		{
			if (get_height((*t)->child[d]) > get_height((*t)->child[!d]) + 1)
			{
				if( get_height((*t)->child[d]) > get_height((*t)->child[!d]))
				{
					rotate(t, d);
				}
				else
				{
					rotate(&(*t)->child[d], !d);
					rotate(t, d);
				}
				
				return;
			}
		}
		adjust_height(*t);
	}
}

void insert(Node **t, void * key, int size, int (*compare)(const void * a, const void * b), void (*display)(const void * data1), void (*update)(Node ** temp, void * data1) )
{
	if (*t == NULL)
	{
		*t = malloc(sizeof(struct Node));
		if (t == NULL)
		{
			fprintf(stderr, "Memory error\n");
			return;
		}
		
		(*t)->child[0] = NULL;
		(*t)->child[1] = NULL;
		
		//Insert the data into a new BST.
		(*t)->key = malloc(size);
		memcpy((*t)->key, key, size);
		(*t)->height = 1;
		
		//Pass utility functions used by nodes
		(*t)->compare = compare;
		(*t)->display = display;
		(*t)->modify =  update;
		
		
		return;
	}
	else if ( compare(key, (*t)->key)  < 0 )
	{
		//Try modifying current node with input info
		(*t)->modify(t , key );
		return;
	}
	else
	{
		insert(&(*t)->child[(*t)->compare(key, (*t)->key)], key, size, compare, display, update);
		rebalance(t);
		return;
	}
}

void print_in_order(Node * t)
{
	if ( t != NULL)
	{ 	
		print_in_order(t->child[0]);
		t->display(t->key);
		print_in_order(t->child[1]);
	}
}

void check(Node * root)
{
	int i;
	if ( root != NULL)
	{
		for ( i = 0; i < 2; i++)
		{
			check(root->child[i]);
		}
		root->height == 1 + Max(get_height(root->child[0]), get_height(root->child[1]));
	}
}

