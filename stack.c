#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct INode {
	int val;
	struct Inode *next;
}INode_t;


typedef struct IStack {
	INode_t *top;
}IStack_t;



int CreateStack(IStack_t **stack)
{
	int ret = 0;
	//IStack_t *stack;
	*stack = (IStack_t *)malloc(sizeof(IStack_t));
	(*stack)->top = NULL;
	//return stack;
	return ret;
}

int PushStack(IStack_t *stack, int data)
{
	INode_t *node = (INode_t *)malloc(sizeof(INode_t));
	node->val = data;
	node->next = stack->top;
	stack->top = node;
	return 0;
}

int IsEmpty(IStack_t *stack)
{

	if (stack->top == NULL) {
		return 1;
	}
	return 0;
}


int PopStack(IStack_t *stack)
{
	int data;
	INode_t *node;
	if (IsEmpty(stack)) {

		printf("stack is empty\n");
		return -1;
	}
	
	data = stack->top->val;
	printf("%s: data=%d\n", __func__, data);
	node = stack->top->next;
	free(stack->top);
	stack->top = node;

}

int main(int argc, char *argv[])
{



	int i = 0;
	int ret = 0;
	IStack_t *stack;
	CreateStack(&stack);

	for(i =  0; i < 16; i ++) {
		ret = PushStack(stack, i);
		
	}

	for(i =  0; i < 17; i ++) {
                ret = PopStack(stack);

        }

	return ret;
}
