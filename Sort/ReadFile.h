#pragma once
#ifndef ReadFile_h
#define ReadFile_h 1

#include"Course.h"

#include<fstream>

//����ͨ�� ���ش�
//���ڣ�2016/12/13/20:01
//���ߣ����ش�
//���ļ��ж�ȡ��Ϣ����������Course����,���ض�ȡ�Ŀγ�����
extern int getAllCourseFromFile(Course *courses,string fileName,int*nums);

#endif // !
