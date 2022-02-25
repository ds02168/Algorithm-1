#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1//������ ��ȣ��� ���� 1�Դϴ�.
#define MAX_STACK_SIZE 10//�ִ� ���� ũ��� 10�Դϴ�.

typedef struct {
	int key;
	/* �ٸ��ʵ� */
}element;//���� ����ü�� �����մϴ�.

element stack[MAX_STACK_SIZE];//�ִ� ���� ũ�⸸ŭ ������ �����մϴ�.
int top = -1;//top�� �ƹ��͵� ���� ���¿��� -1�Դϴ�.

void push(element);//���� �Լ� ����
element pop();//���� �Լ� ����
void stackFull();//Full �Լ� ����
void stackEmpty();//Empty �Լ� ����

int main()
{
	int i,j,c; //i�� ���ϴ� ������ �������Ѻ���, j�� �޴��� �����ϱ� ���� ����, c�¿��ϴ� ������ �Է¹ޱ� ���� �����Դϴ�.
	element item;//stack ����ü�� �����͸� �ѱ������ ����ü�Դϴ�.


	while (1)
	{
		for (i = 0; i <= top; i++)
			printf("���� %d��° ���� : %d\n", i, stack[i].key);//���� ����ü�� ��Ȳ�� ������ݴϴ�.


		printf("���ϴ� �޴��� �����ּ���\n");//�޴� ���
		printf("1.�߰�, 2.����, 3.���� :");
		scanf("%d", &j);//�޴� ����
		
		if (j == 1)//�߰��� ����
		{
			printf("�Է��� ������ ������ �Է��Ͻÿ� (�ִ밹�� %d��): ",(MAX_STACK_SIZE-(top+1)));//�ִ�ũ��-(top+1)�� ���� �����ִ� ������ �����Դϴ�.
			scanf("%d", &c);//�Է��ϰ����ϴ� ������ ������ �޽��ϴ�.

			for (i = 0; i < c; i++)//i�� 0���� �Է��ϰ����ϴ� ������ ������ŭ
			{
				printf("�߰��� ���� : ");
				scanf("%d", &item.key);//������ key������ �Է¹޽��ϴ�.

				push(item);//���� ����ü�� �־��ݴϴ�.
			}
		}

		if (j == 2)//2�� �޴� ���ý�
		{
			printf("������ ������ ������ �Է��Ͻÿ� (�ִ� %d��): ", (top + 1));//���� ������ ������ top+1���Դϴ�.(top==-1���� �����̹Ƿ�)
			scanf("%d", &c);//�����ϰ����ϴ� ������ ������ �޽��ϴ�.
			
			for (i = 0; i < c; i++)//i�� 0���� �����ϰ����ϴ� ������ŭ
				printf("������ ���� %d\n", pop());//������ ���� ȭ�鿡 ����մϴ�.

		}
		if (j == 3)//3�����ý�
		{
			printf("�̿��� �ּż� �����մϴ�. �����մϴ�.\n");
			break;//����
		}
		printf("\n\n");

	}

	return 0;

}

void push(element item)//���� ���� �Լ�
{
	if (top >= MAX_STACK_SIZE - 1)//���� �ִ�ũ��-1���� ũ�ų� ���ٸ�
		stackFull();//full�Լ� ȣ��

	stack[++top] = item;//�׷��� �ʴٸ� top+1 ��ġ�� item���� �־��ݴϴ�.
}

element pop()//���� ���� �Լ�
{
	if (top == -1)//������ ���������
		stackEmpty();//empty �Լ� ȣ��
	
	return stack[top--];//top�� ��ġ�� ���� ������Ű�� top�� -1�մϴ�.
}

void stackFull()//full �Լ�
{
	fprintf(stderr, "stack is full, cannot add element\n");//���� ���
	exit(EXIT_FAILURE);//����

}

void stackEmpty()//empty �Լ�
{
	fprintf(stderr, "stac is empty, cannot delete element\n");//���� ���
	exit(EXIT_FAILURE);//����

}