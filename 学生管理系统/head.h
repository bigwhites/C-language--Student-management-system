
typedef struct node
{
	char name[15];
	char sex[2];
	long long tele;//�绰
	int socre;//ѧ��¼ȡ����
	char stunumber[19];//ѧ��
	long long  birth;
	char class[20];//רҵ
	double GPA;
}stu;

typedef struct stulisted
{
	stu value;
	struct stulisted* next;
}studentlist;//������Ϊ�ṹ��ĵ�����

//��������
void checkin();
void menu();
void AddStudent(studentlist** head);
int PrintStudent(studentlist* head);
int SearchStudent(studentlist* head);
void saveout(studentlist* head);
void readin(studentlist** head);
void DelStudent(studentlist** head);
int ChangeStudent();
studentlist* GPA_sort();