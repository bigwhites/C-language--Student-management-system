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
		printf("\n输入密码以登录>>>");
		scanf("%s", password);
		if (!strcmp(password, pass))
		{
			int cha;
			printf("\n\n>>>>密码正确\n请问是否要改密码?(按1修改,0进入系统)>>>");
			scanf("%d", &cha);
			if (cha == 1)
			{
				char new[30];
				printf("\n请输入要修改的密码：");
				scanf("%s", new);
				fclose(Fp);
				Fp = fopen("password.txt", "w");
				fprintf(Fp, "%s", new);
				puts("\n\a修改成功！重新输入新密码:");
				scanf("%s", password);
				while (strcmp(password, new))
				{
					puts("\n\n密码错误！请重新输入：");
					scanf("%s", password);
				}
				printf("\n\n密码正确!欢迎进入系统！");
				fclose(Fp);
				return;

			}
			fclose(Fp);
			break;
		}
		else
		{
			printf("密码错误\n\a");
			system("pause");
		}
	}
}
void menu()  //主菜单和功能引导函数 
{
	int flag;
road1://用goto语句保证程序不退出

	printf("\n\n\n\t=======================**==#=主菜单=#==**======================\n");
	printf("\n\t*  1.添加学生信息                              *\n");                    
	printf("\n\t*  2.查看学生所有的信息                        *\n");
	printf("\n\t*  3.寻找学生信息                              *\n");
	printf("\n\t*  4.把信息保存至文件中                        *\n");
	printf("\n\t*  5.修改学生信息                              *\n");
	printf("\n\t*  6.读取历史信息                              *\n");
	printf("\n\t*  7.删除学生信息                              *\n");
	printf("\n\t*  8.按GPA对学生排序                           *\n");
	printf("\n\t*  9.退出系统                                  *\n");
	printf("\n\t===============================================================\n");
	printf("\n\t    请键入序号选择>>>>>>>");
	scanf("%d", &flag);//根据用户的选择进入相应功能



	if (flag == 1)
	{
		AddStudent(&head);
		goto road1;
	}

	else if (flag == 2)
	{
		if (!PrintStudent(head))
		{
			printf("\a\n\t    还没有信息，请先添加或者读取。\n");
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
			if (!r)printf("\n\t    没有该学生");
			printf("\n\n\t    键入0停止寻找、1继续>>>");
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
			printf("\n\t\a    输入的学生号不存在！");
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
		printf("是否保存数据（按0不保存）>>>");
		int a;
		scanf("%d", &a);
		if (a&&head!=NULL) saveout(head);
	}
	else
	{
		printf("\n\t    输入有误，请重新选择!\n");
		goto road1;
	}
}

void AddStudent(studentlist** head)   //新增学生信息 
{
	int x = 1;
	static  studentlist* tail;
	tail = *head;
	while (x)
	{
		studentlist* pworker = (studentlist*)malloc(sizeof(studentlist));
		pworker->next = NULL;
		printf("\n\t    请输入学生的学生号(学生号唯一)>>>");
		scanf("%s", pworker->value.stunumber);
		
		if (*head)  
		{
			for (studentlist* pcheck = *head; pcheck; pcheck = pcheck->next)//检查是否与已存在的信息重复
			{
				int no_same = 1;
				no_same = strcmp(pworker->value.stunumber, pcheck->value.stunumber);
				if (!no_same)
				{
					printf("\a\n\t    该学生号的学生已存在\n");
					return;//如果存在则直接结束新增返回主菜单
				}
			}
		}
		printf("\n\t    请输入姓名>>>");
		scanf("%s", &(pworker->value.name));
		fflush(stdin);
		printf("\n\t    请输入出生年月日>>>");
		scanf("%lld", &(pworker->value.birth));
		printf("\n\t    请输入电话>>>");
		scanf("%lld", &(pworker->value.tele));
		printf("\n\t    请输入性别>>>");
		scanf("%s", &(pworker->value.sex));
		printf("\n\t    请输入录取分数>>>");
		scanf("%d", &(pworker->value.socre));
		printf("\n\t    请输入班级>>>");
		scanf("%s", pworker->value.class);
		printf("\n\t    请输入GPA>>>");
		scanf("%lf", &(pworker->value.GPA));
		while (tail != NULL && tail->next != NULL)
		{
			tail = tail->next;//保证tail始终指向尾节点
		}
	//节点的拼接
		if (*head != NULL)//非首结点
		{
			tail->next = pworker;
			tail = tail->next;
		}
		else //为首节点
		{
			*head = pworker;
			tail = pworker;
		}
		printf("继续录入新的数据？（输入0结束）：\n");
		scanf("%d", &x);
	}
}

int PrintStudent(studentlist* head)  //打印信息函数  失败返回0 
{
	studentlist* p = head;
	if (head == NULL) return 0;
	else
	{
		printf("\n\t##**=====================================----学生信息----====================================================**##");
		while (p)
		{
			if (p->value.birth <= 20201111 && p->value.birth > 0&&p->value.birth>20000&&p->value.GPA)
				printf("\n\n\t  *  姓名:% s 性别 % s GPA:%.2lf 班级：%s 电话 % lld  录取分数： % d   学号 % s  生日 % lld   ", p->value.name, p->value.sex,p->value.GPA,p->value.class, p->value.tele, p->value.socre, p->value.stunumber, p->value.birth);
			p = p->next;
		}

	}
		printf("\n\t##**=======================================================================================================**##");
	return 1;
}

int SearchStudent(studentlist* head)   //寻找员工信息函数 
{
	studentlist* p = head;
	printf("\a\n\n\t    请输入学生名字以寻找信息：");
	char ch[15];
	scanf("%s", &ch);
	int x = 0;
	int nofound = 1;//默认没有该学生
	while (p)
	{
		nofound = strcmp(ch, p->value.name);//遍历链表找到同名学生后返回值为0
		if (!nofound)
		{
			printf("\n\n\t    姓名：%s 性别%s 电话%lld 录取分数%d   学号%s  生日%lld 班级%s：GPA:%.2lf", p->value.name, p->value.sex, p->value.tele, p->value.socre, p->value.stunumber, p->value.birth,p->value.class,p->value.GPA);
			x = 1;
		}

		p = p->next;
	}
	if (x == 1)return 1;
	return 0;
}

void saveout(studentlist* head)  //保存信息到文件中
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
		printf("\n\t    保存成功！");
	}
	else
	{
		printf("\n\t    还没有信息!\n");
		system("pause");
	}
	fclose(fp);

}

int ChangeStudent() //修改内存中的学生的信息
{
	char NoChange[10];
	printf("\n\t    请输入要修改的学生的学生号:");
	scanf("%s", &NoChange);
	for (studentlist* ptr = head; ptr; ptr = ptr->next)
	{
		int nofound = 1;
		nofound = strcmp(NoChange, ptr->value.stunumber);
		if (!nofound)
		{
			int t;
			printf("\n\t    将要修改%s的信息：", &(ptr->value.name));
			printf("\n\t请选择修改的内容：  1.电话 2.录取分数 3.姓名 4.班级（转专业）5.GPA 请输入：");
			scanf("%d", &t);
			if (t == 1)
			{
				printf("\n\t    请输入：");
				scanf("%lld", &(ptr->value.tele));
				printf("\n\t    修改成功！！");
				return 1;
			}
			if (t == 2)
			{
				printf("\n\t    请输入：");
				scanf("%d", &(ptr->value.socre));
				printf("\n\t    修改成功！！");
				return 1;
			}
			if (t == 3)
			{
				printf("\n\t    请输入：");
				scanf("%s", ptr->value.name);
				return 1;
			}
			if (t == 4)
			{
				printf("\n\t    请输入：");
				scanf("%s", ptr->value.class);
				return 1;
			}
			if (t == 5)
			{
				printf("\n\t    请输入：");
				scanf("%lf", &(ptr->value.GPA));
				return 1;
			}
		}
	}
	return 0;
}

void readin(studentlist** head) //从文件中读入学生数据
{
	FILE* fp = fopen("t.txt", "a+");
	char a;
	fscanf(fp, "%c  ", &a);
	fgetchar();
	if (fp == NULL || feof(fp))
	{
		printf("\n\t    没有历史记录\n");
		return;
	}
	else
	{
		static studentlist* tail;
		tail = *head;
		while (feof(fp) == 0)//没结束
		{

			studentlist* p = (studentlist*)malloc(sizeof(studentlist));
			p->next = NULL;
			if (!*head)//head为空指针
			{
				*head = p;
				tail = p;
			}
			else//非空指针
			{
				//让tail指向尾节点
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
	printf("\n\t	成功读取.");
	fclose(fp);
}

void DelStudent(studentlist** head)
{
	int _continue = 1;
	while (_continue)
	{
		if (!*head)
		{
			printf("\n\t    还没有学生数据!");
			return;
		}
		studentlist* pdel = *head;
		printf("\n\t	请输入要删除的学生的学生号>>>");
		char del[10];
		scanf("%s", del);
		int nosame = 1;
		for (; pdel; pdel = pdel->next)
		{
			nosame = strcmp(del, pdel->value.stunumber);
			//printf("%d", nosame);
			if (!nosame) break;
		}
		if (!nosame)//找到信息 并删除
		{
			if (pdel == *head)
			{
				if (pdel->next != NULL)
				{
					*head = pdel->next;
					puts("\n\t    删除成功.");
					return;
				}
				else
				{
					*head = NULL;
					puts("\n\t    删除成功.");
					return;
				}
			}
			studentlist* r, * s;
			r = *head;
			while (r->next != pdel)
				r = r->next;
			s = r->next;
			r->next = r->next->next;


			puts("\n\t    删除成功");
			break;
		}

		if (nosame) puts("\n\t    没有该学生号的学生！\n");

		puts("输入0结束删除并返回主菜单,按其他任意键继续删除其他学生>>>");
		scanf("%d", &_continue);
	}

}

studentlist* GPA_sort() //按照GPA对学生排序
{
	studentlist* pnewhead = NULL;//新链表头指针
	int linklen = 0;
	studentlist* pmax = head;
	for (studentlist* p = head;p; p = p->next)//计算链表长度
	{
		if (!p) break;
		linklen++;
	}
	if (linklen <= 2)
	{
		printf("\n\t    信息太少不可排序!\n");//三个数据以下不排序
		return head;
	}
	else
	{    //选择排序

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
			}//已经找到max
			studentlist* pnew = (studentlist*)malloc(sizeof(studentlist)); //新链表的节点
			pnew->next = NULL;
			//把当前GPA最高的学生的数据赋值给新链表并拼接新链表
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
	printf("\n\t    排序成功！");
	return pnewhead;
}