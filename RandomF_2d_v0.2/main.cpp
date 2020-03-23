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
	const int minSamplePerNode = 10;//����С����������
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, TRAINNUM, minSamplePerNode, FEATURENUM, CLASSNUM);
	//3��ѵ�����ɭ��
	randomforest->train();
	
	system("pause");
	
	//�ͷſռ䣬��ֹ�ڴ�й©
	for (int i = 0; i < TRAINNUM; i++) {
		delete[] DataSet[i];
		DataSet[i] = NULL;
	}
	delete[] LabelSet;
	LabelSet = NULL;

	return 0;
}

