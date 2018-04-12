#pragma once
#ifndef Course_h
#define Course_h 1

#include<vector>
#include<iostream>

using namespace std;

//����ͨ�� ���ش�
//���ڣ�2016/12/13/19:55
//���ߣ����ش�
//�洢�γ���Ϣ
class Course
{
public:
	Course(string code,string name,short studyTime,short term);
	Course();
	~Course();

	//�γ̱��
	void setCode(string code);
	string getCode();
	//�γ�����
	void setName(string mname);
	string getName();
	//�γ�ѧʱ
	void setStudyTime(short mstudyTime);
	short getStudyTime();
	//�γ̿�ʼѧ��
	void setTerm(short mterm);
	short getTerm();
	//�γ�ǰ������
	void addCondition(string code);
	vector<string> getCondition();

	bool IsLimit();
private:
	string code;
	string name;
	short studyTime;
	short term;
	vector<string> condition;

	bool isLimit;//�Ƿ���ǰ������
};

#endif // !Course.h
