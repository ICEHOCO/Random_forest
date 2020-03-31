#include "Randomforest.h"
//���ɭ�� ���Ա�����Ķ���

RandomForest::RandomForest(float** dataset, int* labelset, int TreeNum, int maxDepth,
	int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum, int RandFeatureNum)
{
	this->TreeNum = TreeNum;
	this->classNum = classNum;
	//��ʼ����   
	this->carTreeArray.resize(this->TreeNum);
	for (int i = 0; i < TreeNum; i++) {
		this->carTreeArray[i] = new Tree(dataset, labelset, maxDepth, SampleNumPerTree, 
											minSampleNumPerNode, featureNum, this->classNum, RandFeatureNum);
	}
}
RandomForest::~RandomForest()
{
	for (int i = 0; i < this->TreeNum; i++) {
		delete carTreeArray[i];
	}
}
void RandomForest::train()
{
	//���ú�����ʱ���Ѿ�ִ�й���ʼ��!
	//Ŀǰ  ��������  ��  ÿ�����Ľ������  ���Ѿ���ʼ�����
	for (int i = 0; i < this->TreeNum; i++) {
		if (i % 10 == 0) {
			cout << "���ɭ��ѵ�����ȣ� " << i << "/100 ..." << endl;
		}
		carTreeArray[i]->train();
	}
	cout << "ѵ����ɣ�" << endl;
	return;
}

Result* RandomForest::predict(float** testSet, int testNum)
{
	Result* testLabelset = new Result[testNum];
	double* resultProb;
	resultProb = new double [classNum];
	for (int i = 0; i < testNum; i++) {
		//��ʼ��
		for (int j = 0; j < classNum; j++) {
			resultProb[j] = 0;
		}
		//ÿ�����������
		for (int j = 0; j < TreeNum; j++) {
			carTreeArray[j]->predict(testSet[i], &resultProb);
		}

		int max = 0;
		for (int j = 1; j < classNum; j++) {
			if (resultProb[max] < resultProb[j])
				max = j;
		}
		testLabelset[i].classnum = max;
		testLabelset[i].prob = resultProb[max];
	}
	delete[] resultProb;
	return testLabelset;
}