#include <stdio.h>
#define MAX_TERMS 10

typedef struct {
	int row;
	int col;
	int value;
}element; //희소행렬 행,렬,값을 가진 element 구조체를 정의합니다.

typedef struct {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;//희소행렬 데이터를 가진(최대10개)sparse매트릭스를 정의합니다.

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)
{
	SparseMatrix c;//A와 B의 합을 저장할 C행렬을 선언합니다.
	int ca = 0, cb = 0, cc = 0;//ca=행렬 A의 값을 가진 인자의수,cb=행렬 B의 값을 가진 인자갯수,cc=행렬C의 값을 가진 인자갯수입니다.
	if (a.rows != b.rows || a.cols != b.cols)//두행렬의 크기가 다를때
	{
		fprintf(stderr, "희소행렬 크기에러\n");//에러를 출력하고
		exit(1);//종료합니다.
	}
	c.rows = a.rows;
	c.cols = a.cols;//행렬의 크기는=A=B=C입니다.
	c.terms = 0;


	while (ca < a.terms&&cb < b.terms)//ca(행렬 A인자의 갯수)또는 cb(행렬 B인자의 갯수)가 맞춰질때 까지
	{
		int inda = a.data[ca].row*a.cols + a.data[ca].col;
		int indb = b.data[cb].row*b.cols + b.data[cb].col;//행*열갯수+열 일때 차례대로 순번이 매겨집니다.
		if (inda < indb)//***같은 순번째 값 기준*** 같은 n번째 값이 A행려에 먼저있을때
			c.data[cc++] = a.data[ca++];//C행렬 n번째 값에 A를 넘겨주고 A는의 n+1번째와 B의 n번째 행렬을 비교합니다.
		else if (inda == indb)//행렬 A의 인자와 B의 인자가 같은 위치에 있을때
		{
			c.data[cc].row = a.data[ca].row;
			c.data[cc].col = a.data[ca].col;
			c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;//행렬 A인자의 값과 B인자의 값을 더해줍니다.
		}
		else//***같은 순번째 값 기준*** 같은 n번째 값이 B행려에 먼저있을때
			c.data[cc++] = b.data[cb++];//C행렬 n번째 값에 B의 값을 넘겨주고 B는의 n+1번째와 A의 n번째 행렬을 비교합니다.
	}

	for (; ca < a.terms; ca++)
		c.data[cc++] = a.data[ca++];
	for (; cb < b.terms; cb++)
		c.data[cc++] = b.data[cb++];//비교가 끝난후 값을 가진 인자수가 더많은 행렬에서 비교하지 못한 값들을 입력합니다.
	c.terms = cc;//cc의 값은 비교+나머지추가입력 할때마다 0에서 +1씩 되었으므로 행렬 C의 인자수의 값입니다.
	return c;//sparsematrix c 반환;


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
	SparseMatrix m3;//sparsematrix 구조체 선언

	printf("행렬 A와 B의 사이즈를 입력하시오 ex)3 3 :");
	scanf("%d %d", &a, &b);//행렬 A와 B의 행렬 값을 입력받습니다.
	m1.rows = a;
	m1.cols = b;
	m2.rows = a;
	m2.cols = b;
	printf("행렬 A의 값의 갯수 : ");//값을 가진 인자의 갯수를 입력합니다.
	scanf("%d",&c);
	m1.terms = c;//terms=값을 가진 인자의 갯수

	printf("행렬 A의 값을 초기화 하시오ex)1 1 4\n");
	for (i = 0; i < c; i++)
	{
		printf("행 렬 값 : ");
		scanf("%d %d %d", &m1.data[i].row, &m1.data[i].col, &m1.data[i].value);//terms에 입력된 갯수에 맞게 행,렬,값을 입력합니다.

	}

	printf("행렬 B의 값의 갯수 : ");//B의 값을 가진 인자의 갯수를 입력합니다.
	scanf("%d", &c);
	m2.terms = c;//terms=값을 가진 인자의 갯수
	printf("행렬 B의 값을 초기화 하시오 \n");
	for (i = 0; i < c; i++)
	{
		printf("행  렬  값 :");
		scanf("%d  %d  %d", &m2.data[i].row, &m2.data[i].col, &m2.data[i].value);

	}

	m3 = sparse_matrix_add2(m1, m2);//A행렬과 B행렬을 더하는 함수 호출
	for (i = 0; i < m3.terms; i++)
		printf("%d %d %d\n", m3.data[i].row, m3.data[i].col, m3.data[i].value);//두 행렬의 덧셈 결과 출력

	return 0;
}