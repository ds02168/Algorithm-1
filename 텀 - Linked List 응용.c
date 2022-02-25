#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define Max_id 500 //�л���
#define Max_course 35 //�ڽ���

typedef struct enroll_s *enroll_sp;
typedef struct enroll_s {
	char alpha; //�߰�(A)���� ����(D)���� �����ϴ� ����
	int id_num; //ID�� �����ϴº���
	int course_num; //�ڽ��� �����ϴ� ����
	enroll_sp right; //���� id�� ���������� ���� ��带 ����ŵ�ϴ�.
	enroll_sp left; //���� �ڽ��� ���������� ���� ��带 ����ŵ�ϴ�.
}enroll_s;//�ڷ��� ��Ī enroll_s�� ������ enroll_sp�� �����մϴ�.

enroll_sp courses[Max_course]; //course�� �ڽ�������  ����ü �ּҵ��� �����ϴ� �迭
enroll_sp students[Max_id]; //students�� �л�ID������ ����ü �ּҵ��� �����ϴ� �迭

FILE *fp1, *fp2; //fp1�� ���Ͽ���, fp2�� �������

int course_number, id_number; //�ڽ���ȣ,�л���ȣ
char alpha; //A(�߰�) �Ǵ� D(����)�� �����ϴ� ����
int nonalpha = 0, same = 0, emp = 0, courseerr = 0, iderr = 0, ErrRsn = 0;
//������ ������,�ߺ�������,�̵�Ͽ������� �����ϴ� ������ ����
//�ڽ��������� �����ϴ� ����,ID�������� �����ϴ� ����,���ٴ� ���������� �����ϴ� ������ ����
char arr[25]; //0~25���� ���ۿ��� �ҷ����̴� �迭
char buffer[50]; //input ������ ������ �ѹ��ھ� �����մϴ�.

//��������

int interger(int, int);
int check_input();//���� ���� �Ǵ� �Լ�
int Error(int);//���� ���� Ȯ�� �Լ�
int add();//���� �Լ�
int del();//���� �Լ�
int read(int, int);//�Է� ������ ���ڸ� �����ͷ� �о�帮�� �Լ�
void print_node(enroll_sp, int);//�����͸� ����ϴ� �Լ�

//�Լ�����


int main()
{
	int  in = 0; //in�� ��ϰ����� �����ϴ� ����
	int cancel = 0; //cancel�� ��� ������ �����ϴ� ����
	int	card = 0; //card�� ���������� ���� ���� �����ϴ� ����
	int count = 0; //count�� �ݺ����� Ƚ���� ���� ���� ����

	if ((fp1 = fopen("C:\\Users\\K\\Desktop\\input.txt", "r")) != NULL) //input������ �б��������� fp1���� ���ϴ�.
		printf("�����б� �Ϸ�\n"); //�����۵��� Ȯ�� ���

	else//������
	{
		printf("��θ� �ٽ� Ȯ���� �ּ���.\n"); // �������
		return 1;//����
	}

	fp2 = fopen("C:\\Users\\K\\Desktop\\output.txt", "w"); //output������ ������������ �ҷ��ɴϴ�.

	for (count = 0; count < Max_id; count++)
		students[count] = NULL; //students �迭�� NULL�� �ʱ�ȭ ���ݴϴ�.

	for (count = 0; count < Max_course; count++)
		courses[count] = NULL;//course �迭�� NULL�� �ʱ�ȭ ���ݴϴ�.

	fprintf(fp2, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (fgets(buffer, sizeof(buffer), fp1)) //input������ 50���ھ� buffer�迭�� �����մϴ�,���� ��ȿ�ϴ� ����
	{
		if (strcmp("end of file", buffer) == 0) //end of file�� ������
			break; //����

		card++; //card 1����
		strcpy(arr, buffer); //buffer�迭�� arr�迭�� �����մϴ�.
		ErrRsn = check_input(); //reasonsofError�� ����κп��� ���������� ���� ���� �����մϴ�.
		fprintf(fp2, "%d,  %d, %c ", id_number, course_number, alpha);//���پ� input�� �Է�� ������ ����մϴ�.

		if (ErrRsn) // ���� ������ ������
		{
			Error(ErrRsn);//����
			continue;//���
		}

		else //������
		{
			switch (alpha) // ���ĺ���
			{
			case 'A'://A�̸�
				if (add())//���Կ� ������ ������
					Error(1);//1�� ���� ���(�ߺ�)
				else in++; //��� ���� ����
				break;

			case 'D'://D�̸�
				if (del())//������ ������ ������
					Error(2);//2�� ���� ���(�̵��)
				else//������ ������
				{
					cancel++; //��� ���� ����
					fprintf(fp2, "          ** �����Ϸ�**");//���� ���
				}
				break;//swhitch ���� ����
			}

		}
		fprintf(fp2, "\n");//���پ� ����ݴϴ�.
	}

	fprintf(fp2, "\n\n");//���� ����ݴϴ�.


	for (count = 1; count < Max_course; count++) //�ڽ����� �з�
	{
		if (courses[count] != NULL)//�ڽ��� �����Ѵٸ�
		{
			fprintf(fp2, "%d: ", courses[count]->course_num);//���
			print_node(courses[count], 0);//����Լ� ȣ��
		}
	}

	fprintf(fp2, "\n[��������]   ** �ߺ���ϼ� **:  %d", same);
	fprintf(fp2, "   ** �̵�ϼ� **:  %d", emp);
	fprintf(fp2, "   ** ��ȿ���� �ʴ� �ڽ�ID **:  %d", courseerr);
	fprintf(fp2, "   ** ��ȿ���� �ʴ� �л�ID **:  %d", iderr);
	fprintf(fp2, "   ** A Ȥ�� D�� �ƴ� **:  %d\n\n", nonalpha);
	fprintf(fp2, "\n[�Էº���]   ** ����ī��� **: %d", card);
	fprintf(fp2, "   ** ��ȿ��� **: %d", in);
	fprintf(fp2, "   ** ��� **: %d\n", cancel);//Ư�̻��� ����
	fprintf(fp2, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	fclose(fp1);
	fclose(fp2);//���ϵ��� �ݽ��ϴ�.

	return 0;
}



int add()
{
	enroll_sp ptr, temp; //ù ������ ptr,
	int i, j, infinite = 1;//id_number�� ���� ���� i, course_number�� ���� ���� j,���¸� �����ϴ� ���� infinite

	i = id_number - 2000;//i�� students�ε����� 0~499�̹Ƿ�  -2000�Ͽ� �ε����� id_number������ ���̸� �����ݴϴ�.ex)id_number[2001]�� students[1]
	j = course_number - 100;//j�� course�ε����� 0~34�̹Ƿ� -100���Ͽ� �ε����� course_number������ ���̸� �����ݴϴ�. ex)course[101]�� course[1]

	ptr = (enroll_s *)malloc(sizeof(enroll_s));//ptr����� ���� ũ�� �Ҵ�
	ptr->id_num = id_number;//�����ϰ����ϴ� id_number�� ptr����ü�� id_num�� �����մϴ�.
	ptr->course_num = course_number;//�����ϰ����ϴ� course_number�� ptr����ü�� course_num�� �����մϴ�.
	ptr->right = NULL;
	ptr->left = NULL;//���� ��ũ�� NULL�� �ʱ�ȭ

	if (!students[i])//students[id_number-2000]�� NULL�̸�
		students[i] = ptr; //pn��° students �迭�� ptr�� ����

	else if (students[i]->course_num == ptr->course_num) //id_number�� �ڽ��� ptr�� �ڽ��� ������
		return 2;//2�� ��ȯ�մϴ�.(�ߺ�����)

	else //�Ǵ� 
	{
		temp = students[i];//pn���� students�迭�� ���� temp ��忡 �����Ѵ�.
		while (infinite)//������� 1�̹Ƿ� ���ѷ���
		{
			if (temp->right == NULL)//temp�� link�� NULL�̶��(temp�� ������ ����϶�)
			{
				ptr->right = NULL; //ptr�� link�� NULL�� �����ϰ�
				temp->right = ptr;//temp�� link�� ptr�ּҰ��� �����Ѵ�.
				infinite = 0;//������� 0���� �ٲپ� ���� ������ ���� �ʴ´�
			}

			else if ((ptr->course_num) < (temp->right->course_num))//�Ǵ� ptr�� �ڽ��� temp�� ����Ű�� ����� �ڽ������� ������
			{
				ptr->right = temp->right;//ptr�� link�� temp�� link�� �����ϰ�
				temp->right = ptr;//temp�� link�� ptr�� �ּҸ� ����Ű�� �Ѵ�
				infinite = 0;
			}

			else if (ptr->course_num == temp->right->course_num)//�Ǵ� ptr�� �ڽ����� temp�� ����Ű�� ����� �ڽ����� ������
				return 2;//2�� ��ȯ(�ߺ� ����)

			else//�Ǵ�(temp�� ����Ű�� ��尡 �������� �ʴ°��)
				temp = temp->right;//temp�� temp�� ����Ű���� �Ѵ�.
		}
	}

	if (!courses[j]) //j��° �ڽ��� NULL�϶�
		courses[j] = ptr; //ptr�� �ּҰ��� course[j]�� ����

	else //j��° �ڽ��� ���� ������ ������
	{
		temp = courses[j]; //temp ��忡 j��° course �迭 ��带 �����Ѵ�.
		infinite = 1; //������ 1�� �Ѵ�.
		while (infinite)
		{
			if (temp->left == NULL)//temp�� left�� NULL�϶�(temp�� ������ ����϶�)
			{
				ptr->left = NULL;//ptr�� left�� NULL�� �����Ѵ�.
				temp->left = ptr;//temp�� left�� ptr�� �ּҰ��� �����մϴ�.
				infinite = 0;//infinite�� 0���� �����Ͽ� ���� ������ ���� �ʽ��ϴ�.
			}

			else if ((ptr->id_num) < (temp->left->id_num)) //ptr�� id_num�� temp�� ����Ű�� ����� id_num���� ������
			{
				ptr->left = temp->left;//temp�� ����Ű�� �ּҸ� ptr�� left�� �����մϴ�.
				temp->left = ptr;//temp�� ptr�� ����ŵ�ϴ�.
				infinite = 0;
			}

			else //�Ǵ�
				temp = temp->left;//������ �ڱ��ڽ��� ����Ų��.
		}
	}

	return 0;//���������� �߰�
}

int del()// ���� �Լ�
{
	int i, j;
	enroll_sp ptr, temp;
	i = id_number - 2000;
	j = course_number - 100; //add�Լ��� ����(i�� id_number, j�� course)
	temp = students[i];//id_number - 2000���� ��带 temp ��忡 �����մϴ�.

	if (!students[i])//��尡 ������
		return 1;//1�� ��ȯ�մϴ�.(�̵�� ����)

	if (students[i]->id_num == id_number) //�����ϰ����ϴ� id_number���� �̹� �ִ�id_num�� ���� ��ġ�Ҵ�(��ȿ �Ҷ�)
	{
		students[i] = students[i]->right;//students[i]�� �ּҰ��� ���� ����� �ּҰ����� �ٲߴϴ�.
		ptr = temp;//ptr�� temp�� �ּҰ��� �־��ݴϴ�.
	}
	else if ((students[i]->id_num) > id_number)//������� �ϴ� id_number���� id_num���� ������ (�ּҰ��� �� ���� ��)
		return 1;//1�� ��ȯ�մϴ�.(�̵�� ����)
	else
	{
		ptr = temp->right; //temp->link�� �ּҰ��� ptr�� �ּҰ����� �����մϴ�.
		while (ptr)//ptr�� ���� NULL�� �ƴҶ�(����Ʈ �ȿ�������)
		{
			if (ptr->id_num == id_number)//id_num�� id_number�� ���� ��ġ�Ѵٸ�
				temp->right = ptr->right;//temp->right�� temp->right->right�� �ǵ��� �մϴ�.(�ǳʶ��)

			else //�Űܵ� �� �۴ٸ�
			{
				temp = ptr;
				ptr = ptr->right;//temp�� ptr�� ��ĭ�� ���̵�
			}

		}
		return 1;//�����尡 ���������� ���ٸ� �������� �����Ƿ� �̵�Ͽ���
	}

	temp = courses[j];//temp�� course[j]�� �ּҰ��� �Է��մϴ�.

	if (!courses[j])//�ڽ����� �������� �ʴ´ٸ�
		return 1;//1�� ��ȯ(�̵�� ����)

	if (courses[j]->course_num == course_number) //�����ϰ��� �ϴ� ���� ����� �ִ� ���� ��ġ�ϸ�
	{
		courses[j] = courses[j]->left; //course->left�� �ּҰ��� course�� �ּڰ��� ����
		ptr = temp;//ptr�� �ּҸ� temp�� �ּҷ� ����
	}

	else if ((courses[j]->course_num) > course_number)//�����ϰ����ϴ� ���� �����ϴ� ������ �۴ٸ�
		return 1;//1�� ��ȯ

	else//�����ϰ����ϴ� ���� �����ϴ� ������ ũ��
	{
		ptr = temp->left;//temp->left�ּҰ��� ptr�� �ּҿ� ����
		while (ptr)//ptr�� ��ȿ�ҵ���
		{
			if (ptr->course_num == course_number)//course_number�� course_num�� ���� ��ġ�Ѵٸ�(���� �ϰ����ϴ� ���� �����ϸ�)
				temp->left = ptr->left;//�Ѵܰ� �ǳʶپ� ����

			else//���� ��ġ ���� �ʴ´ٸ�
			{
				temp = ptr;
				ptr = ptr->left;//ptr�� temp�� ��带 �Ѵܰ辿 �ǳʶڴ�
			}

		}

		return 1;//ã�Ƶ� ������ ����x(�̵��)
	}

	free(temp);
	free(ptr);//�ӽó�� ����

	return 0;//���������� ����
}


int read(int first, int last)//������ ����Ÿ�� Ȯ���ϴ� �Լ�
{
	int i, num, result, sum = 0;

	for (i = first; i < last; i++) //i�� ���ۺ��� ������������
	{
		if (*buffer == NULL) //������ ���� NULL �̸�
			arr[i] = NULL;//arr�� NULL �̴�

		num = arr[i] - '0';//arr�� ������ ���ڸ� ������ ���ڷ� ��ȯ�Ͽ� num�� �����Ѵ�.
		result = interger(10, last - i); //10��(1,2,3,....,last-i-1)�� �����ݴϴ�.(�ڸ���)
		sum = sum + result * num;//sum�� �ڸ������� �����ݴϴ�.
	}

	return sum;//sum�� ��ȯ�մϴ�.
}

int check_input()//���Ϸκ��� ������ �ִ��� Ȯ���ϴ� �Լ�
{
	id_number = course_number = 0;// �л���ȣ = �ڽ���ȣ = 0
	id_number = read(3, 7);//4��° ����~ 8���� ���ڸ� �о� id_number�� ����
	course_number = read(13, 16); // 14��° ���� ~ 17��°���ڸ� �о� course_number�� ����
	alpha = arr[25]; //25��° ���ڸ� alpha�� �����մϴ�. (A�Ǵ�D)

	if ((course_number < 100) || (course_number > 100 + Max_course)) //course_number�� 100~135������ ���ڸ�
		return 3; //3�� ��ȯ

	if ((id_number < 2001) || (id_number > 2000 + Max_id))//id_number�� 2001~2500������ ���ڰ��ƴϸ�
		return 4; //4�� ��ȯ

	if ((alpha != 'A') && (alpha != 'D')) //A���ƴϰ� D�� �ƴϸ�
		return 5; //5�� ��ȯ

	return 0;
}


int Error(int value) // � �������� Ȯ���ϴ� �Լ�
{
	switch (value)
	{
	case 1: same++;//�ߺ���� ������ ����
		fprintf(fp2, "          ** �ߺ����**");//�ߺ���� ���� ���
		break; //����
	case 2: emp++;//�̵�� ������ ����
		fprintf(fp2, "          ** �̵��**");//�̵�� ���
		break;//����
	case 3: courseerr++;//�ڽ� ���̵�X
		fprintf(fp2, "          ** ��ȿ�����ʴ��ڽ�ID **\n"); //��ȿ�����ʴ� �ڽ� ���
		break;
	case 4: iderr++;//ID ����
		fprintf(fp2, "          ** ��ȿ�����ʴ��л�ID **\n"); //��ȿ���� �ʴ� �л�ID ���
		break;
	case 5: nonalpha++;//������ ����
		fprintf(fp2, "          ** 'A'Ȥ��'D'���ƴ�**\n"); //A Ȥ�� D�� �ƴ��� ���
		break;
	}

	return 0; //����x
}

void print_node(enroll_sp ptr, int data)//��� �Լ�
{
	if (!data)//data�� ���� ������
	{
		for (; ptr; ptr = ptr->left)
			fprintf(fp2, " %d, ", ptr->id_num);//�л� ��ȣ���� ���

	}
	else//���� ������ ������
		for (; ptr; ptr = ptr->right)
			fprintf(fp2, "%c, ", ptr->alpha);//�����ǵ��� ���
	fprintf(fp2, " \n");
}

int interger(int x, int y) //a�� 10,b�� end_n-i
{
	int total = 1, i;
	for (i = 0; i < y - 1; i++)//i�� 0���� end_n-i����
		total = total * x; //total�� x�� �����ݴϴ�.

	return total;//total�� ��ȯ�մϴ�.
}