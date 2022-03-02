
typedef struct node
{
	char name[15];
	char sex[2];
	long long tele;//电话
	int socre;//学生录取分数
	char stunumber[19];//学号
	long long  birth;
	char class[20];//专业
	double GPA;
}stu;

typedef struct stulisted
{
	stu value;
	struct stulisted* next;
}studentlist;//数据域为结构体的单链表

//函数声明
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