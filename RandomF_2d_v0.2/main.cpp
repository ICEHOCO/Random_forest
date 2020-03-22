// main.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "Dataprocess.h"	
#include "RandomForest.h"

//ѵ��
#define TRAINNUM    150		//ѵ��������
#define FEATURENUM  2		//������ά��
#define CLASSNUM    3		//��������
//����
#define TESTNUM		50		//����������
//��������
#define TREENUM		100		//��������
#define MAXDEPTH	5		//ÿ����������

int main()
{
	vector<float> dataset;
	vector<int> labelset;
	//1����ȡ�������ǩ
	if (!ReadAll(&dataset, &labelset, TRAINNUM, false)) { system("pause"); return -1; };
	float** DataSet = ReadData(true);
	int* LabelSet = ReadLabel(false);
	//2���������ɭ��
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, TRAINNUM, 10, FEATURENUM, CLASSNUM);
	//3��ѵ�����ɭ��
	randomforest->train();
	
	system("pause");
	
	//�ͷſռ䣬��ֹ�ڴ�й©
	int point_num = TRAINNUM / FEATURENUM;
	for (int i = 0; i < point_num; i++) {
		delete[] DataSet[i];
		DataSet[i] = NULL;
	}
	delete[] LabelSet;
	LabelSet = NULL;

	return 0;
}

