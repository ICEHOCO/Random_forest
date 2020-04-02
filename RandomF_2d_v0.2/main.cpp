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
	//1����ȡ������Ԥ����
	//��ʼ�����������
	srand(static_cast<unsigned int>(time(NULL)));
	bool readFlag = false;
	float** DataSet = ReadData(false, &readFlag, TRAINNUM, FEATURENUM);
	if (readFlag == false) {
		system("pause");
		return -1;
	}
	int* LabelSet = ReadLabel(false,TRAINNUM);
	/*SMOTE:������������
	ע�⣺1��ĳһ����������� ����Ҫ�� ������������ �� 1������TODO��
	2��Xnew = Xi + 0.38 * �� * (Xi - Xij); XijΪ��Զ�ĵ㣨ŷ�����룩
	*/
	SMOTE_Set p = SMOTE(DataSet, LabelSet, TRAINNUM, CLASSNUM, FEATURENUM);
	DataSet = p.data;
	LabelSet = p.label;
	//�����ע�����ѵ��������
	int trainNum = p.length;
	OutputDataFile(DataSet);

	//�ָ�ϣ�ѵ����-> ѵ�� + ԤԤ��
	float** Pre_DataSet;
	int* Pre_LabelSet;
	Split_Set q = PreSplit(DataSet, LabelSet, trainNum, CLASSNUM, 3);
	DataSet = q.data;
	LabelSet = q.label;
	trainNum = q.length;
	Pre_DataSet = q.pre_data;
	Pre_LabelSet = q.pre_label;
	int testNum = q.pre_length;
	//2���������ɭ����Ԥ-Ԥ��
	const int minSamplePerNode = 10;//����С����������
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, trainNum, minSamplePerNode, FEATURENUM, CLASSNUM, 3);

	//3��ѵ�����ɭ��
	randomforest->train();

	//3.5��ԤԤ��
	randomforest->pre_predict(Pre_DataSet, Pre_LabelSet, testNum, 0.88, 1.05);

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
	//���ɭ��Ԥ��
	testLabel = randomforest->predict(TestDataSet, TESTNUM);
	
	//5���������
	int missCount = 0;
	for (int i = 0; i < TESTNUM; i++) {
		float correct_prob = testLabel[i].prob / randomforest->get_AllWeight();
		cout << "�� " << i << " ��������Ԥ����Ϊ:" << testLabel[i].classnum << "\t����Ϊ: " << correct_prob*100 << endl;;
		if (testLabel[i].classnum != answerLabel[i]) {
			missCount++;
		}
	}
	float correct_Ratio = static_cast<double>((TESTNUM - missCount)) / TESTNUM;
	cout << "��ȷ��Ϊ:" << correct_Ratio << endl;
	cout << "��Ȩ��Ϊ:" << randomforest->get_AllWeight() << endl;
	system("pause");
	
	//�ͷſռ䣬��ֹ�ڴ�й©
	delete randomforest;
	for (int i = 0; i < TRAINNUM; i++) {
		delete[] DataSet[i];
	}
	delete[] DataSet;
	delete[] LabelSet;
	return 0;
}

