#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node_t {
	void *data;
	struct _Node_t *next;
} Node_t;

typedef struct _BiTreeNode_t {
	int data;
	struct BiTreeNode_t *left;
	struct BiTreeNode_t *right;

} BiTreeNode_t;

typedef struct _Stack_t {
        int count;
	Node_t *top;
} Stack_t;

int stack_init(Stack_t *stack)
{
	stack = (Stack_t *)malloc(sizeof(Stack_t));
	if (stack == NULL)
		return -1;
	stack->top = NULL;
	stack->count = 0;

	return 0;
}

int stack_is_empty(Stack_t *stack)
{
	if (stack->count == 0)
		return 1;
	else 
		return 0;
}

int stack_push(Stack_t *stack, void *data)
{
	Node_t *node = NULL;
	Node_t *p = NULL;

	if (stack == NULL)
		return -1;
	node = (Node_t *)malloc(sizeof(Node_t));
	if (node == NULL)
		return -1;
	node->data = data;
	node->next = NULL;

	if (stack->count == 0) {
		stack->top = node;
	} else {
		p = stack->top;
		node->next = p;
		stack->top = node;
	}

	stack->count++;
	return 0;
}

int stack_pop(Stack_t *stack, void *data)
{
	Node_t *p = NULL;

	if (stack == NULL)
		return -1;
        if (stack_is_empty(stack))
		return -1;	
	p = stack->top;
	data = stack->top;
	stack->top = p->next;
	free(p);
	stack->count--;
	return 0;
}

int stack_clear(Stack_t *stack)
{
	void *data;
	if (stack == NULL)
		return -1;
	if (stack_is_empty(stack))
		return 0;
	while (stack->count) {
		stack_pop(stack, data);
	}
}

int stack_destroy(Stack_t *stack)
{
	Node_t *p = NULL;
	if (stack == NULL)
		return -1;
	if (stack_is_empty(stack))
		free(stack);
	else
		return -1;
}
int list_init(Node_t **head)
{
	(*head) = (Node_t *)malloc(sizeof(Node_t));
	if (*head == NULL)
		return -1;
	(*head)->data = NULL;
	(*head)->next = NULL;

	return 0;
}


int list_insert(Node_t *head, void *data)
{
	Node_t *node = (Node_t *)malloc(sizeof(Node_t));

	Node_t *p = NULL;
	if (node == NULL)
		return -1;
	node->data = data;
	if (head->next == NULL)
		head->next = node;
	else {
		p = head->next;
		head->next = node;
		node->next = p;
	}
	return 0;
}

void visit(void *data)
{
	printf("=> %d\n", *((int*)data));
}

int list_traverse(Node_t *head, void(*visit)( void *data))
{
	Node_t *p = NULL;
	if (head == NULL)
		return -1;
	p = head->next;

	while(p) {
		visit(p->data);
		p = p->next;
	}

	return 0;
}

int list_delete(Node_t *head)
{
	Node_t *p = NULL;
	Node_t *q = NULL;

	if (head == NULL)
		return -1;
	p = head->next;
	while (p != NULL) {
		q = p;
		free(q);
		p = p->next;
		
	}
}

int list_destroy(Node_t *head)
{
	if (head != NULL)
		free(head);
}

int main(int argc, char *argv[])
{
	Node_t *head = NULL;
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;

	list_init(&head);
	data1 = 10;
	list_insert(head, &data1);

	data2 = 20;
	list_insert(head, &data2);

	data3 = 30;
	list_insert(head, &data3);
	
	list_traverse(head, visit);

	list_delete(head);
	list_destroy(head);
	return 0;
}
