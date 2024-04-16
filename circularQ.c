/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void) {
	printf("[-------------2023041004 ------- 한윤수 --------------]\n");
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			//만약 큐가 가득 찼을 경우 명령 실행 중지
			if (isFull(cQ)) {
				printf("큐가 가득 찼습니다.\n");
			} else {
				data = getElement();
				enQueue(cQ, data);
			}
			break;
		case 'd': case 'D':
			//만약 큐가 비어있을 경우 명령 실행 중지
			if (isEmpty(cQ)) {
				printf("큐가 비어있습니다.\n");
			} else {
				deQueue(cQ, &data);
				printf("%c가 삭제되었습니다.\n", data);
			}
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement() {
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ) {
	//프론트와 리어가 같을 경우 (앞과 뒤의 위치가 같을 경우) 큐가 비어있는 것으로 판단
	return cQ->front == cQ->rear;
}

/* complete the function */
int isFull(QueueType *cQ) {
	//리어의 다음 위치가 프론트일 경우 큐가 가득 찬 것으로 판단
	return (cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front;
}

/* complete the function */
void enQueue(QueueType *cQ, element item) {
	//리어의 위치를 한 칸 뒤로 옮긴 후 그 위치에 아이템을 넣음
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
	cQ->queue[cQ->rear] = item;
	return;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item) {
	//프론트의 위치를 한 칸 뒤로 옮긴 후 그 위치의 아이템을 반환하고 그 위치를 공백으로 초기화
	cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE;
	*item = cQ->queue[cQ->front];
	cQ->queue[cQ->front] = ' ';
    return;
}


void printQ(QueueType *cQ) {
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


