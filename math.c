#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MATH_RETURN_BASE	10000000
#define OK	(MATH_RETURN_BASE+1)
#define ERROR	(MATH_RETURN_BASE+2)

typedef struct INode {
	int data;
	struct INode *next;
} INode_t;


typedef struct IStack {
	INode_t *top;
	int count;
} IStack_t;


int CreateStack(IStack_t **stack)
{
	printf("%s: sizeof(IStack_t) = %ld \n", __func__, sizeof(IStack_t));
	*stack = (IStack_t *)malloc(sizeof(IStack_t));
	(*stack)->top = NULL;
	(*stack)->count = 0;
	return OK;
}

int IsStackEmpty(IStack_t *stack)
{
	if (stack->count == 0) {
		printf("%s: Stack is empty \n", __func__);
		return OK;
	}
	return ERROR;
}

int StackPush(IStack_t *stack, int data)
{
	INode_t *node = NULL;

	if (stack == NULL) {
		printf("%s: stack pointer is NULL \n", __func__);
		return ERROR;
	}
	
	node = (INode_t *)malloc(sizeof(INode_t));
	if (node == NULL) {
		printf("%s: alloc memory failed \n", __func__);
		return ERROR;
	}

	node->data = data;
	node->next = stack->top;
	stack->top = node;
 	stack->count++;
	return OK;

}

int StackPop(IStack_t *stack)
{

	INode_t *node = NULL;
	int val;
	
	if (stack == NULL) {
		printf("%s: stack pointer is NULL \n", __func__);
		return ERROR;
	}
	
	if (IsStackEmpty(stack) == OK) {
		return ERROR;
	}

	node = stack->top;
	val = node->data;

	printf("%s: data=%d      \n", __func__, node->data);
	stack->top = node->next;

	free(node);
	node = NULL;
	stack->count--;
	
	return val;
}

int StackGet(IStack_t *stack)
{
	if (IsStackEmpty(stack) == OK) {
		printf("%s: stack is empty\n", __func__);
		return ERROR;
	}

	return (stack->top->data);
}

int Priority(char ch)
{

	switch(ch) {
		case '(':
			return 3;
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
	}
	return OK;
}


int main(int argc, char *argv[])
{
	int ret = 0;
	int i = 0;
        int tmp = 0;
        int j = 0;
	char str[100] = {0};

	IStack_t *vStackOpt = NULL;
	ret = CreateStack(&vStackOpt); //operator
	if (ret != OK) {
		printf("Init fail\n");
		exit(1);
	}


	IStack_t *vStackNum = NULL;
	ret = CreateStack(&vStackNum);
	if (ret != OK) {
		printf("Init Fail\n");
		exit(1);
	}

	printf("Please input operator: \n");
	scanf("%s", str);

	while(str[i] != '\0' || IsStackEmpty(vStackOpt) != OK) {
		//printf("%s: line:%d\n", __func__, __LINE__);

		if (str[i] >= '0' && str[i] <= '9') {
			tmp = tmp * 10 + str[i] - '0';
			i++;

			if (str[i]  < '0' || str[i] > '9') {
				//printf("-------------push data=%d\n", tmp);
				StackPush(vStackNum, tmp);
				tmp = 0;
			}
			printf("%s: line:%d\n", __func__, __LINE__);
		} else {

			//if ((IsStackEmpty(vStackOpt) == OK || (StackGet(vStackOpt) == '(' && str[i]) != ')') || Priority(str[i]) > Priority(StackGet(vStackOpt))) {

			if((IsStackEmpty(vStackOpt) == OK) || (StackGet(vStackOpt) == '(' && str[i] != ')') || Priority(str[i]) > Priority(StackGet(vStackOpt))) {
				StackPush(vStackOpt, str[i]);
				i++;
				continue;
			}
			if(StackGet(vStackOpt) == '(' && str[i] == ')') {
				StackPop(vStackOpt);
				i++;
				continue;

			}
			printf("%s: line:%d\n", __func__, __LINE__);
			if ((str[i] == '\0' && IsStackEmpty(vStackOpt) != OK) || (str[i] == ')' && StackGet(vStackOpt) != '(') || Priority(str[i]) <= Priority(StackGet(vStackOpt))) //stack pop and caculate the result 
			{
				switch (StackPop(vStackOpt)) {
					case '+':
						StackPush(vStackNum, StackPop(vStackNum)+StackPop(vStackNum));
						break;
					case '-':
						j = StackPop(vStackNum);
						StackPush(vStackNum, StackPop(vStackNum)-j);
						break;
					case '*':
						StackPush(vStackNum, StackPop(vStackNum)*StackPop(vStackNum));
						break;
					case '/':
						j= StackPop(vStackNum);
						StackPush(vStackNum, StackPop(vStackNum)/j);
						break;
					default:
						break;
				}
				continue;
			}
			printf("%s: line:%d\n", __func__, __LINE__);
		}

	}

	printf("the result = %d\n", StackPop(vStackNum));
}
