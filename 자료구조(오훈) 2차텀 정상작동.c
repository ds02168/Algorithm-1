#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define end_of_file 0
#define M_id 500 //학생수
#define M_course 35 //코스수

typedef struct enroll_s *node_ptr;
typedef struct enroll_s
{
	char position; //추가(A)할지 삭제(D)할지 저장하는 변수
	int id_num; //ID를 저장하는변수
	int course_num; //코스를 저장하는 변수
	node_ptr llink; //같은 id의 오름차순의 다음 노드를 가리킵니다.
	node_ptr plink; //같은 코스의 오름차순의 다음 노드를 가리킵니다.
}node;


char instr[25]; //0~25문자 버퍼에서 불러들이는 배열
int course_number, id_number; //코스번호,학생번호
char position; //A(추가) 또는 D(삭제)를 저장하는 변수
int NotAD = 0, OverapReg = 0, NotReg = 0; //포지션 오류수,중복오류수,미등록오류수를 저장하는 정수형 변수
int Notcoursenum = 0, Notidnum = 0, ReasonofError = 0; //코스에러수,ID에러수,한줄당 에러종류를 저장하는 정수형 변수

FILE *fp1, *fp2; //fp1은 파일오픈, fp2는 파일저장
char buffer[50]; //input 파일의 한줄의 한문자씩 저장합니다.

node_ptr course[M_course]; //course는
node_ptr ids[M_id]; //ids는

						//전역변수

int sqr(int a, int b);
int checkdata();//에러 유무 판단 함수
int Error(int ReasonofError);//에러 종류 확인 함수
int insert();//삽입 함수
int deletel();//삭제 함수
int subcheck(int start_n, int end_n);
void printlist(node_ptr, int pln);
//함수선언


int main()
{

	int k = 0, l = 0, d = 0, t = 0; //i는 등록개수,d는 취소 갯수,k는 정상적으로 읽은 수

	if ((fp1 = fopen("C:\\Users\\YTH\\Desktop\\input.txt", "r")) != NULL) //input파일을 읽기형식으로 fp1으로 엽니다.
		printf("파일읽기 완료\n"); //정상작동시 확인 출력

	else//에러시
	{
		printf("에러: 파일을찾을수없습니다.\n"); // 에러출력
		return 1;//종료
	}

	fp2 = fopen("C:\\Users\\YTH\\Desktop\\output.txt", "w"); //output파일을 쓰기형식으로 불러옵니다.

	for (t = 0; t < M_id; t++)
		ids[t] = NULL; //ids 배열을 NULL로 초기화 해줍니다.

	for (t = 0; t < M_course; t++)
		course[t] = NULL;//course 배열을 NULL로 초기화 해줍니다.

	while (fgets(buffer, 50, fp1)) //input파일을 50문자씩 buffer배열에 저장합니다,줄이 유효하는 동안
	{
		if (strcmp("end of file", buffer) == 0) //end of file을 만나면
			break; //종료

		k++; //k 1증가
		strcpy(instr, buffer); //buffer배열을 instr배열에 복사합니다.
		ReasonofError = checkdata(); //reasonsofError에 어느부분에서 오류인지에 대한 값을 저장합니다.
		fprintf(fp2, "%d,  %d, %c ", id_number, course_number, position);//한줄씩 input에 입력됬던 값들을 출력합니다.

		if (ReasonofError != 0) // 에러 사유가 있으면
		{
			Error(ReasonofError);//에러
			continue;//계속
		}
		else //없으면
		{
			switch (position) // 포지션이
			{
			case 'A'://A이면
				if (insert())//삽입에 에러가 있으면
					Error(1);//1번 에러 출력(중복)
				else l++; //등록 갯수 증가
				break;
			case 'D'://D이면
				if (deletel())//삭제에 에러가 있으면
					Error(2);//2번 에러 출력(미등록)
				else//문제가 없으면
				{
					d++; //취소 갯수 증가
					fprintf(fp2, " ** 삭제완료**");//삭제 출력
				}
				break;//swhitch 루프 종료
			}
			fprintf(fp2, "\n");//한줄씩 듸어준다.
		}
	}

	for (t = 1; t < M_course; t++) //코스별로 분류
	{
		if (course[t] != NULL)//코스가 존재한다면
		{
			fprintf(fp2, "%d 강의수강생: ", course[t]->course_num);//출력
			printlist(course[t], 0);//출력함수 호출
		}
	}
	fprintf(fp2, "\n<<에러보고>>\n 중복등록수  :   %d\n", OverapReg);
	fprintf(fp2, " 미등록수  :   %d\n", NotReg);
	fprintf(fp2, " 유효하지않는코스ID    :   %d\n", Notcoursenum);
	fprintf(fp2, " 유효하지않는학생ID   :   %d\n", Notidnum);
	fprintf(fp2, " A,D가 아님  :   %d\n", NotAD);
	fprintf(fp2, "\n<<입력보고>>\n읽은카드수: %d", k);
	fprintf(fp2, " 유효등록: %d", l);
	fprintf(fp2, " 취소: %d", d);//특이사항 보고

	fclose(fp1);
	fclose(fp2);//파일들을 닫습니다.

	return 0;
}



int insert()
{
	node_ptr ptr, temp; //첫 노드기준 ptr,
	int pn, ln, condition = 1;//id_number값 보정 변수 pn, course_number값 보정 변수 ln,상태를 저장하는 변수 condition
	pn = id_number - 2000;//pn은 ids인덱스가 0~499이므로  -2000하여 인덱스와 id_number사이의 차이를 맞춰줍니다.ex)id_number[2001]은 ids[1]
	ln = course_number - 100;//ln은 course인덱스가 0~34이므로 -100을하여 인덱스와 course_number사이의 차이를 맞춰줍니다. ex)course[101]은 course[1]

	ptr = (node *)malloc(sizeof(node));//ptr노드의 동적 크기 할당
	ptr->id_num = id_number;//삽입하고자하는 id_number을 ptr구조체의 id_num에 저장합니다.
	ptr->course_num = course_number;//삽입하고자하는 course_number을 ptr구조체의 course_num에 저장합니다.
	ptr->llink = NULL;
	ptr->plink = NULL;//연결 링크를 NULL로 초기화

	if (!ids[pn])//ids[id_number-2000]이 NULL이면
		ids[pn] = ptr; //pn번째 ids 배열에 ptr을 저장

	else if (ids[pn]->course_num == ptr->course_num) //id_number의 코스와 ptr의 코스가 같으면
		return 2;//2를 반환합니다.(중복오류)

	else //또는 
	{
		temp = ids[pn];//pn번재 ids배열의 값을 temp 노드에 저장한다.
		while (condition)//컨디션은 1이므로 무한루프
		{
			if (temp->llink == NULL)//temp의 link가 NULL이라면(temp가 마지막 노드일때)
			{
				ptr->llink = NULL; //ptr의 link에 NULL을 저장하고
				temp->llink = ptr;//temp의 link에 ptr주소값을 저장한다.
				condition = 0;//컨디션을 0으로 바꾸어 다음 루프를 돌지 않는다
			}

			else if ((ptr->course_num) < (temp->llink->course_num))//또는 ptr의 코스가 temp가 가리키는 노드의 코스값보다 작으면
			{
				ptr->llink = temp->llink;//ptr의 link에 temp의 link를 저장하고
				temp->llink = ptr;//temp의 link가 ptr의 주소를 가리키게 한다
				condition = 0;
			}

			else if (ptr->course_num == temp->llink->course_num)//또는 ptr의 코스값과 temp가 가리키는 노드의 코스값이 같으면
				return 2;//2를 반환(중복 오류)

			else//또는(temp가 가리키는 노드가 존재하지 않는경우)
				temp = temp->llink;//temp가 temp를 가리키도록 한다.
		}
	}

	if (!course[ln]) //ln번째 코스가 NULL일때
		course[ln] = ptr; //ptr의 주소값을 course[ln]에 저장

	else //ln번째 코스가 값을 가지고 있을때
	{
		temp = course[ln]; //temp 노드에 ln번째 course 배열 노드를 저장한다.
		condition = 1; //조건을 1로 한다.
		while (condition)
		{
			if (temp->plink == NULL)//temp의 plink가 NULL일때(temp가 마지막 노드일때)
			{
				ptr->plink = NULL;//ptr의 plink를 NULL로 저장한다.
				temp->plink = ptr;//temp의 plink에 ptr의 주소값을 저장합니다.
				condition = 0;//condition을 0으로 저장하여 다음 루프를 돌지 않습니다.
			}

			else if ((ptr->id_num) < (temp->plink->id_num)) //ptr의 id_num이 temp가 가리키는 노드의 id_num보다 작으면
			{
				ptr->plink = temp->plink;//temp가 가리키는 주소를 ptr의 plink에 저장합니다.
				temp->plink = ptr;//temp가 ptr을 가리킵니다.
				condition = 0;
			}

			else //또는
				temp = temp->plink;//템프가 자기자신을 가리킨다.
		}
	}

	return 0;
}



void printlist(node_ptr list, int pln)//출력 함수
{
	if (!pln)//pln이 값을 가질때
	{
		for (; list; list = list->plink)
			fprintf(fp2, " %d, ", list->id_num);//학생 번호들을 출력

	}
	else//값을 가지지 않을때
		for (; list; list = list->llink)
			fprintf(fp2, "%c, ", list->position);//포지션들을 출력
	fprintf(fp2, " \n");
}

int deletel()// 삭제 함수
{
	int pn, ln;
	node_ptr ptr, temp;
	pn = id_number - 2000;
	ln = course_number - 100; //insert함수와 동일(pn은 id_number, ln은 course)
	temp = ids[pn];//id_number - 2000번의 노드를 temp 노드에 저장합니다.

	if (!ids[pn])//노드가 없으면
		return 1;//1을 반환합니다.(미등록 오류)

	if (ids[pn]->id_num == id_number) //삭제하고자하는 id_number값과 이미 있는id_num의 값이 일치할대(유효 할때)
	{
		ids[pn] = ids[pn]->llink;//ids[pn]의 주소값을 다음 노드의 주소값으로 바꿉니다.
		ptr = temp;//ptr에 temp의 주소값을 넣어줍니다.
	}
	else if ((ids[pn]->id_num) > id_number)//지우고자 하는 id_number값이 id_num보다 작을때 (최소값이 더 작을 때)
		return 1;//1을 반환합니다.(미등록 오류)
	else
	{
		ptr = temp->llink; //temp->link의 주소값을 ptr의 주소값으로 저장합니다.
		while (ptr)//ptr의 값이 NULL이 아닐때(리스트 안에있을때)
		{
			if (ptr->id_num == id_number)//id_num과 id_number의 값이 일치한다면
				temp->llink = ptr->llink;//temp->llink가 temp->llink->llink가 되도록 합니다.(건너띄기)

			else //옮겨도 더 작다면
			{
				temp = ptr;
				ptr = ptr->llink;//temp와 ptr을 한칸씩 더이동
			}

		}
		return 1;//연결노드가 끝날때까지 없다면 존재하지 않으므로 미등록오류
	}

	temp = course[ln];//temp에 course[ln]의 주소값을 입력합니다.

	if (!course[ln])//코스값이 존재하지 않는다면
		return 1;//1을 반환(미등록 오류)

	if (course[ln]->course_num == course_number) //삭제하고자 하는 값과 노드의 있는 값이 일치하면
	{
		course[ln] = course[ln]->plink; //course->plink의 주소값을 course의 주솟값에 저장
		ptr = temp;//ptr의 주소를 temp의 주소로 저장
	}

	else if ((course[ln]->course_num) > course_number)//삭제하고자하는 값이 존재하는 값보다 작다면
		return 1;//1을 반환

	else//삭제하고자하는 값이 존재하는 값보다 크면
	{
		ptr = temp->plink;//temp->plink주소값을 ptr의 주소에 저장
		while (ptr)//ptr이 유효할동안
		{
			if (ptr->course_num == course_number)//course_number와 course_num의 값이 일치한다면(삭제 하고자하는 값이 존재하면)
				temp->plink = ptr->plink;//한단계 건너뛰어 연결

			else//아직 일치 하지 않는다면
			{
				temp = ptr;
				ptr = ptr->plink;//ptr과 temp의 노드를 한단계씩 건너뛴다
			}

		}

		return 1;//찾아도 없으면 존재x(미등록)
	}

	free(ptr);//노드 삭제

	return 0;//id존재 course존재시 이상없음
}



int Error(int ERRcode) // 어떤 에러인지 확인하는 함수
{
	switch (ERRcode)
	{
	case 1: OverapReg++;//중복등록 에러수 증가
		fprintf(fp2, "** 중복등록**");//중복등록 에러 출력
		break; //종료
	case 2: NotReg++;//미등록 에러수 증가
		fprintf(fp2, "** 미등록**");//미등록 출력
		break;//종료
	case 3: Notcoursenum++;//코스 아이디X
		fprintf(fp2, "** 유효하지않는코스ID **\n");
		break;
	case 4: Notidnum++;//ID 오류
		fprintf(fp2, "** 유효하지않는학생ID **\n");
		break;
	case 5: NotAD++;//포지션 오류
		fprintf(fp2, "** 'A'혹은'D'가아님**\n");
		break;
	}

	return 0; //에러x
}

int sqr(int a, int b) //a는 10,b는 end_n-i
{
	int c = 1, y;
	for (y = 0; y < b - 1; y++)//y는 0부터 end_n-i까지
		c = c * a; //c에 a를 곱해줍니다.

	return c;//c를 반환합니다.
}

int checkdata()//파일로부터 오류가 있는지 확인하는 함수
{
	id_number = course_number = 0;// 학생번호 = 코스번호 = 0
	id_number = subcheck(0, 4);//0번재 문자~ 4번재 문자를 읽어 id_number에 저장
	course_number = subcheck(10, 13); // 10번째 문자 ~ 13번째문자를 읽어 course_number에 저장
	position = instr[25]; //25번째 문자를 position에 저장합니다. (A또는D)
	if (position != 'A' && position != 'D') //A도아니고 D도 아니면
		return 5; //5를 반환

	if ((id_number<2001) || (id_number>2000 + M_id))//id_number가 2001~2500사이의 숫자가아니면
		return 4; //4를 반환

	if ((course_number<100) || (course_number>100 + M_course)) //course_number가 100~135사이의 숫자면
		return 3; //3를 반환

	return 0;
}

int subcheck(int start_n, int end_n)//파일의 데이타를 확인하는 함수
{
	int i, number, op, course_id = 0;

	for (i = start_n; i < end_n; i++) //i는 시작부터 마지막전까지
	{
		if (*buffer == NULL) //버퍼의 값이 NULL 이면
			instr[i] = NULL;//instr은 NULL 이다

		number = instr[i] - '0';//instr의 문자형 숫자를 정수형 숫자로 변환하여 number에 저장한다.
		op = sqr(10, end_n - i); //10에(1,2,3,....,end_n-i-1)를 곱해줍니다.(자리수)
		course_id = course_id + op * number;//course_id에 자리수마다 더해줍니다.
	}

	return course_id;//course_id를 반환합니다.
}
