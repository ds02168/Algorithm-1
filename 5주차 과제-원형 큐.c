#include <stdio.h>
#define MAX_SIZE 10//원형큐의 최대사이즈+1(한 자리는 비워야합니다.)


typedef struct {
	int key[MAX_SIZE];//key 배열은 값이 들어가는 공간입니다.
	int front;//프론트
	int rear;//레어
}Circle;//원형큐 구조체 정의 Circle

void initqueue(Circle *);//초기화 함수
int ISempty(Circle *);//원형 큐가 비었는지 확인하는 함수
int ISfull(Circle *);//원형 큐가 다 찼는지 확인하는 함수
void ADDqueue(Circle *, int);//차례로 값을 더하는 함수
int DELqueue(Circle *);//차례로 값을 빼는 함수

int main()
{
	int c, k, i;//c:입력하고자 하는 값의 갯수,k입력하고자하는값,i횟수를 저장하는 변수입니다.
	Circle queue;//원형큐 구조체 queue 선언 합니다.
	initqueue(&queue);//원형 큐를 초기화 하는 함수를 호출합니다.

	printf("몇개를 입력하시겠습니까? (최대 9개)");
	scanf("%d", &c);//추가하고싶은 값의 갯수를 입력합니다.
		for (i = 0; i < c; i++)
		{
			printf("원하는 값을 입력하시오");
			scanf("%d", &k);//넣고자하는 값을 차례로 입력합니다.

			ADDqueue(&queue, k);//원형큐에 값을 더하는 함수를 호출합니다. 이때 k는 입력받은 값을 저장하는 변수입니다.

		}
	printf("몇개를 삭제하시겠습니까?" );
	scanf("%d", &c);//삭제하고자하는 값의 갯수를 입력합니다.
		for (i = 0; i < c; i++)
		{
			printf("삭제된 값 : %d\n", DELqueue(&queue));//값을 삭제하는 하수를 호출하고 삭제한 값을 출력합니다.
		}


	printf("1개의 큐를 추가합니다. 값을 입력하시오 :");
	scanf("%d", &k);//1개의 큐를 호출합니다.

	ADDqueue(&queue, k);//추가 함수 호출

	printf("%d\n", DELqueue(&queue));//삭제 함수 호출,삭제값 출력

	return 0;

}

int ISempty(Circle *queue)//함수가 비었는지 확인하는 함수
{
	if (queue->front == queue->rear)//큐의 front와 rear가 같은 위치에 있다면
		return 1;//1을 반환 합니다.
	else//아니면
		return 0;//0을 반환 합니다.
}
int ISfull(Circle *queue)//큐가 다찼는지 확인하는 함수
{
	if (((queue->rear + 1) % MAX_SIZE) == queue->front)//rear+1한값을 큐의 크기로 나머지연산한 값이 front와 같으면(front가 queue바로 뒤에있거나 서로 끝에 있으면)
		return 1;//1을 반환합니다.
	else
		return 0;//0을 반환 합니다.
}
void ADDqueue(Circle *queue, int data)//추가 함수
{
	if (ISfull(queue))//큐가 다찬 상태면
	{
		printf("error, Queue is full!!!\n");//에러를 출력합니다.
		return;//끝냅니다.
	}

	queue->rear = (queue->rear + 1) % MAX_SIZE;//%MAX_SIZE는 원형 함수이므로 자동으로 끝 다음자리가 처음으로 되돌아 가기 위함입니다.
	queue->key[queue->rear] = data;//rear위치에 값을 더해줍니다.
}

int DELqueue(Circle *queue)//삭제 함수
{
	int data = -1;//data에 -1을 담습니다.
	if (ISempty(queue))//큐가 비어있으면
	{
		printf("error, Queue is empty!!!\n");//에러출력
		return data;//-1을 반환합니다.
	}
	queue->front = (queue->front + 1) % MAX_SIZE;//front를 한칸뒤로 보냅니다.(%MAX_SIZE는 맨끝에서 맨앞으로 오기위함입니다.
	data = queue->key[queue->front];//front자리에 위치한 값을 data에 보냅니다.
	return data;//data 출력

}

void initqueue(Circle *queue)//초기화 함수
{
	queue->front = queue->rear = 0;//front와 rear을 0으로 초기화 합니다.
}
