#include <stdio.h>
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
}element; //������ ��,��,���� ���� element ����ü�� �����մϴ�.

typedef struct {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;//������ �����͸� ����(�ִ�10��)sparse��Ʈ������ �����մϴ�.

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c;//A�� B�� ���� ������ C����� �����մϴ�.
	int ca = 0, cb = 0, cc = 0;//ca=��� A�� ���� ���� �����Ǽ�,cb=��� B�� ���� ���� ���ڰ���,cc=���C�� ���� ���� ���ڰ����Դϴ�.
	if (a.rows != b.rows || a.cols != b.cols)//������� ũ�Ⱑ �ٸ���
	{
		fprintf(stderr, "������ ũ�⿡��\n");//������ ����ϰ�
		exit(1);//�����մϴ�.
	}
	c.rows = a.rows;
	c.cols = a.cols;//����� ũ���=A=B=C�Դϴ�.
	c.terms = 0;


	while (ca < a.terms&&cb < b.terms)//ca(��� A������ ����)�Ǵ� cb(��� B������ ����)�� �������� ����
	{
		int inda = a.data[ca].row*a.cols + a.data[ca].col;
		int indb = b.data[cb].row*b.cols + b.data[cb].col;//��*������+�� �϶� ���ʴ�� ������ �Ű����ϴ�.
		if (inda < indb)//***���� ����° �� ����*** ���� n��° ���� A����� ����������
			c.data[cc++] = a.data[ca++];//C��� n��° ���� A�� �Ѱ��ְ� A���� n+1��°�� B�� n��° ����� ���մϴ�.
		else if (inda == indb)//��� A�� ���ڿ� B�� ���ڰ� ���� ��ġ�� ������
		{
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;//��� A������ ���� B������ ���� �����ݴϴ�.
		}
		else//***���� ����° �� ����*** ���� n��° ���� B����� ����������
			c.data[cc++] = b.data[cb++];//C��� n��° ���� B�� ���� �Ѱ��ְ� B���� n+1��°�� A�� n��° ����� ���մϴ�.
	}

	for (; ca < a.terms; ca++)
		c.data[cc++] = a.data[ca++];
	for (; cb < b.terms; cb++)
		c.data[cc++] = b.data[cb++];//�񱳰� ������ ���� ���� ���ڼ��� ������ ��Ŀ��� ������ ���� ������ �Է��մϴ�.
	c.terms = cc;//cc�� ���� ��+�������߰��Է� �Ҷ����� 0���� +1�� �Ǿ����Ƿ� ��� C�� ���ڼ��� ���Դϴ�.
	return c;//sparsematrix c ��ȯ;


}

int main()
{
	/*int i;
	SparseMatrix m1 = { { { 1,1,5 },{ 2,2,9 } },3,3,2 };
	SparseMatrix m2 = { { { 0,0,5 },{ 2,2,9 } },3,3,2 };
	SparseMatrix m3;
	m3 = sparse_matrix_add2(m1, m2);
	*/
	int i, a, b, c;
	SparseMatrix m1;
	SparseMatrix m2;
	SparseMatrix m3;//sparsematrix ����ü ����

	printf("��� A�� B�� ����� �Է��Ͻÿ� ex)3 3 :");
	scanf("%d %d", &a, &b);//��� A�� B�� ��� ���� �Է¹޽��ϴ�.
	m1.rows = a;
	m1.cols = b;
	m2.rows = a;
	m2.cols = b;
	printf("��� A�� ���� ���� : ");//���� ���� ������ ������ �Է��մϴ�.
	scanf("%d",&c);
	m1.terms = c;//terms=���� ���� ������ ����

	printf("��� A�� ���� �ʱ�ȭ �Ͻÿ�ex)1 1 4\n");
	for (i = 0; i < c; i++)
	{
		printf("�� �� �� : ");
		scanf("%d %d %d", &m1.data[i].row, &m1.data[i].col, &m1.data[i].value);//terms�� �Էµ� ������ �°� ��,��,���� �Է��մϴ�.

	}

	printf("��� B�� ���� ���� : ");//B�� ���� ���� ������ ������ �Է��մϴ�.
	scanf("%d", &c);
	m2.terms = c;//terms=���� ���� ������ ����
	printf("��� B�� ���� �ʱ�ȭ �Ͻÿ� \n");
	for (i = 0; i < c; i++)
	{
		printf("��  ��  �� :");
		scanf("%d  %d  %d", &m2.data[i].row, &m2.data[i].col, &m2.data[i].value);

	}

	m3 = sparse_matrix_add2(m1, m2);//A��İ� B����� ���ϴ� �Լ� ȣ��
	for (i = 0; i < m3.terms; i++)
		printf("%d %d %d\n", m3.data[i].row, m3.data[i].col, m3.data[i].value);//�� ����� ���� ��� ���

	return 0;
}