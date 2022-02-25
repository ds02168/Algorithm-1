#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define Max_id 500 //학생수
#define Max_course 35 //코스수

typedef struct enroll_s *enroll_sp;
typedef struct enroll_s {
	char alpha; //추가(A)할지 삭제(D)할지 저장하는 변수
	int id_num; //ID를 저장하는변수
	int course_num; //코스를 저장하는 변수
	enroll_sp right; //같은 id의 오름차순의 다음 노드를 가리킵니다.
	enroll_sp left; //같은 코스의 오름차순의 다음 노드를 가리킵니다.
}enroll_s;//자료형 별칭 enroll_s와 포인터 enroll_sp를 선언합니다.

enroll_sp courses[Max_course]; //course는 코스에대한  구조체 주소들을 저장하는 배열
enroll_sp students[Max_id]; //students는 학생ID에대한 구조체 주소들을 저장하는 배열

FILE *fp1, *fp2; //fp1은 파일열기, fp2는 파일출력

int course_number, id_number; //코스번호,학생번호
char alpha; //A(추가) 또는 D(삭제)를 저장하는 변수
int nonalpha = 0, same = 0, emp = 0, courseerr = 0, iderr = 0, ErrRsn = 0;
//포지션 오류수,중복오류수,미등록오류수를 저장하는 정수형 변수
//코스에러수를 저장하는 변수,ID에러수를 저장하는 변수,한줄당 에러종류를 저장하는 정수형 변수
char arr[25]; //0~25문자 버퍼에서 불러들이는 배열
char buffer[50]; //input 파일의 한줄의 한문자씩 저장합니다.

//전역변수

int interger(int, int);
int check_input();//에러 유무 판단 함수
int Error(int);//에러 종류 확인 함수
int add();//삽입 함수
int del();//삭제 함수
int read(int, int);//입력 파일의 문자를 데이터로 읽어드리는 함수
void print_node(enroll_sp, int);//데이터를 출력하는 함수

//함수선언


int main()
{
	int  in = 0; //in는 등록개수를 저장하는 변수
	int cancel = 0; //cancel는 취소 갯수를 저장하는 변수
	int	card = 0; //card는 정상적으로 읽은 수를 저장하는 변수
	int count = 0; //count는 반복문의 횟수를 세기 위한 변수

	if ((fp1 = fopen("C:\\Users\\K\\Desktop\\input.txt", "r")) != NULL) //input파일을 읽기형식으로 fp1으로 엽니다.
		printf("파일읽기 완료\n"); //정상작동시 확인 출력

	else//에러시
	{
		printf("경로를 다시 확인해 주세요.\n"); // 에러출력
		return 1;//종료
	}

	fp2 = fopen("C:\\Users\\K\\Desktop\\output.txt", "w"); //output파일을 쓰기형식으로 불러옵니다.

	for (count = 0; count < Max_id; count++)
		students[count] = NULL; //students 배열을 NULL로 초기화 해줍니다.

	for (count = 0; count < Max_course; count++)
		courses[count] = NULL;//course 배열을 NULL로 초기화 해줍니다.

	fprintf(fp2, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fgets(buffer, sizeof(buffer), fp1)) //input파일을 50문자씩 buffer배열에 저장합니다,줄이 유효하는 동안
	{
		if (strcmp("end of file", buffer) == 0) //end of file을 만나면
			break; //종료

		card++; //card 1증가
		strcpy(arr, buffer); //buffer배열을 arr배열에 복사합니다.
		ErrRsn = check_input(); //reasonsofError에 어느부분에서 오류인지에 대한 값을 저장합니다.
		fprintf(fp2, "%d,  %d, %c ", id_number, course_number, alpha);//한줄씩 input에 입력됬던 값들을 출력합니다.

		if (ErrRsn) // 에러 사유가 있으면
		{
			Error(ErrRsn);//에러
			continue;//계속
		}

		else //없으면
		{
			switch (alpha) // 알파벳이
			{
			case 'A'://A이면
				if (add())//삽입에 에러가 있으면
					Error(1);//1번 에러 출력(중복)
				else in++; //등록 갯수 증가
				break;

			case 'D'://D이면
				if (del())//삭제에 에러가 있으면
					Error(2);//2번 에러 출력(미등록)
				else//문제가 없으면
				{
					cancel++; //취소 갯수 증가
					fprintf(fp2, "          ** 삭제완료**");//삭제 출력
				}
				break;//swhitch 루프 종료
			}

		}
		fprintf(fp2, "\n");//한줄씩 띄어줍니다.
	}

	fprintf(fp2, "\n\n");//두줄 띄어줍니다.


	for (count = 1; count < Max_course; count++) //코스별로 분류
	{
		if (courses[count] != NULL)//코스가 존재한다면
		{
			fprintf(fp2, "%d: ", courses[count]->course_num);//출력
			print_node(courses[count], 0);//출력함수 호출
		}
	}

	fprintf(fp2, "\n[에러보고]   ** 중복등록수 **:  %d", same);
	fprintf(fp2, "   ** 미등록수 **:  %d", emp);
	fprintf(fp2, "   ** 유효하지 않는 코스ID **:  %d", courseerr);
	fprintf(fp2, "   ** 유효하지 않는 학생ID **:  %d", iderr);
	fprintf(fp2, "   ** A 혹은 D가 아님 **:  %d\n\n", nonalpha);
	fprintf(fp2, "\n[입력보고]   ** 읽은카드수 **: %d", card);
	fprintf(fp2, "   ** 유효등록 **: %d", in);
	fprintf(fp2, "   ** 취소 **: %d\n", cancel);//특이사항 보고
	fprintf(fp2, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	fclose(fp1);
	fclose(fp2);//파일들을 닫습니다.

	return 0;
}



int add()
{
	enroll_sp ptr, temp; //첫 노드기준 ptr,
	int i, j, infinite = 1;//id_number값 보정 변수 i, course_number값 보정 변수 j,상태를 저장하는 변수 infinite

	i = id_number - 2000;//i은 students인덱스가 0~499이므로  -2000하여 인덱스와 id_number사이의 차이를 맞춰줍니다.ex)id_number[2001]은 students[1]
	j = course_number - 100;//j은 course인덱스가 0~34이므로 -100을하여 인덱스와 course_number사이의 차이를 맞춰줍니다. ex)course[101]은 course[1]

	ptr = (enroll_s *)malloc(sizeof(enroll_s));//ptr노드의 동적 크기 할당
	ptr->id_num = id_number;//삽입하고자하는 id_number을 ptr구조체의 id_num에 저장합니다.
	ptr->course_num = course_number;//삽입하고자하는 course_number을 ptr구조체의 course_num에 저장합니다.
	ptr->right = NULL;
	ptr->left = NULL;//연결 링크를 NULL로 초기화

	if (!students[i])//students[id_number-2000]이 NULL이면
		students[i] = ptr; //pn번째 students 배열에 ptr을 저장

	else if (students[i]->course_num == ptr->course_num) //id_number의 코스와 ptr의 코스가 같으면
		return 2;//2를 반환합니다.(중복오류)

	else //또는 
	{
		temp = students[i];//pn번재 students배열의 값을 temp 노드에 저장한다.
		while (infinite)//컨디션은 1이므로 무한루프
		{
			if (temp->right == NULL)//temp의 link가 NULL이라면(temp가 마지막 노드일때)
			{
				ptr->right = NULL; //ptr의 link에 NULL을 저장하고
				temp->right = ptr;//temp의 link에 ptr주소값을 저장한다.
				infinite = 0;//컨디션을 0으로 바꾸어 다음 루프를 돌지 않는다
			}

			else if ((ptr->course_num) < (temp->right->course_num))//또는 ptr의 코스가 temp가 가리키는 노드의 코스값보다 작으면
			{
				ptr->right = temp->right;//ptr의 link에 temp의 link를 저장하고
				temp->right = ptr;//temp의 link가 ptr의 주소를 가리키게 한다
				infinite = 0;
			}

			else if (ptr->course_num == temp->right->course_num)//또는 ptr의 코스값과 temp가 가리키는 노드의 코스값이 같으면
				return 2;//2를 반환(중복 오류)

			else//또는(temp가 가리키는 노드가 존재하지 않는경우)
				temp = temp->right;//temp가 temp를 가리키도록 한다.
		}
	}

	if (!courses[j]) //j번째 코스가 NULL일때
		courses[j] = ptr; //ptr의 주소값을 course[j]에 저장

	else //j번째 코스가 값을 가지고 있을때
	{
		temp = courses[j]; //temp 노드에 j번째 course 배열 노드를 저장한다.
		infinite = 1; //조건을 1로 한다.
		while (infinite)
		{
			if (temp->left == NULL)//temp의 left가 NULL일때(temp가 마지막 노드일때)
			{
				ptr->left = NULL;//ptr의 left를 NULL로 저장한다.
				temp->left = ptr;//temp의 left에 ptr의 주소값을 저장합니다.
				infinite = 0;//infinite을 0으로 저장하여 다음 루프를 돌지 않습니다.
			}

			else if ((ptr->id_num) < (temp->left->id_num)) //ptr의 id_num이 temp가 가리키는 노드의 id_num보다 작으면
			{
				ptr->left = temp->left;//temp가 가리키는 주소를 ptr의 left에 저장합니다.
				temp->left = ptr;//temp가 ptr을 가리킵니다.
				infinite = 0;
			}

			else //또는
				temp = temp->left;//템프가 자기자신을 가리킨다.
		}
	}

	return 0;//정상적으로 추가
}

int del()// 삭제 함수
{
	int i, j;
	enroll_sp ptr, temp;
	i = id_number - 2000;
	j = course_number - 100; //add함수와 동일(i은 id_number, j은 course)
	temp = students[i];//id_number - 2000번의 노드를 temp 노드에 저장합니다.

	if (!students[i])//노드가 없으면
		return 1;//1을 반환합니다.(미등록 오류)

	if (students[i]->id_num == id_number) //삭제하고자하는 id_number값과 이미 있는id_num의 값이 일치할대(유효 할때)
	{
		students[i] = students[i]->right;//students[i]의 주소값을 다음 노드의 주소값으로 바꿉니다.
		ptr = temp;//ptr에 temp의 주소값을 넣어줍니다.
	}
	else if ((students[i]->id_num) > id_number)//지우고자 하는 id_number값이 id_num보다 작을때 (최소값이 더 작을 때)
		return 1;//1을 반환합니다.(미등록 오류)
	else
	{
		ptr = temp->right; //temp->link의 주소값을 ptr의 주소값으로 저장합니다.
		while (ptr)//ptr의 값이 NULL이 아닐때(리스트 안에있을때)
		{
			if (ptr->id_num == id_number)//id_num과 id_number의 값이 일치한다면
				temp->right = ptr->right;//temp->right가 temp->right->right가 되도록 합니다.(건너띄기)

			else //옮겨도 더 작다면
			{
				temp = ptr;
				ptr = ptr->right;//temp와 ptr을 한칸씩 더이동
			}

		}
		return 1;//연결노드가 끝날때까지 없다면 존재하지 않으므로 미등록오류
	}

	temp = courses[j];//temp에 course[j]의 주소값을 입력합니다.

	if (!courses[j])//코스값이 존재하지 않는다면
		return 1;//1을 반환(미등록 오류)

	if (courses[j]->course_num == course_number) //삭제하고자 하는 값과 노드의 있는 값이 일치하면
	{
		courses[j] = courses[j]->left; //course->left의 주소값을 course의 주솟값에 저장
		ptr = temp;//ptr의 주소를 temp의 주소로 저장
	}

	else if ((courses[j]->course_num) > course_number)//삭제하고자하는 값이 존재하는 값보다 작다면
		return 1;//1을 반환

	else//삭제하고자하는 값이 존재하는 값보다 크면
	{
		ptr = temp->left;//temp->left주소값을 ptr의 주소에 저장
		while (ptr)//ptr이 유효할동안
		{
			if (ptr->course_num == course_number)//course_number와 course_num의 값이 일치한다면(삭제 하고자하는 값이 존재하면)
				temp->left = ptr->left;//한단계 건너뛰어 연결

			else//아직 일치 하지 않는다면
			{
				temp = ptr;
				ptr = ptr->left;//ptr과 temp의 노드를 한단계씩 건너뛴다
			}

		}

		return 1;//찾아도 없으면 존재x(미등록)
	}

	free(temp);
	free(ptr);//임시노드 삭제

	return 0;//정상적으로 삭제
}


int read(int first, int last)//파일의 데이타를 확인하는 함수
{
	int i, num, result, sum = 0;

	for (i = first; i < last; i++) //i는 시작부터 마지막전까지
	{
		if (*buffer == NULL) //버퍼의 값이 NULL 이면
			arr[i] = NULL;//arr은 NULL 이다

		num = arr[i] - '0';//arr의 문자형 숫자를 정수형 숫자로 변환하여 num에 저장한다.
		result = interger(10, last - i); //10에(1,2,3,....,last-i-1)를 곱해줍니다.(자리수)
		sum = sum + result * num;//sum에 자리수마다 더해줍니다.
	}

	return sum;//sum를 반환합니다.
}

int check_input()//파일로부터 오류가 있는지 확인하는 함수
{
	id_number = course_number = 0;// 학생번호 = 코스번호 = 0
	id_number = read(3, 7);//4번째 문자~ 8번재 문자를 읽어 id_number에 저장
	course_number = read(13, 16); // 14번째 문자 ~ 17번째문자를 읽어 course_number에 저장
	alpha = arr[25]; //25번째 문자를 alpha에 저장합니다. (A또는D)

	if ((course_number < 100) || (course_number > 100 + Max_course)) //course_number가 100~135사이의 숫자면
		return 3; //3를 반환

	if ((id_number < 2001) || (id_number > 2000 + Max_id))//id_number가 2001~2500사이의 숫자가아니면
		return 4; //4를 반환

	if ((alpha != 'A') && (alpha != 'D')) //A도아니고 D도 아니면
		return 5; //5를 반환

	return 0;
}


int Error(int value) // 어떤 에러인지 확인하는 함수
{
	switch (value)
	{
	case 1: same++;//중복등록 에러수 증가
		fprintf(fp2, "          ** 중복등록**");//중복등록 에러 출력
		break; //종료
	case 2: emp++;//미등록 에러수 증가
		fprintf(fp2, "          ** 미등록**");//미등록 출력
		break;//종료
	case 3: courseerr++;//코스 아이디X
		fprintf(fp2, "          ** 유효하지않는코스ID **\n"); //유효하지않는 코스 출력
		break;
	case 4: iderr++;//ID 오류
		fprintf(fp2, "          ** 유효하지않는학생ID **\n"); //유효하지 않는 학생ID 출력
		break;
	case 5: nonalpha++;//포지션 오류
		fprintf(fp2, "          ** 'A'혹은'D'가아님**\n"); //A 혹은 D가 아님을 출력
		break;
	}

	return 0; //에러x
}

void print_node(enroll_sp ptr, int data)//출력 함수
{
	if (!data)//data이 값을 가질때
	{
		for (; ptr; ptr = ptr->left)
			fprintf(fp2, " %d, ", ptr->id_num);//학생 번호들을 출력

	}
	else//값을 가지지 않을때
		for (; ptr; ptr = ptr->right)
			fprintf(fp2, "%c, ", ptr->alpha);//포지션들을 출력
	fprintf(fp2, " \n");
}

int interger(int x, int y) //a는 10,b는 end_n-i
{
	int total = 1, i;
	for (i = 0; i < y - 1; i++)//i는 0부터 end_n-i까지
		total = total * x; //total에 x를 곱해줍니다.

	return total;//total을 반환합니다.
}