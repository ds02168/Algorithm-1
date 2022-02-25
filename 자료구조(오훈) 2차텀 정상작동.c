#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define end_of_file 0
#define M_id 500 //�л���
#define M_course 35 //�ڽ���

typedef struct enroll_s *node_ptr;
typedef struct enroll_s
{
	char position; //�߰�(A)���� ����(D)���� �����ϴ� ����
	int id_num; //ID�� �����ϴº���
	int course_num; //�ڽ��� �����ϴ� ����
	node_ptr llink; //���� id�� ���������� ���� ��带 ����ŵ�ϴ�.
	node_ptr plink; //���� �ڽ��� ���������� ���� ��带 ����ŵ�ϴ�.
}node;


char instr[25]; //0~25���� ���ۿ��� �ҷ����̴� �迭
int course_number, id_number; //�ڽ���ȣ,�л���ȣ
char position; //A(�߰�) �Ǵ� D(����)�� �����ϴ� ����
int NotAD = 0, OverapReg = 0, NotReg = 0; //������ ������,�ߺ�������,�̵�Ͽ������� �����ϴ� ������ ����
int Notcoursenum = 0, Notidnum = 0, ReasonofError = 0; //�ڽ�������,ID������,���ٴ� ���������� �����ϴ� ������ ����

FILE *fp1, *fp2; //fp1�� ���Ͽ���, fp2�� ��������
char buffer[50]; //input ������ ������ �ѹ��ھ� �����մϴ�.

node_ptr course[M_course]; //course��
node_ptr ids[M_id]; //ids��

						//��������

int sqr(int a, int b);
int checkdata();//���� ���� �Ǵ� �Լ�
int Error(int ReasonofError);//���� ���� Ȯ�� �Լ�
int insert();//���� �Լ�
int deletel();//���� �Լ�
int subcheck(int start_n, int end_n);
void printlist(node_ptr, int pln);
//�Լ�����


int main()
{

	int k = 0, l = 0, d = 0, t = 0; //i�� ��ϰ���,d�� ��� ����,k�� ���������� ���� ��

	if ((fp1 = fopen("C:\\Users\\YTH\\Desktop\\input.txt", "r")) != NULL) //input������ �б��������� fp1���� ���ϴ�.
		printf("�����б� �Ϸ�\n"); //�����۵��� Ȯ�� ���

	else//������
	{
		printf("����: ������ã���������ϴ�.\n"); // �������
		return 1;//����
	}

	fp2 = fopen("C:\\Users\\YTH\\Desktop\\output.txt", "w"); //output������ ������������ �ҷ��ɴϴ�.

	for (t = 0; t < M_id; t++)
		ids[t] = NULL; //ids �迭�� NULL�� �ʱ�ȭ ���ݴϴ�.

	for (t = 0; t < M_course; t++)
		course[t] = NULL;//course �迭�� NULL�� �ʱ�ȭ ���ݴϴ�.

	while (fgets(buffer, 50, fp1)) //input������ 50���ھ� buffer�迭�� �����մϴ�,���� ��ȿ�ϴ� ����
	{
		if (strcmp("end of file", buffer) == 0) //end of file�� ������
			break; //����

		k++; //k 1����
		strcpy(instr, buffer); //buffer�迭�� instr�迭�� �����մϴ�.
		ReasonofError = checkdata(); //reasonsofError�� ����κп��� ���������� ���� ���� �����մϴ�.
		fprintf(fp2, "%d,  %d, %c ", id_number, course_number, position);//���پ� input�� �Է�� ������ ����մϴ�.

		if (ReasonofError != 0) // ���� ������ ������
		{
			Error(ReasonofError);//����
			continue;//���
		}
		else //������
		{
			switch (position) // ��������
			{
			case 'A'://A�̸�
				if (insert())//���Կ� ������ ������
					Error(1);//1�� ���� ���(�ߺ�)
				else l++; //��� ���� ����
				break;
			case 'D'://D�̸�
				if (deletel())//������ ������ ������
					Error(2);//2�� ���� ���(�̵��)
				else//������ ������
				{
					d++; //��� ���� ����
					fprintf(fp2, " ** �����Ϸ�**");//���� ���
				}
				break;//swhitch ���� ����
			}
			fprintf(fp2, "\n");//���پ� ����ش�.
		}
	}

	for (t = 1; t < M_course; t++) //�ڽ����� �з�
	{
		if (course[t] != NULL)//�ڽ��� �����Ѵٸ�
		{
			fprintf(fp2, "%d ���Ǽ�����: ", course[t]->course_num);//���
			printlist(course[t], 0);//����Լ� ȣ��
		}
	}
	fprintf(fp2, "\n<<��������>>\n �ߺ���ϼ�  :   %d\n", OverapReg);
	fprintf(fp2, " �̵�ϼ�  :   %d\n", NotReg);
	fprintf(fp2, " ��ȿ�����ʴ��ڽ�ID    :   %d\n", Notcoursenum);
	fprintf(fp2, " ��ȿ�����ʴ��л�ID   :   %d\n", Notidnum);
	fprintf(fp2, " A,D�� �ƴ�  :   %d\n", NotAD);
	fprintf(fp2, "\n<<�Էº���>>\n����ī���: %d", k);
	fprintf(fp2, " ��ȿ���: %d", l);
	fprintf(fp2, " ���: %d", d);//Ư�̻��� ����

	fclose(fp1);
	fclose(fp2);//���ϵ��� �ݽ��ϴ�.

	return 0;
}



int insert()
{
	node_ptr ptr, temp; //ù ������ ptr,
	int pn, ln, condition = 1;//id_number�� ���� ���� pn, course_number�� ���� ���� ln,���¸� �����ϴ� ���� condition
	pn = id_number - 2000;//pn�� ids�ε����� 0~499�̹Ƿ�  -2000�Ͽ� �ε����� id_number������ ���̸� �����ݴϴ�.ex)id_number[2001]�� ids[1]
	ln = course_number - 100;//ln�� course�ε����� 0~34�̹Ƿ� -100���Ͽ� �ε����� course_number������ ���̸� �����ݴϴ�. ex)course[101]�� course[1]

	ptr = (node *)malloc(sizeof(node));//ptr����� ���� ũ�� �Ҵ�
	ptr->id_num = id_number;//�����ϰ����ϴ� id_number�� ptr����ü�� id_num�� �����մϴ�.
	ptr->course_num = course_number;//�����ϰ����ϴ� course_number�� ptr����ü�� course_num�� �����մϴ�.
	ptr->llink = NULL;
	ptr->plink = NULL;//���� ��ũ�� NULL�� �ʱ�ȭ

	if (!ids[pn])//ids[id_number-2000]�� NULL�̸�
		ids[pn] = ptr; //pn��° ids �迭�� ptr�� ����

	else if (ids[pn]->course_num == ptr->course_num) //id_number�� �ڽ��� ptr�� �ڽ��� ������
		return 2;//2�� ��ȯ�մϴ�.(�ߺ�����)

	else //�Ǵ� 
	{
		temp = ids[pn];//pn���� ids�迭�� ���� temp ��忡 �����Ѵ�.
		while (condition)//������� 1�̹Ƿ� ���ѷ���
		{
			if (temp->llink == NULL)//temp�� link�� NULL�̶��(temp�� ������ ����϶�)
			{
				ptr->llink = NULL; //ptr�� link�� NULL�� �����ϰ�
				temp->llink = ptr;//temp�� link�� ptr�ּҰ��� �����Ѵ�.
				condition = 0;//������� 0���� �ٲپ� ���� ������ ���� �ʴ´�
			}

			else if ((ptr->course_num) < (temp->llink->course_num))//�Ǵ� ptr�� �ڽ��� temp�� ����Ű�� ����� �ڽ������� ������
			{
				ptr->llink = temp->llink;//ptr�� link�� temp�� link�� �����ϰ�
				temp->llink = ptr;//temp�� link�� ptr�� �ּҸ� ����Ű�� �Ѵ�
				condition = 0;
			}

			else if (ptr->course_num == temp->llink->course_num)//�Ǵ� ptr�� �ڽ����� temp�� ����Ű�� ����� �ڽ����� ������
				return 2;//2�� ��ȯ(�ߺ� ����)

			else//�Ǵ�(temp�� ����Ű�� ��尡 �������� �ʴ°��)
				temp = temp->llink;//temp�� temp�� ����Ű���� �Ѵ�.
		}
	}

	if (!course[ln]) //ln��° �ڽ��� NULL�϶�
		course[ln] = ptr; //ptr�� �ּҰ��� course[ln]�� ����

	else //ln��° �ڽ��� ���� ������ ������
	{
		temp = course[ln]; //temp ��忡 ln��° course �迭 ��带 �����Ѵ�.
		condition = 1; //������ 1�� �Ѵ�.
		while (condition)
		{
			if (temp->plink == NULL)//temp�� plink�� NULL�϶�(temp�� ������ ����϶�)
			{
				ptr->plink = NULL;//ptr�� plink�� NULL�� �����Ѵ�.
				temp->plink = ptr;//temp�� plink�� ptr�� �ּҰ��� �����մϴ�.
				condition = 0;//condition�� 0���� �����Ͽ� ���� ������ ���� �ʽ��ϴ�.
			}

			else if ((ptr->id_num) < (temp->plink->id_num)) //ptr�� id_num�� temp�� ����Ű�� ����� id_num���� ������
			{
				ptr->plink = temp->plink;//temp�� ����Ű�� �ּҸ� ptr�� plink�� �����մϴ�.
				temp->plink = ptr;//temp�� ptr�� ����ŵ�ϴ�.
				condition = 0;
			}

			else //�Ǵ�
				temp = temp->plink;//������ �ڱ��ڽ��� ����Ų��.
		}
	}

	return 0;
}



void printlist(node_ptr list, int pln)//��� �Լ�
{
	if (!pln)//pln�� ���� ������
	{
		for (; list; list = list->plink)
			fprintf(fp2, " %d, ", list->id_num);//�л� ��ȣ���� ���

	}
	else//���� ������ ������
		for (; list; list = list->llink)
			fprintf(fp2, "%c, ", list->position);//�����ǵ��� ���
	fprintf(fp2, " \n");
}

int deletel()// ���� �Լ�
{
	int pn, ln;
	node_ptr ptr, temp;
	pn = id_number - 2000;
	ln = course_number - 100; //insert�Լ��� ����(pn�� id_number, ln�� course)
	temp = ids[pn];//id_number - 2000���� ��带 temp ��忡 �����մϴ�.

	if (!ids[pn])//��尡 ������
		return 1;//1�� ��ȯ�մϴ�.(�̵�� ����)

	if (ids[pn]->id_num == id_number) //�����ϰ����ϴ� id_number���� �̹� �ִ�id_num�� ���� ��ġ�Ҵ�(��ȿ �Ҷ�)
	{
		ids[pn] = ids[pn]->llink;//ids[pn]�� �ּҰ��� ���� ����� �ּҰ����� �ٲߴϴ�.
		ptr = temp;//ptr�� temp�� �ּҰ��� �־��ݴϴ�.
	}
	else if ((ids[pn]->id_num) > id_number)//������� �ϴ� id_number���� id_num���� ������ (�ּҰ��� �� ���� ��)
		return 1;//1�� ��ȯ�մϴ�.(�̵�� ����)
	else
	{
		ptr = temp->llink; //temp->link�� �ּҰ��� ptr�� �ּҰ����� �����մϴ�.
		while (ptr)//ptr�� ���� NULL�� �ƴҶ�(����Ʈ �ȿ�������)
		{
			if (ptr->id_num == id_number)//id_num�� id_number�� ���� ��ġ�Ѵٸ�
				temp->llink = ptr->llink;//temp->llink�� temp->llink->llink�� �ǵ��� �մϴ�.(�ǳʶ��)

			else //�Űܵ� �� �۴ٸ�
			{
				temp = ptr;
				ptr = ptr->llink;//temp�� ptr�� ��ĭ�� ���̵�
			}

		}
		return 1;//�����尡 ���������� ���ٸ� �������� �����Ƿ� �̵�Ͽ���
	}

	temp = course[ln];//temp�� course[ln]�� �ּҰ��� �Է��մϴ�.

	if (!course[ln])//�ڽ����� �������� �ʴ´ٸ�
		return 1;//1�� ��ȯ(�̵�� ����)

	if (course[ln]->course_num == course_number) //�����ϰ��� �ϴ� ���� ����� �ִ� ���� ��ġ�ϸ�
	{
		course[ln] = course[ln]->plink; //course->plink�� �ּҰ��� course�� �ּڰ��� ����
		ptr = temp;//ptr�� �ּҸ� temp�� �ּҷ� ����
	}

	else if ((course[ln]->course_num) > course_number)//�����ϰ����ϴ� ���� �����ϴ� ������ �۴ٸ�
		return 1;//1�� ��ȯ

	else//�����ϰ����ϴ� ���� �����ϴ� ������ ũ��
	{
		ptr = temp->plink;//temp->plink�ּҰ��� ptr�� �ּҿ� ����
		while (ptr)//ptr�� ��ȿ�ҵ���
		{
			if (ptr->course_num == course_number)//course_number�� course_num�� ���� ��ġ�Ѵٸ�(���� �ϰ����ϴ� ���� �����ϸ�)
				temp->plink = ptr->plink;//�Ѵܰ� �ǳʶپ� ����

			else//���� ��ġ ���� �ʴ´ٸ�
			{
				temp = ptr;
				ptr = ptr->plink;//ptr�� temp�� ��带 �Ѵܰ辿 �ǳʶڴ�
			}

		}

		return 1;//ã�Ƶ� ������ ����x(�̵��)
	}

	free(ptr);//��� ����

	return 0;//id���� course����� �̻����
}



int Error(int ERRcode) // � �������� Ȯ���ϴ� �Լ�
{
	switch (ERRcode)
	{
	case 1: OverapReg++;//�ߺ���� ������ ����
		fprintf(fp2, "** �ߺ����**");//�ߺ���� ���� ���
		break; //����
	case 2: NotReg++;//�̵�� ������ ����
		fprintf(fp2, "** �̵��**");//�̵�� ���
		break;//����
	case 3: Notcoursenum++;//�ڽ� ���̵�X
		fprintf(fp2, "** ��ȿ�����ʴ��ڽ�ID **\n");
		break;
	case 4: Notidnum++;//ID ����
		fprintf(fp2, "** ��ȿ�����ʴ��л�ID **\n");
		break;
	case 5: NotAD++;//������ ����
		fprintf(fp2, "** 'A'Ȥ��'D'���ƴ�**\n");
		break;
	}

	return 0; //����x
}

int sqr(int a, int b) //a�� 10,b�� end_n-i
{
	int c = 1, y;
	for (y = 0; y < b - 1; y++)//y�� 0���� end_n-i����
		c = c * a; //c�� a�� �����ݴϴ�.

	return c;//c�� ��ȯ�մϴ�.
}

int checkdata()//���Ϸκ��� ������ �ִ��� Ȯ���ϴ� �Լ�
{
	id_number = course_number = 0;// �л���ȣ = �ڽ���ȣ = 0
	id_number = subcheck(0, 4);//0���� ����~ 4���� ���ڸ� �о� id_number�� ����
	course_number = subcheck(10, 13); // 10��° ���� ~ 13��°���ڸ� �о� course_number�� ����
	position = instr[25]; //25��° ���ڸ� position�� �����մϴ�. (A�Ǵ�D)
	if (position != 'A' && position != 'D') //A���ƴϰ� D�� �ƴϸ�
		return 5; //5�� ��ȯ

	if ((id_number<2001) || (id_number>2000 + M_id))//id_number�� 2001~2500������ ���ڰ��ƴϸ�
		return 4; //4�� ��ȯ

	if ((course_number<100) || (course_number>100 + M_course)) //course_number�� 100~135������ ���ڸ�
		return 3; //3�� ��ȯ

	return 0;
}

int subcheck(int start_n, int end_n)//������ ����Ÿ�� Ȯ���ϴ� �Լ�
{
	int i, number, op, course_id = 0;

	for (i = start_n; i < end_n; i++) //i�� ���ۺ��� ������������
	{
		if (*buffer == NULL) //������ ���� NULL �̸�
			instr[i] = NULL;//instr�� NULL �̴�

		number = instr[i] - '0';//instr�� ������ ���ڸ� ������ ���ڷ� ��ȯ�Ͽ� number�� �����Ѵ�.
		op = sqr(10, end_n - i); //10��(1,2,3,....,end_n-i-1)�� �����ݴϴ�.(�ڸ���)
		course_id = course_id + op * number;//course_id�� �ڸ������� �����ݴϴ�.
	}

	return course_id;//course_id�� ��ȯ�մϴ�.
}
