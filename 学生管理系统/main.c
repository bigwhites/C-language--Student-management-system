//�Ŀγ����   ѧ������ϵͳv1.0

#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<Windows.h>
#include"head.h"

int main(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);//�ı�������ɫ
	char username[10]="admin";
	char user[10];
	printf("��ӭ�����人��֯��ѧѧ����Ϣ����ϵͳv1.0\n");
	do
	{
		printf("\n�������û���>>>");
		scanf("%s", user);
		int noUser = 1;
		noUser = strcmp(user, username);
		if (!noUser)
		{
			printf("\a\n��ӭ����%s! ", user);
			break;
		}
		else
		{
			puts("����ʧ�ܣ������ǹ���Ա!");
		}
	} while (1);
	checkin();//�ɹ������û�����������ܽ���
	printf("\n		��ӭ�����人��֯��ѧѧ������ϵͳv1.0!   (*^��^*)\n");
	menu();
	system("pause");
	return 0;
}