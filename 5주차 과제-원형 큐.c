#include <stdio.h>
#define MAX_SIZE 10//����ť�� �ִ������+1(�� �ڸ��� ������մϴ�.)


typedef struct {
	int key[MAX_SIZE];//key �迭�� ���� ���� �����Դϴ�.
	int front;//����Ʈ
	int rear;//����
}Circle;//����ť ����ü ���� Circle

void initqueue(Circle *);//�ʱ�ȭ �Լ�
int ISempty(Circle *);//���� ť�� ������� Ȯ���ϴ� �Լ�
int ISfull(Circle *);//���� ť�� �� á���� Ȯ���ϴ� �Լ�
void ADDqueue(Circle *, int);//���ʷ� ���� ���ϴ� �Լ�
int DELqueue(Circle *);//���ʷ� ���� ���� �Լ�

int main()
{
	int c, k, i;//c:�Է��ϰ��� �ϴ� ���� ����,k�Է��ϰ����ϴ°�,iȽ���� �����ϴ� �����Դϴ�.
	Circle queue;//����ť ����ü queue ���� �մϴ�.
	initqueue(&queue);//���� ť�� �ʱ�ȭ �ϴ� �Լ��� ȣ���մϴ�.

	printf("��� �Է��Ͻðڽ��ϱ�? (�ִ� 9��)");
	scanf("%d", &c);//�߰��ϰ���� ���� ������ �Է��մϴ�.
		for (i = 0; i < c; i++)
		{
			printf("���ϴ� ���� �Է��Ͻÿ�");
			scanf("%d", &k);//�ְ����ϴ� ���� ���ʷ� �Է��մϴ�.

			ADDqueue(&queue, k);//����ť�� ���� ���ϴ� �Լ��� ȣ���մϴ�. �̶� k�� �Է¹��� ���� �����ϴ� �����Դϴ�.

		}
	printf("��� �����Ͻðڽ��ϱ�?" );
	scanf("%d", &c);//�����ϰ����ϴ� ���� ������ �Է��մϴ�.
		for (i = 0; i < c; i++)
		{
			printf("������ �� : %d\n", DELqueue(&queue));//���� �����ϴ� �ϼ��� ȣ���ϰ� ������ ���� ����մϴ�.
		}


	printf("1���� ť�� �߰��մϴ�. ���� �Է��Ͻÿ� :");
	scanf("%d", &k);//1���� ť�� ȣ���մϴ�.

	ADDqueue(&queue, k);//�߰� �Լ� ȣ��

	printf("%d\n", DELqueue(&queue));//���� �Լ� ȣ��,������ ���

	return 0;

}

int ISempty(Circle *queue)//�Լ��� ������� Ȯ���ϴ� �Լ�
{
	if (queue->front == queue->rear)//ť�� front�� rear�� ���� ��ġ�� �ִٸ�
		return 1;//1�� ��ȯ �մϴ�.
	else//�ƴϸ�
		return 0;//0�� ��ȯ �մϴ�.
}
int ISfull(Circle *queue)//ť�� ��á���� Ȯ���ϴ� �Լ�
{
	if (((queue->rear + 1) % MAX_SIZE) == queue->front)//rear+1�Ѱ��� ť�� ũ��� ������������ ���� front�� ������(front�� queue�ٷ� �ڿ��ְų� ���� ���� ������)
		return 1;//1�� ��ȯ�մϴ�.
	else
		return 0;//0�� ��ȯ �մϴ�.
}
void ADDqueue(Circle *queue, int data)//�߰� �Լ�
{
	if (ISfull(queue))//ť�� ���� ���¸�
	{
		printf("error, Queue is full!!!\n");//������ ����մϴ�.
		return;//�����ϴ�.
	}

	queue->rear = (queue->rear + 1) % MAX_SIZE;//%MAX_SIZE�� ���� �Լ��̹Ƿ� �ڵ����� �� �����ڸ��� ó������ �ǵ��� ���� �����Դϴ�.
	queue->key[queue->rear] = data;//rear��ġ�� ���� �����ݴϴ�.
}

int DELqueue(Circle *queue)//���� �Լ�
{
	int data = -1;//data�� -1�� ����ϴ�.
	if (ISempty(queue))//ť�� ���������
	{
		printf("error, Queue is empty!!!\n");//�������
		return data;//-1�� ��ȯ�մϴ�.
	}
	queue->front = (queue->front + 1) % MAX_SIZE;//front�� ��ĭ�ڷ� �����ϴ�.(%MAX_SIZE�� �ǳ����� �Ǿ����� ���������Դϴ�.
	data = queue->key[queue->front];//front�ڸ��� ��ġ�� ���� data�� �����ϴ�.
	return data;//data ���

}

void initqueue(Circle *queue)//�ʱ�ȭ �Լ�
{
	queue->front = queue->rear = 0;//front�� rear�� 0���� �ʱ�ȭ �մϴ�.
}
