#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;
	struct Node * left;
	struct Node * right;
}NODE;

NODE * NewNode(int data);
NODE * InsertAtEnd(int data);
NODE * Traverse(NODE * root);

NODE * NewNode(int data)
{
	NODE* _newNode = ((NODE *)malloc(sizeof(NODE)));
	_newNode->data = data;
	return _newNode;
}

NODE * Traverse(NODE * _node)
{
	if(_node->left == NULL)
		return _node->left;
	else if(_node->right == NULL)
		return _node->right;
	Traverse(_node->left);
}

int main()
{
	NODE *tree = NewNode(3);
	printf("tree root node is %d\n",tree->data);
	return 0;
}
