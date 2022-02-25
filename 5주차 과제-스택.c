#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1//실패의 기호상수 값은 1입니다.
#define MAX_STACK_SIZE 10//최대 스텍 크기는 10입니다.

typedef struct {
	int key;
	/* 다른필드 */
}element;//스텍 구조체를 정의합니다.

element stack[MAX_STACK_SIZE];//최대 스택 크기만큼 스택을 정의합니다.
int top = -1;//top은 아무것도 없는 상태에서 -1입니다.

void push(element);//삽입 함수 정의
element pop();//삭제 함수 정의
void stackFull();//Full 함수 정의
void stackEmpty();//Empty 함수 정의

int main()
{
	int i,j,c; //i는 원하는 갯수를 세기위한변수, j는 메뉴를 선택하기 위한 변수, c는원하는 갯수를 입력받기 위한 변수입니다.
	element item;//stack 구조체에 데이터를 넘기기위한 구조체입니다.


	while (1)
	{
		for (i = 0; i <= top; i++)
			printf("현재 %d번째 스텍 : %d\n", i, stack[i].key);//현재 구조체를 상황을 출력해줍니다.


		printf("원하는 메뉴를 눌러주세요\n");//메뉴 출력
		printf("1.추가, 2.삭제, 3.종료 :");
		scanf("%d", &j);//메뉴 선택
		
		if (j == 1)//추가를 고를시
		{
			printf("입력할 스택의 갯수를 입력하시오 (최대갯수 %d개): ",(MAX_STACK_SIZE-(top+1)));//최대크기-(top+1)은 현재 들어갈수있는 스택의 갯수입니다.
			scanf("%d", &c);//입력하고자하는 스택의 갯수를 받습니다.

			for (i = 0; i < c; i++)//i는 0부터 입력하고자하는 스택의 갯수만큼
			{
				printf("추가할 스텍 : ");
				scanf("%d", &item.key);//스텍의 key값들을 입력받습니다.

				push(item);//스텍 구조체로 넣어줍니다.
			}
		}

		if (j == 2)//2번 메뉴 선택시
		{
			printf("삭제할 스택의 갯수를 입력하시오 (최대 %d개): ", (top + 1));//현재 스텍의 갯수는 top+1개입니다.(top==-1부터 시작이므로)
			scanf("%d", &c);//삭제하고자하는 스택의 갯수를 받습니다.
			
			for (i = 0; i < c; i++)//i가 0부터 삭제하고자하는 갯수만큼
				printf("삭제된 스택 %d\n", pop());//삭제한 값을 화면에 출력합니다.

		}
		if (j == 3)//3번선택시
		{
			printf("이용해 주셔서 감사합니다. 종료합니다.\n");
			break;//종료
		}
		printf("\n\n");

	}

	return 0;

}

void push(element item)//스텍 삽입 함수
{
	if (top >= MAX_STACK_SIZE - 1)//스텍 최대크기-1보다 크거나 같다면
		stackFull();//full함수 호출

	stack[++top] = item;//그렇지 않다면 top+1 위치에 item값을 넣어줍니다.
}

element pop()//스텍 삭제 함수
{
	if (top == -1)//스텍이 비어있을시
		stackEmpty();//empty 함수 호출
	
	return stack[top--];//top에 위치한 값을 삭제시키고 top을 -1합니다.
}

void stackFull()//full 함수
{
	fprintf(stderr, "stack is full, cannot add element\n");//에러 출력
	exit(EXIT_FAILURE);//종료

}

void stackEmpty()//empty 함수
{
	fprintf(stderr, "stac is empty, cannot delete element\n");//에러 출력
	exit(EXIT_FAILURE);//종료

}