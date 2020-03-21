// main.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "Dataprocess.h"	
#include "RandomForest.h"

#define TRAINNUM    200		//ѵ��������
#define FEATURENUM  2		//������ά��
#define TESTNUM		50		//����������
#define TREENUM		100		//��������
#define MAXDEPTH	5		//ÿ����������
int main()
{
	vector<float> dataset;
	vector<int> labelset;
	//dataset = readData(TRAINNUM, true);
	//labelset = readLabel(TRAINNUM, true);
	//��ȡ�������ǩ
	if (!ReadAll(&dataset, &labelset, TRAINNUM, true)) { system("pause"); return -1; };
	//�������ɭ��
	RandomForest* randomforest;
	randomforest = new RandomForest(&dataset, &labelset, TREENUM, MAXDEPTH, TRAINNUM, 10, FEATURENUM);
	
	
	system("pause");

	return 0;
}

