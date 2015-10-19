#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int data;
	struct Node *next;
};

//void Insert(struct Node *_node,int data)
//{
	//struct Node temp = _node;
//	struct Node * curr = TraverseToTail(_node);
//	curr->next = (struct Node *)malloc(sizeof(struct Node));
//	curr->next->data = data;
//	curr->next->next = NULL;
//}
struct Node * TraverseToTail(struct Node *head)
{
	struct Node *tail;
	//printf("its here traversetotail 1\n");
	tail = head;
	while(tail->next != NULL)
	{
		tail = tail->next;
	}
	return tail;
}

struct Node * NewNode(int data)
{
	struct Node * _newNode = (struct Node *)malloc(sizeof(struct Node));
	_newNode->data = data;
	_newNode->next = NULL;
	return _newNode;
}
void InsertAtEnd(struct Node *_node,int data)
{
        struct Node * curr = TraverseToTail(_node);
	curr->next = NewNode(data);
}

void PrintList(struct Node *head);

struct Node * ReverseList(struct Node** head,struct Node* currNode)
{
	struct Node* tempCurr = currNode;
	struct Node* tempHead;
	printf("outside every thing value of tempCurr and currNode  %d %d\n",tempCurr->data,currNode->data);
	if(currNode->next == NULL)
	{
		printf("in if condition ReversalList() before head %d\n",currNode->data);
		tempHead = *head;
		*head = currNode;
                currNode->next = NULL;
//		printf("in if condition ReversalList() after head currNode %d %d\n",*head->data,currNode->data);
		return *head;
	}
	else
	{
		printf("in else condition ReversalList() before call %d\n",currNode->data);
		struct Node * temp = ReverseList(head,currNode->next);
		printf("in else condition ReversalList() after call temp tempCurr  %d %d\n",temp->data,tempCurr->data);
                temp->next = currNode;
		if(temp == tempHead)
		{
			printf("in the condition of putting null at the end");
			temp->next->next = NULL;
		}
                //currNode->next = NULL;
                //PrintList(head);
		temp->next->next = NULL;
                return temp->next;
	}
}

void PrintList(struct Node *head)
{
        printf("Inside print list\n");
	while(head != NULL)
	{
		printf("%d\n",head->data);
		head= head->next;
	}
}

void PrintListTest(struct Node *head)
{
        int i =0;
        //while(head->next!=NULL)
        while(i<=10)
        {
                printf("%d\n",head->data);
                head= head->next;
                i++;
        }
}


int main()
{
	//printf("its here main 3\n");
	struct Node *_list = (struct Node *)malloc(sizeof(struct Node));
        //_list = (struct Node *)malloc(sizeof(struct Node));
        _list->data = 10;

	//printf("its here main  4\n");
	InsertAtEnd(_list,1);
	InsertAtEnd(_list,2);
	InsertAtEnd(_list,3);
	InsertAtEnd(_list,4);
	InsertAtEnd(_list,5);
	InsertAtEnd(_list,234);
	InsertAtEnd(_list,98898);
	//int x;
	//printf("")
	PrintList(_list);

	printf("Printing reversal of list\n");
	ReverseList(&_list,_list);
	printf("after reversal of list before print\n");
	PrintList(_list);
	puts("after printlist \n");
	return 0;
}
