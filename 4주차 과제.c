#include <stdio.h>
#include <stdlib.h>
#include <time.h> //헤더 파일 포함 시킵니다.



typedef struct {
	int col;
	int row;
	int value;
}term; //각 원소가 col(열),row(행),value(값)인 구조체를 term이라는 별칭을 사용하여 선언합니다.


clock_t start, finish; //시작 시간 start변수와 종료시간 finish변수를 선언해 줍니다.
double duration; //걸린 시간을 저장할 변수를 선언해 줍니다.


void transpose(term *a, term *b) //a구조체 배열의 행과 열을 서로바꾸어 b구조체 배열에 저장하는 함수입니다.
{
	start = clock(); //시작 시각을 측정합니다.

	int n, i, j, currentb;//2중 for문을 사용하기에 정수 변수 i와 j를 선언하고 배열의 갯수를 저장하는 정수변수 n, 1번 열부터 차례로 비교하기위한 current 변수를 선언합니다.
	n = a[0].value; //정수 변수n에 원소의 갯수를 초기화합니다.
	b[0].row = a[0].col;//a의 열의갯수=b의 행의갯수
	b[0].col = b[0].row;//a의 행의갯수=b의 열의갯수
	b[0].value = n;//b의 원소의 갯수는 a의 원소의 갯수와 같습니다.
	if (n > 0) //원소의 값이 0이 아닌 행렬
	{
		currentb = 1;//카운트는 1부터(a[0]구조체는 행렬의 행,렬,갯수에대한 정보가 있기때문에 제외)
		for (i = 0; i < a[0].col; i++) //열들을 0번째 열부터 차례로 구합니다. 
			for (j = 1; j <= n; j++)//a[1]부터 a[1000]까지의 셉니다. 
				if (a[j].col == i)//j번째 열에 있는 a의 원소가 i와 같다면
				{
					b[currentb].row = a[j].col; 
					b[currentb].col = a[j].row;
					b[currentb].value = a[j].value; //cuurrentb번째 b구조체 배열에 대입
					currentb++; //다음번째 b구조체 배열에 추가해야하므로 currentb를 1씩 증가시킨다.
				}
	}
	finish = clock();//종료 시각을 측정합니다.

	duration = ((double)finish - (double)start) / CLOCKS_PER_SEC; //시작시각과 종료시각 사이의 걸린 시간을 duration 변수에 저장합니다.

}


int main() //메인함수
{
	int n, i; //n번째 배열을 지정하기 위해 선언된 변수입니다.
	term A[1001], B[1001]; //값을 가지고 있을 A구조체배열, 행 순서를 열순서로 바꿔줄 B구조체 배열 각각 100개씩 선언해 줍니다.


	A[0].value = 1000;//1000개의 값이 0이아닌 원소를 가지므로 A[0].value의 값을 1000으로 해줍니다.
	for (n = 1; n < 1001; n++) //첫번째 원소부터 마지막 1000번째 원소까지
		A[n].value = rand() % 5+1; //A.value의 원소들은 랜덤으로 1부터 5까지의 값을 가집니다.

	for (i = 0; i <= A[0].value; i++)
		printf("%d   %d   %d   %d\n", i, A[i].row, A[i].col, A[i].value);

	printf("\n\n\n\n\n\n\n\n\n\n");



	transpose(A, B);//함수를 호출하여 작업을 실시합니다.
	


	for (i = 0; i <= B[0].value; i++) 
		printf("%d   %d   %d   %d\n", i, B[i].row, B[i].col, B[i].value);




		printf("%f초 입니다.\n", duration);//걸린시간을 화면에 출력합니다.

		return 0;


	}

