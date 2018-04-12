#pragma once
#ifndef Graph_H
#define Graph_H 1

#include<iostream>

class Graph
{
public:
	Graph(int n);
	~Graph();
	int n()const;
	int e()const;
	int first(int v)const;
	int next(int v, int w)const;
	void setEdge(int v, int w, int wgt);
	void deletEdge(int v, int w);
	int weight(int v, int w)const;
	int getMark(int v)const;
	void setMark(int v,int val);
	void subOneInDegree(int v);//����V���ڵĵ���ȼ�һ
	int* getAllIndegree();//���ش洢��ȵ�����
private:
	int numVertex;
	int numEdge;
	int **matrix;
	int *mark;

	int *inDegree;
};

#endif // !Graph_H
