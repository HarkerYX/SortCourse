#include"ReadFile.h"
#include"Graph.h"

#include<queue>
#include<iomanip>

#define h_term_num 8

//C:\Users\asus\Desktop\Sort\course_inf1.txt

//ȫ�ֱ���
queue<int>  q[h_term_num + 1];
char course_table[h_term_num + 1][10][6][100];//ѧ�ڡ��ڴΡ����ڡ��γ���
int numsOfTerm[h_term_num];



//��ӡ����
void printMenu(char *fileName);
//����
void makeGraph(Graph &gra, Course* courses, int numOfCourses);
//��������
bool topological_order(Graph &gra,Course* courses);
//�����Ϊ0�Ķ������Ӧ�Ķ���
void zero_indgree_push(Graph &gra, Course*courses);
//�ſ�
bool range(int num, int term, char* name);
//�����ſ�
bool range_one(int &week_day, int term, char* course_name);
bool range_two(int &week_day, int term, char* course_name);
bool range_three(int &week_day, int term, char* course_name);
//���ҿտΣ������ص�һ�ڿεĽڴ�
int find_one(int week_day, int term);
int find_two(int week_day, int term);
int find_three(int week_day, int term);


int main()
{
	//��ӡ�˵�����ȡ�ļ���
	char fileName[100];
	printMenu(fileName);
	
	//��ȡ�γ���Ϣ
	Course *temp = new Course[100];
	int allCourse;
	allCourse = getAllCourseFromFile(temp,fileName,numsOfTerm);
	if (allCourse < 0)
	{
		cout << "�ſ�ʧ�ܣ�" << endl;
		return 1;
	}

	//��ͼ
	Graph gra(allCourse);
	makeGraph(gra, temp, allCourse);

	//��տα�
	for (int i = 1; i <=h_term_num; i++)                     //ѧ����
		for (int j = 1; j <= 9; j++)                        //�ڴ�
			for (int k = 1; k <= 5; k++)                     //����   
				strcpy(course_table[i][j][k], "");

	//�ز�����
	if (!topological_order(gra, temp))
	{
		//�ͷ���Դ
		delete[]temp;
		cout << "�ſ�ʧ��!" << endl;
		return 1;
	}

	cout << endl;
	cout << "�ſ���ɣ���ָ��Ҫ������ļ���" << endl;
	cin >> fileName;

	//������ļ�
	fstream outcome(fileName, ios::out);
	if (!outcome)
	{
		cout << "���ļ�ʧ��!" << endl;
		return 0;
	}
	
	for (int i = 1; i <= 8; i++)
	{
		
		outcome << '\t' << '\t' << '\t' << '\t' << '\t' << "XXרҵ��" << i << "ѧ�ڿα�" << endl;
		outcome << endl;
		outcome <<setw(20)<< "����";
		outcome << setw(20) << "����һ";
		outcome << setw(20) << "���ڶ�";
		outcome << setw(20) << "������";
		outcome << setw(20) << "������";
		outcome << setw(20) << "������";
		outcome << endl;
		for (int j = 1; j <= 9; j++)
		{
			outcome << setw(20) << "��" << j << "��";
			for (int k = 1; k <= 5; k++)
			{
				
				outcome << setw(20) << course_table[i][j][k];
			}
			outcome << endl;
			outcome << endl;
		}

		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
	}

	cout << "������!" << endl;
	//�ͷ���Դ
	delete[]temp;
	outcome.close();
	return 0;
}

//����ͨ�� ���ش�
//���ڣ�2016/12/17/11:20
//���ߣ����ش�
//��ӡ���棬��ȡҪ�ſε��ļ���
void printMenu(char *fileName)
{
	cout << "******************************************************" << endl;
	cout << "                 ��ӭʹ���ſ�ϵͳv1.0:)               " << endl;
	cout << "******************************************************" << endl;
	cout << "������γ��ļ�����" << endl;
	cin >> fileName;

	return;
}

void makeGraph(Graph &gra, Course* courses, int numOfCourses)
{
	vector<string> conditions;
	for (int i = 0; i < numOfCourses; i++)
	{
		if (courses[i].IsLimit())
		{
			conditions = courses[i].getCondition();
			for (int j = 0; j < (int)conditions.size(); j++)
			{
				for (int k = 0; k < numOfCourses; k++)
				{
					if (courses[k].getCode()==conditions.at(j))
					{
						gra.setEdge(k, i, 1);
						break;
					}
				}
			}
		}
	}

	return;
}

//�ز�����
bool topological_order(Graph &gra, Course* courses)
{

	zero_indgree_push(gra, courses);
	//��term�ж�Ӧ�Ŀγ��ſ�
	int v;
	int size;
	Course course;
	char name[100];
	for (int term = 1; term <= h_term_num; term++)
	{
		size = (int)q[term].size();
		for (int i = 0; i<size; i++)
		{
			v = q[term].front();
			q[term].pop();
			//�ſ�
			course = courses[v];
			strncpy(name, course.getName().data(), 99);
			range(course.getStudyTime(), term,name);
			
			//����Խv���ڵĶ�����ȼ�һ
			gra.subOneInDegree(v);
			
			//���
			int *inDegrees = gra.getAllIndegree();
			for (int j = 0; j < gra.n(); j++)
			{
				if (0 == inDegrees[j]&&(0==courses[j].getTerm()||courses[j].getTerm()>term)&&0==gra.getMark(j))
				{
					q[courses[j].getTerm()].push(j);
					gra.setMark(j, 1);//����Ѿ�����
				}
				else if(0 == inDegrees[j] && (courses[j].getTerm()>0 && courses[j].getTerm()<=term)&&0==gra.getMark(j))
				{
					cout << "�γ̳�ͻ���ſν�����" << endl;
					return false;;
				}
				//C:\Users\asus\Desktop\Sort\course_inf1.txt
			}
			
		}

		for (int i = 0;i<numsOfTerm[term-1]-size; i++)
		{
			v = q[0].front();
			q[0].pop();
			//�ſ�
			course = courses[v];
			strncpy(name, course.getName().data(), 99);
			range(course.getStudyTime(), term, name);
			//����Խv���ڵĶ�����ȼ�һ
			gra.subOneInDegree(v);

			//���
			int *inDegrees = gra.getAllIndegree();
			for (int j = 0; j < gra.n(); j++)
			{
				if (0 == inDegrees[j] && (0 == courses[j].getTerm() || courses[j].getTerm()>term) && 0 == gra.getMark(j))
				{
					q[courses[j].getTerm()].push(j);
					gra.setMark(j, 1);//����Ѿ�����
				}
				else if (0 == inDegrees[j] && (0 < courses[j].getTerm() && courses[j].getTerm()<=term)&& 0 == gra.getMark(j))
				{
					cout << "�γ̳�ͻ���ſν�����" << endl;
					return false;
				}
			}
			
		}
	}

	for (int i = 0; i < gra.n(); i++)
	{
		if (0 == gra.getMark(i))
		{
			cout<<"��δ�������пγ̣��ſ�ʧ�ܣ�";
			return false;
		}
	}
	
	return true;
}

void zero_indgree_push(Graph &gra,Course*courses)
{
	int *inDegrees = gra.getAllIndegree();
	//����Ϊ0�ĵ����Ӧ�Ķ���
	for (int i = 0; i < gra.n(); i++)
	{
		if (0 == inDegrees[i])
		{
			q[courses[i].getTerm()].push(i);
			gra.setMark(i, 1);//����Ѿ�����
		}
	}
}

//�ſ�
bool range(int num, int term, char* name)
{
	int static week_day = 1;

	if (num==1)
	{
		if (range_one(week_day,term,name)==false)
		{
			return false;
		}
		else
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
			return true;
		}
	}
	else if (num % 3 == 0)
	{
		for (int i = 0; i < num/3; i++)
		{
			if (range_three(week_day, term, name) == false)
			{
				return false;
			}
			else
			{
				week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
				return true;
			}
		}
	}
	else if (num % 2 == 0)
	{
		for (int i = 0; i < num / 2; i++)
		{
			if (range_two(week_day, term, name) == false)
			{
				return false;
			}
			else
			{
				week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
				return true;
			}
		}
	}
	else if (5 == num)
	{
		if (range_three(week_day, term, name) == false)
		{
			return false;
		}
		else
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
			if (range_two(week_day, term, name) == false)
			{
				return false;
			}
			else
			{
				week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
				return true;
			}
		}
	}
	return false;
}

//�����ſΣ���һ�ڿ�
bool range_one(int &week_day, int term, char* course_name)
{
	int local;
	for (int i = 0; i < 5; i++)
	{
		local = find_one(week_day, term);
		if (-1 == local)
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
		}
		else
		{
			strcpy(course_table[term][local][week_day], course_name);
			return true;
		}
	}
	return false;
}

//�����ſΣ������ڿ�
bool range_two(int &week_day, int term, char* course_name)
{
	int local;
	for (int i = 0; i < 5; i++)
	{
		local = find_two(week_day, term);
		if (-1 == local)
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
		}
		else
		{
			strcpy(course_table[term][local][week_day], course_name);
			strcpy(course_table[term][local+1][week_day], course_name);
			return true;
		}
	}
	return false;

}

//�����ſΣ������ڿ�
bool range_three(int &week_day, int term, char* course_name)
{
	int local;
	for (int i = 0; i < 5; i++)
	{
		local = find_three(week_day, term);
		if (-1 == local)
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
		}
		else
		{
			strcpy(course_table[term][local][week_day], course_name);
			strcpy(course_table[term][local+1][week_day], course_name);
			strcpy(course_table[term][local+2][week_day], course_name);
			return true;
		}
	}
	return false;
}

//����һ�ڿտΣ������ص�һ�ڿεĽڴ�
int find_one(int week_day, int term)
{
	for (int i = 1; i <= 9; i++)
	{
		if (strlen(course_table[term][i][week_day])==0)
		{
			return i;
		}

	}
	return -1;
}

//�������ڿտΣ������ص�һ�ڿεĽڴ�
int find_two(int week_day, int term)
{
	if (strlen(course_table[term][1][week_day]) == 0 && strlen(course_table[term][2][week_day]) == 0 )
	{
		return 1;
	}
	if (strlen(course_table[term][3][week_day]) == 0 && strlen(course_table[term][4][week_day]) == 0)
	{
		return 3;
	}
	if (strlen(course_table[term][8][week_day]) == 0 && strlen(course_table[term][9][week_day]) == 0)
	{
		return 8;
	}
	if (strlen(course_table[term][5][week_day]) == 0 && strlen(course_table[term][6][week_day]) == 0)
	{
		return 5;
	}

	return -1;
}

//�������ڿտΣ������ص�һ�ڿεĽڴ�
int find_three(int week_day, int term)
{
	if (strlen(course_table[term][5][week_day]) == 0 && strlen(course_table[term][6][week_day]) == 0 &&
		strlen(course_table[term][7][week_day]) == 0)
	{
		return 5;
	}
	if (strlen(course_table[term][1][week_day]) == 0 && strlen(course_table[term][2][week_day]) == 0 &&
		strlen(course_table[term][3][week_day]) == 0)
	{
		return 1;
	}
	return -1;
}