//的课程设计   学生管理系统v1.0

#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<Windows.h>
#include"head.h"

int main(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);//改变字体颜色
	char username[10]="admin";
	char user[10];
	printf("欢迎来到武汉纺织大学学生信息管理系统v1.0\n");
	do
	{
		printf("\n请输入用户名>>>");
		scanf("%s", user);
		int noUser = 1;
		noUser = strcmp(user, username);
		if (!noUser)
		{
			printf("\a\n欢迎您，%s! ", user);
			break;
		}
		else
		{
			puts("登入失败，您不是管理员!");
		}
	} while (1);
	checkin();//成功输入用户名和密码才能进入
	printf("\n		欢迎进入武汉纺织大学学生管理系统v1.0!   (*^▽^*)\n");
	menu();
	system("pause");
	return 0;
}