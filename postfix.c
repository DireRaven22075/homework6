/** 
 * postfix.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x); char postfixPop(); void evalPush(int x);
int evalPop(); void getInfix(); precedence getToken(char symbol); precedence getPriority(char x);
void charCat(char* c); void toPostfix(); void debug(); void reset(); void evaluation();

int main() {
	printf("[-------------2023041004 ------- 한윤수 --------------]\n");
	char command;
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol) {
	switch(symbol) {
		case '(' : return lparen;
		case ')' : return rparen;
		case '+' : return plus;
		case '-' : return minus;
		case '/' : return divide;
		case '*' : return times;
		default : return operand;
	}
}

precedence getPriority(char x) {
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c) {
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

void toPostfix() {
	char *exp = infixExp; /* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') {
		if (getToken(*exp) == operand) {
			//연산자가 아니면 postfixExp에 추가
			charCat(exp);
		}
		else {
			//연산자일 경우
			if (postfixStackTop == -1) {
				//스택이 비어있는 경우
				//스택이 비어있으면 연산자를 스택에 push
				postfixPush(*exp);
			}
			else {
				//스택이 비어있지 않은 경우
				//현재 연산자의 우선순위가 스택의 top에 있는 연산자의 우선순위보다 높은 경우
				if (getPriority(*exp) > getPriority(postfixStack[postfixStackTop])) {
					postfixPush(*exp);
				}
				//현재 연산자의 우선순위가 스택의 top에 있는 연산자의 우선순위보다 낮거나 같은 경우
				else {
					//스택의 top에 있는 연산자의 우선순위가 높아질 때까지 pop하여 postfixExp에 추가
					while (postfixStackTop != -1 && getPriority(*exp) <= getPriority(postfixStack[postfixStackTop])) {
						x = postfixPop();
						charCat(&x);
					}
					//현재 연산자를 스택에 push
					postfixPush(*exp);
				}
			}
		}
		exp++;
	}
	//스택에 남아있는 연산자들을 모두 pop하여 postfixExp에 추가
	while (postfixStackTop != -1) {
		x = postfixPop();
		charCat(&x);
	}
}

void debug() {
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);
	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);
	printf("\n");
}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() {
	int i = 0; char token;
	int operand1, operand2;
	//표현식 끝까지 반복
	while (postfixExp[i] != '\0') {
		//토큰을 읽어옴
		token = postfixExp[i];
		if (getToken(token) == operand) {
			//피연산자일 경우 스택에 push
			//숫자로 변환하기 위해 ascii 코드에서 '0'을 빼줌 ('3' -> 3)
			evalPush(token - '0'); 
		} else {
			//연산자일 경우 pop을 통해 피연산자 2개를 가져온 후 연산 수행
			operand2 = evalPop();
			operand1 = evalPop();
			switch (token) { //연산 수행
				case '+': evalPush(operand1 + operand2); break;
				case '-': evalPush(operand1 - operand2); break;
				case '*': evalPush(operand1 * operand2); break;
				case '/': evalPush(operand1 / operand2); break;
			}
		}
		i++;
	}
	//계산 결과를 evalResult에 저장
	evalResult = evalPop();
	printf("계산결과: %d\n", evalResult);
}

