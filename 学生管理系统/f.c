#include<stdio.h>
#include"head.h"
#include<stdlib.h>
#include<string.h> 
#include<Windows.h>
studentlist* head = NULL;
void checkin()
{
	FILE* Fp = fopen("password.txt" ,"at+ ");
	char password[30];
	char pass[30];
	fscanf(Fp, "%s", pass);
	while (1)
	{
		printf("\n���������Ե�¼>>>");
		scanf("%s", password);
		if (!strcmp(password, pass))
		{
			int cha;
			printf("\n\n>>>>������ȷ\n�����Ƿ�Ҫ������?(��1�޸�,0����ϵͳ)>>>");
			scanf("%d", &cha);
			if (cha == 1)
			{
				char new[30];
				printf("\n������Ҫ�޸ĵ����룺");
				scanf("%s", new);
				fclose(Fp);
				Fp = fopen("password.txt", "w");
				fprintf(Fp, "%s", new);
				puts("\n\a�޸ĳɹ�����������������:");
				scanf("%s", password);
				while (strcmp(password, new))
				{
					puts("\n\n����������������룺");
					scanf("%s", password);
				}
				printf("\n\n������ȷ!��ӭ����ϵͳ��");
				fclose(Fp);
				return;

			}
			fclose(Fp);
			break;
		}
		else
		{
			printf("�������\n\a");
			system("pause");
		}
	}
}
void menu()  //���˵��͹����������� 
{
	int flag;
road1://��goto��䱣֤�����˳�

	printf("\n\n\n\t=======================**==#=���˵�=#==**======================\n");
	printf("\n\t*  1.���ѧ����Ϣ                              *\n");                    
	printf("\n\t*  2.�鿴ѧ�����е���Ϣ                        *\n");
	printf("\n\t*  3.Ѱ��ѧ����Ϣ                              *\n");
	printf("\n\t*  4.����Ϣ�������ļ���                        *\n");
	printf("\n\t*  5.�޸�ѧ����Ϣ                              *\n");
	printf("\n\t*  6.��ȡ��ʷ��Ϣ                              *\n");
	printf("\n\t*  7.ɾ��ѧ����Ϣ                              *\n");
	printf("\n\t*  8.��GPA��ѧ������                           *\n");
	printf("\n\t*  9.�˳�ϵͳ                                  *\n");
	printf("\n\t===============================================================\n");
	printf("\n\t    ��������ѡ��>>>>>>>");
	scanf("%d", &flag);//�����û���ѡ�������Ӧ����



	if (flag == 1)
	{
		AddStudent(&head);
		goto road1;
	}

	else if (flag == 2)
	{
		if (!PrintStudent(head))
		{
			printf("\a\n\t    ��û����Ϣ��������ӻ��߶�ȡ��\n");
		}
		goto road1;
	}

	else if (flag == 3)
	{
		int _continue = 1;
		while (_continue)
		{
			int r=0;
			r=SearchStudent(head);
			if (!r)printf("\n\t    û�и�ѧ��");
			printf("\n\n\t    ����0ֹͣѰ�ҡ�1����>>>");
			fflush(stdin);
			scanf("%d", &_continue);
		}
		goto road1;
	}

	else if (flag == 4)
	{
		saveout(head);
		goto road1;
	}
	else if (flag == 5)
	{
		int result = ChangeStudent();
		if (result == 0)
		{
			printf("\n\t\a    �����ѧ���Ų����ڣ�");
			Sleep(500);
		}
		goto road1;
	}
	else if (flag == 6)
	{
		readin(&head);
		goto road1;
	}
	else if (flag == 7)
	{
		DelStudent(&head);
		goto road1;
	}
	else if (flag == 8)
	{
		head = GPA_sort();
		goto road1;
	}

	else if (flag == 9)
	{
		printf("�Ƿ񱣴����ݣ���0�����棩>>>");
		int a;
		scanf("%d", &a);
		if (a&&head!=NULL) saveout(head);
	}
	else
	{
		printf("\n\t    ��������������ѡ��!\n");
		goto road1;
	}
}

void AddStudent(studentlist** head)   //����ѧ����Ϣ 
{
	int x = 1;
	static  studentlist* tail;
	tail = *head;
	while (x)
	{
		studentlist* pworker = (studentlist*)malloc(sizeof(studentlist));
		pworker->next = NULL;
		printf("\n\t    ������ѧ����ѧ����(ѧ����Ψһ)>>>");
		scanf("%s", pworker->value.stunumber);
		
		if (*head)  
		{
			for (studentlist* pcheck = *head; pcheck; pcheck = pcheck->next)//����Ƿ����Ѵ��ڵ���Ϣ�ظ�
			{
				int no_same = 1;
				no_same = strcmp(pworker->value.stunumber, pcheck->value.stunumber);
				if (!no_same)
				{
					printf("\a\n\t    ��ѧ���ŵ�ѧ���Ѵ���\n");
					return;//���������ֱ�ӽ��������������˵�
				}
			}
		}
		printf("\n\t    ����������>>>");
		scanf("%s", &(pworker->value.name));
		fflush(stdin);
		printf("\n\t    ���������������>>>");
		scanf("%lld", &(pworker->value.birth));
		printf("\n\t    ������绰>>>");
		scanf("%lld", &(pworker->value.tele));
		printf("\n\t    �������Ա�>>>");
		scanf("%s", &(pworker->value.sex));
		printf("\n\t    ������¼ȡ����>>>");
		scanf("%d", &(pworker->value.socre));
		printf("\n\t    ������༶>>>");
		scanf("%s", pworker->value.class);
		printf("\n\t    ������GPA>>>");
		scanf("%lf", &(pworker->value.GPA));
		while (tail != NULL && tail->next != NULL)
		{
			tail = tail->next;//��֤tailʼ��ָ��β�ڵ�
		}
	//�ڵ��ƴ��
		if (*head != NULL)//���׽��
		{
			tail->next = pworker;
			tail = tail->next;
		}
		else //Ϊ�׽ڵ�
		{
			*head = pworker;
			tail = pworker;
		}
		printf("����¼���µ����ݣ�������0��������\n");
		scanf("%d", &x);
	}
}

int PrintStudent(studentlist* head)  //��ӡ��Ϣ����  ʧ�ܷ���0 
{
	studentlist* p = head;
	if (head == NULL) return 0;
	else
	{
		printf("\n\t##**=====================================----ѧ����Ϣ----====================================================**##");
		while (p)
		{
			if (p->value.birth <= 20201111 && p->value.birth > 0&&p->value.birth>20000&&p->value.GPA)
				printf("\n\n\t  *  ����:% s �Ա� % s GPA:%.2lf �༶��%s �绰 % lld  ¼ȡ������ % d   ѧ�� % s  ���� % lld   ", p->value.name, p->value.sex,p->value.GPA,p->value.class, p->value.tele, p->value.socre, p->value.stunumber, p->value.birth);
			p = p->next;
		}

	}
		printf("\n\t##**=======================================================================================================**##");
	return 1;
}

int SearchStudent(studentlist* head)   //Ѱ��Ա����Ϣ���� 
{
	studentlist* p = head;
	printf("\a\n\n\t    ������ѧ��������Ѱ����Ϣ��");
	char ch[15];
	scanf("%s", &ch);
	int x = 0;
	int nofound = 1;//Ĭ��û�и�ѧ��
	while (p)
	{
		nofound = strcmp(ch, p->value.name);//���������ҵ�ͬ��ѧ���󷵻�ֵΪ0
		if (!nofound)
		{
			printf("\n\n\t    ������%s �Ա�%s �绰%lld ¼ȡ����%d   ѧ��%s  ����%lld �༶%s��GPA:%.2lf", p->value.name, p->value.sex, p->value.tele, p->value.socre, p->value.stunumber, p->value.birth,p->value.class,p->value.GPA);
			x = 1;
		}

		p = p->next;
	}
	if (x == 1)return 1;
	return 0;
}

void saveout(studentlist* head)  //������Ϣ���ļ���
{
	FILE* fp;
	fp = fopen("t.txt", "w");
	studentlist* p = head;
	if (head)
	{

		while (p)
		{
			if (p == head)fprintf(fp, ".");
			if (p->value.birth > 0&&p->value.GPA>0.2)			{
				fprintf(fp, "%s %s %lld %d %s %lld %s %.2lf\n", p->value.name, p->value.sex, p->value.tele, p->value.socre, p->value.stunumber, p->value.birth,p->value.class,p->value.GPA);
			}
			p = p->next;
		}
		printf("\n\t    ����ɹ���");
	}
	else
	{
		printf("\n\t    ��û����Ϣ!\n");
		system("pause");
	}
	fclose(fp);

}

int ChangeStudent() //�޸��ڴ��е�ѧ������Ϣ
{
	char NoChange[10];
	printf("\n\t    ������Ҫ�޸ĵ�ѧ����ѧ����:");
	scanf("%s", &NoChange);
	for (studentlist* ptr = head; ptr; ptr = ptr->next)
	{
		int nofound = 1;
		nofound = strcmp(NoChange, ptr->value.stunumber);
		if (!nofound)
		{
			int t;
			printf("\n\t    ��Ҫ�޸�%s����Ϣ��", &(ptr->value.name));
			printf("\n\t��ѡ���޸ĵ����ݣ�  1.�绰 2.¼ȡ���� 3.���� 4.�༶��תרҵ��5.GPA �����룺");
			scanf("%d", &t);
			if (t == 1)
			{
				printf("\n\t    �����룺");
				scanf("%lld", &(ptr->value.tele));
				printf("\n\t    �޸ĳɹ�����");
				return 1;
			}
			if (t == 2)
			{
				printf("\n\t    �����룺");
				scanf("%d", &(ptr->value.socre));
				printf("\n\t    �޸ĳɹ�����");
				return 1;
			}
			if (t == 3)
			{
				printf("\n\t    �����룺");
				scanf("%s", ptr->value.name);
				return 1;
			}
			if (t == 4)
			{
				printf("\n\t    �����룺");
				scanf("%s", ptr->value.class);
				return 1;
			}
			if (t == 5)
			{
				printf("\n\t    �����룺");
				scanf("%lf", &(ptr->value.GPA));
				return 1;
			}
		}
	}
	return 0;
}

void readin(studentlist** head) //���ļ��ж���ѧ������
{
	FILE* fp = fopen("t.txt", "a+");
	char a;
	fscanf(fp, "%c  ", &a);
	fgetchar();
	if (fp == NULL || feof(fp))
	{
		printf("\n\t    û����ʷ��¼\n");
		return;
	}
	else
	{
		static studentlist* tail;
		tail = *head;
		while (feof(fp) == 0)//û����
		{

			studentlist* p = (studentlist*)malloc(sizeof(studentlist));
			p->next = NULL;
			if (!*head)//headΪ��ָ��
			{
				*head = p;
				tail = p;
			}
			else//�ǿ�ָ��
			{
				//��tailָ��β�ڵ�
				while (tail->next)
				{
					tail = tail->next;
				}
				tail->next = p;
				tail = tail->next;
				fscanf(fp, "%s %s %lld %d %s %lld %s %lf", p->value.name, p->value.sex, &(p->value.tele),&( p->value.socre), p->value.stunumber,&( p->value.birth),p->value.class,&(p->value.GPA));
			}
		}
	}
	printf("\n\t	�ɹ���ȡ.");
	fclose(fp);
}

void DelStudent(studentlist** head)
{
	int _continue = 1;
	while (_continue)
	{
		if (!*head)
		{
			printf("\n\t    ��û��ѧ������!");
			return;
		}
		studentlist* pdel = *head;
		printf("\n\t	������Ҫɾ����ѧ����ѧ����>>>");
		char del[10];
		scanf("%s", del);
		int nosame = 1;
		for (; pdel; pdel = pdel->next)
		{
			nosame = strcmp(del, pdel->value.stunumber);
			//printf("%d", nosame);
			if (!nosame) break;
		}
		if (!nosame)//�ҵ���Ϣ ��ɾ��
		{
			if (pdel == *head)
			{
				if (pdel->next != NULL)
				{
					*head = pdel->next;
					puts("\n\t    ɾ���ɹ�.");
					return;
				}
				else
				{
					*head = NULL;
					puts("\n\t    ɾ���ɹ�.");
					return;
				}
			}
			studentlist* r, * s;
			r = *head;
			while (r->next != pdel)
				r = r->next;
			s = r->next;
			r->next = r->next->next;


			puts("\n\t    ɾ���ɹ�");
			break;
		}

		if (nosame) puts("\n\t    û�и�ѧ���ŵ�ѧ����\n");

		puts("����0����ɾ�����������˵�,���������������ɾ������ѧ��>>>");
		scanf("%d", &_continue);
	}

}

studentlist* GPA_sort() //����GPA��ѧ������
{
	studentlist* pnewhead = NULL;//������ͷָ��
	int linklen = 0;
	studentlist* pmax = head;
	for (studentlist* p = head;p; p = p->next)//����������
	{
		if (!p) break;
		linklen++;
	}
	if (linklen <= 2)
	{
		printf("\n\t    ��Ϣ̫�ٲ�������!\n");//�����������²�����
		return head;
	}
	else
	{    //ѡ������

		double max=0;
		studentlist* pnewtail=NULL;
		for (int i = 1; i <= linklen; ++i)
		{
			for (studentlist* psort = head; psort; psort = psort->next)
			{
				if (psort->value.GPA > max)
				{
					max = psort->value.GPA;
					pmax = psort;
				}
			}//�Ѿ��ҵ�max
			studentlist* pnew = (studentlist*)malloc(sizeof(studentlist)); //������Ľڵ�
			pnew->next = NULL;
			//�ѵ�ǰGPA��ߵ�ѧ�������ݸ�ֵ��������ƴ��������
			if (!pnewhead)
			{
				pnew->value = pmax->value;
				pnewhead = pnew;
				pnewtail = pnew;
			}
			else
			{
				pnew->value = pmax->value;
				pnewtail->next = pnew;
				pnewtail = pnew;
			}
			pmax->value.GPA = 0;
			max = 0;
			

		}
	}
	printf("\n\t    ����ɹ���");
	return pnewhead;
}