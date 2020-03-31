// main.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "Dataprocess.h"	
#include "RandomForest.h"


//ѵ��
#define TRAINNUM    87		//ѵ��������
#define FEATURENUM  8		//������ά��
#define CLASSNUM    3		//��������
//����
#define TESTNUM		40		//����������
//��������
#define TREENUM		100		//��������
#define MAXDEPTH	3 		//ÿ���������� 

int main()
{
	//1����ȡ�������ǩ
	//��ʼ�����������
	srand(static_cast<unsigned int>(time(NULL)));
	bool readFlag = false;
	float** DataSet = ReadData(false, &readFlag, TRAINNUM, FEATURENUM);
	if (readFlag == false) {
		system("pause");
		return -1 ;
	}
	int* LabelSet = ReadLabel(false,TRAINNUM);
	//2���������ɭ��
	const int minSamplePerNode = 10;//����С����������
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, TRAINNUM, minSamplePerNode, FEATURENUM, CLASSNUM, 3);
	//3��ѵ�����ɭ��
	randomforest->train();

	//4��Ԥ��
	float** TestDataSet;//���ļ��ж�ȡ�������ݼ�
	readFlag = false;
	TestDataSet = ReadTestData(false, &readFlag, TESTNUM, FEATURENUM);
	if (readFlag == false) {
		system("pause");
		return -1;
	}
	Result* testLabel;
	int* answerLabel = ReadTestLabel(false, TESTNUM);
	testLabel = randomforest->predict(TestDataSet, TESTNUM);
	
	int missCount = 0;
	for (int i = 0; i < TESTNUM; i++) {
		cout << "�� " << i << " ��������Ԥ����Ϊ:" << testLabel[i].classnum << "\t����Ϊ: " << testLabel[i].prob << endl;;
		if (testLabel[i].classnum != answerLabel[i]) {
			missCount++;
		}
	}
	double correct_Ratio = static_cast<double>(TESTNUM - missCount) / TESTNUM;
	cout << "��ȷ��Ϊ:" << correct_Ratio << endl;
	system("pause");
	
	//�ͷſռ䣬��ֹ�ڴ�й©
	delete randomforest;
	for (int i = 0; i < TRAINNUM; i++) {
		delete[] DataSet[i];
	}
	delete[] LabelSet;
	return 0;
}

