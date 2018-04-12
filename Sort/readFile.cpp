#ifndef readFile_H
#define readFile_H 1

#include"ReadFile.h"

//����ע�ͣ����Ҵ�������ʱ�ļ�
static void xiao_chu_zhu_shi(fstream &in, fstream &out);
//����ʱ�ļ��ж�ȡ�ļ�������
static int du_qu_wen_jian(fstream &in,int*nums,Course*courses);

int getAllCourseFromFile(Course *courses,string fileName,int *nums)
{
	//���ļ�
	fstream readFile(fileName,ios::in);
	if (!readFile)
	{
		cout << "���ļ�ʧ�ܣ���readFile.cpp����" << fileName.data();
		return -1;
	}
	//����ʱ�ļ�
	string tempFile;
	tempFile = fileName;
	tempFile += ".temp";
	fstream tempOutFile(tempFile, ios::out);
	if (!tempOutFile)
	{
		cout << "���ļ�ʧ�ܣ���readFile.cpp����" << tempFile.data();
		return -1;
	}

	//����ע��
	xiao_chu_zhu_shi(readFile, tempOutFile);
	tempOutFile.close();
	
	//��ȡ�ļ�
	fstream tempInFile(tempFile, ios::in);
	if (!tempInFile)
	{
		cout << "In���ļ�ʧ�ܣ���readFile.cpp����" << tempFile.data();
		return -1;
	}
	int numberOfCourse;
	numberOfCourse = du_qu_wen_jian(tempInFile, nums, courses);
	tempInFile.close();

	//�ͷ���Դ
	readFile.close();
	return numberOfCourse;
}

void xiao_chu_zhu_shi(fstream &in, fstream &out)
{
	char ch;
	char lastCh = 'a';
	while (!in.eof())
	{

		//����ע����
		ch = in.get();
		if ('/' == ch)
		{
			ch = in.get();
			if ('/' == ch)
			{
				while ('\n' != (ch = in.get()));
				lastCh = '\n';
				continue;
			}
			else
			{
				in.putback(ch);
				ch = '/';
			}
		}
		//д����ʱ�ļ�
		if (!('\n'==lastCh&&'\n'==ch))
		{
			out.put(ch);
		}
		lastCh = ch;
	}
}

int du_qu_wen_jian(fstream &in,int *nums,Course* courses)
{
	for (int i = 0; i < 8; i++)
	{
		in >> nums[i];
	}

	int count = 0;
	char *chstemp = new char[50];
	char temp;
	short numtemp;
	while (!in.eof())
	{
		in >> chstemp;
		//����ĩβ�ǿո�
		if (in.eof())
		{
			break;
		}
		courses[count].setCode(chstemp);
		in >> chstemp;
		courses[count].setName(chstemp);
		in >> numtemp;
		courses[count].setStudyTime(numtemp);
		in >> numtemp;
		courses[count].setTerm(numtemp);
		
		while ('\n'!=(temp=in.get()))
		{
			if (' '!=temp&&'\t'!=temp)
			{
				in.putback(temp);
				in >> chstemp;
				courses[count].addCondition(chstemp);
			}
		}
		count++;
	}

	//�ͷ���Դ
	delete chstemp;

	return count;
 }
#endif // !readFile_H