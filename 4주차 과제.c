#include <stdio.h>
#include <stdlib.h>
#include <time.h> //��� ���� ���� ��ŵ�ϴ�.



typedef struct {
	int col;
	int row;
	int value;
}term; //�� ���Ұ� col(��),row(��),value(��)�� ����ü�� term�̶�� ��Ī�� ����Ͽ� �����մϴ�.


clock_t start, finish; //���� �ð� start������ ����ð� finish������ ������ �ݴϴ�.
double duration; //�ɸ� �ð��� ������ ������ ������ �ݴϴ�.


void transpose(term *a, term *b) //a����ü �迭�� ��� ���� ���ιٲپ� b����ü �迭�� �����ϴ� �Լ��Դϴ�.
{
	start = clock(); //���� �ð��� �����մϴ�.

	int n, i, j, currentb;//2�� for���� ����ϱ⿡ ���� ���� i�� j�� �����ϰ� �迭�� ������ �����ϴ� �������� n, 1�� ������ ���ʷ� ���ϱ����� current ������ �����մϴ�.
	n = a[0].value; //���� ����n�� ������ ������ �ʱ�ȭ�մϴ�.
	b[0].row = a[0].col;//a�� ���ǰ���=b�� ���ǰ���
	b[0].col = b[0].row;//a�� ���ǰ���=b�� ���ǰ���
	b[0].value = n;//b�� ������ ������ a�� ������ ������ �����ϴ�.
	if (n > 0) //������ ���� 0�� �ƴ� ���
	{
		currentb = 1;//ī��Ʈ�� 1����(a[0]����ü�� ����� ��,��,���������� ������ �ֱ⶧���� ����)
		for (i = 0; i < a[0].col; i++) //������ 0��° ������ ���ʷ� ���մϴ�. 
			for (j = 1; j <= n; j++)//a[1]���� a[1000]������ ���ϴ�. 
				if (a[j].col == i)//j��° ���� �ִ� a�� ���Ұ� i�� ���ٸ�
				{
					b[currentb].row = a[j].col; 
					b[currentb].col = a[j].row;
					b[currentb].value = a[j].value; //cuurrentb��° b����ü �迭�� ����
					currentb++; //������° b����ü �迭�� �߰��ؾ��ϹǷ� currentb�� 1�� ������Ų��.
				}
	}
	finish = clock();//���� �ð��� �����մϴ�.

	duration = ((double)finish - (double)start) / CLOCKS_PER_SEC; //���۽ð��� ����ð� ������ �ɸ� �ð��� duration ������ �����մϴ�.

}


int main() //�����Լ�
{
	int n, i; //n��° �迭�� �����ϱ� ���� ����� �����Դϴ�.
	term A[1001], B[1001]; //���� ������ ���� A����ü�迭, �� ������ �������� �ٲ��� B����ü �迭 ���� 100���� ������ �ݴϴ�.


	A[0].value = 1000;//1000���� ���� 0�̾ƴ� ���Ҹ� �����Ƿ� A[0].value�� ���� 1000���� ���ݴϴ�.
	for (n = 1; n < 1001; n++) //ù��° ���Һ��� ������ 1000��° ���ұ���
		A[n].value = rand() % 5+1; //A.value�� ���ҵ��� �������� 1���� 5������ ���� �����ϴ�.

	for (i = 0; i <= A[0].value; i++)
		printf("%d   %d   %d   %d\n", i, A[i].row, A[i].col, A[i].value);

	printf("\n\n\n\n\n\n\n\n\n\n");



	transpose(A, B);//�Լ��� ȣ���Ͽ� �۾��� �ǽ��մϴ�.
	


	for (i = 0; i <= B[0].value; i++) 
		printf("%d   %d   %d   %d\n", i, B[i].row, B[i].col, B[i].value);




		printf("%f�� �Դϴ�.\n", duration);//�ɸ��ð��� ȭ�鿡 ����մϴ�.

		return 0;


	}

